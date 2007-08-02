/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/debug.h>
#include <crisscross/core_network.h>
#include <crisscross/core_socket.h>

#if defined ( TARGET_OS_MACOSX )
#    define _BSD_SOCKLEN_T_ int
#endif

#if !defined ( TARGET_OS_WINDOWS )
#    include <arpa/inet.h>
#    include <errno.h>
#    include <netdb.h>
#    include <netinet/in.h>
#    include <netinet/tcp.h>
#    include <sys/ioctl.h>
#    include <sys/socket.h>
#    include <signal.h>
#    define INVALID_SOCKET -1
#    define SOCKET_ERROR -1
#else
     typedef int socklen_t;
#endif

using namespace CrissCross::Network;

// #define PACKET_DEBUG

CoreSocket::CoreSocket()
{
    CrissCross::Errors retval = __initialise_network();
    m_calledInitialise = 1;
    CoreAssert ( retval == CC_ERR_NONE );
    memset ( &m_sock, 0, sizeof ( socket_t ) );
    m_sock = INVALID_SOCKET;
    m_state = SOCKET_STATE_NOT_CREATED;
    m_bufferSize = 8192;
}

CoreSocket::CoreSocket ( socket_t socket )
    : m_calledInitialise ( 0 )
{
    /* Calling __initialise_network() is NOT
       necessary if we have a socket to copy. */
    CoreAssert ( socket != INVALID_SOCKET );
    m_sock = socket;
    m_state = SOCKET_STATE_UNKNOWN;
    m_bufferSize = 8192;
}

CoreSocket::~CoreSocket()
{
    Close();
    if ( m_calledInitialise == 1 )
        __cleanup_network();
}

CrissCross::Errors
CoreSocket::Ban ( unsigned long _host )
{
#if defined ( ENABLE_PROTECTION )
    if ( m_banned_hosts.findNode ( &_host ) == NULL )
        m_banned_hosts.insert ( &_host, (char *)1 );
#endif
    return CC_ERR_NONE;
}

CrissCross::Errors
CoreSocket::Close()
{
    if ( m_sock == INVALID_SOCKET ) return CC_ERR_ENOTSOCK;

    // Close the socket.
#ifdef TARGET_OS_WINDOWS
    closesocket ( m_sock );
#else
    close ( m_sock );
#endif
    m_sock = INVALID_SOCKET;
    m_state = SOCKET_STATE_NOT_CREATED;
    return CC_ERR_NONE;
}

const char *
CoreSocket::GetRemoteIP ()
{
    // Verify the socket.
    if ( m_sock == INVALID_SOCKET ) return NULL;

    static char buffer[15];
    struct sockaddr_in sock; int sock_size = sizeof(sock);
    memset ( &sock, 0, sizeof(sock) );

    // Resolve the remote IP.
    getpeername ( m_sock, (sockaddr *)&sock, (socklen_t *)&sock_size );

    // Print it to a buffer.
    sprintf ( buffer, inet_ntoa ( sock.sin_addr ) );

    // Return it.
    return buffer;
}

u_long
CoreSocket::GetLocalHost ()
{
    char str[512];
    long result = gethostname( str, sizeof(str) );
    if (result < 0) 
    {
        return 0;
    }

    struct hostent *lpHostEnt;
    lpHostEnt = gethostbyname (str);

    struct sockaddr_in addr;
    memcpy( &addr.sin_addr, lpHostEnt->h_addr_list[0], sizeof(addr.sin_addr) );
    addr.sin_port = 0;

    const unsigned char *a = (const unsigned char *) &addr.sin_addr;
    result = (a[0] << 24) + (a[1] << 16) + (a[2] << 8) + a[3];

    return result;
}

u_long
CoreSocket::GetRemoteHost ()
{
    if ( m_sock == INVALID_SOCKET ) return 0;

    struct sockaddr_in addr; int sock_size = sizeof(addr);
    memset ( &addr, 0, sizeof(addr) );
    getpeername ( m_sock, (sockaddr *)&addr, (socklen_t *)&sock_size );

    // Return the remote host (not the IP, but the bare host).
    return addr.sin_addr.s_addr;
}

socket_t
CoreSocket::GetSocket()
{
    // ugh. Allow the user to do whatever they want with the socket.
    return m_sock;
}

bool
CoreSocket::IsBanned ( unsigned long _host ) const
{
#if defined ( ENABLE_PROTECTION )
    if ( m_banned_hosts.find ( &_host ) )
        return true;
    else
#endif
        return false;
}

int
CoreSocket::Read ( std::string &_output )
{
    if ( m_sock == INVALID_SOCKET ) return CC_ERR_ENOTSOCK;

    char *buf = new char[m_bufferSize];
    memset ( buf, 0, m_bufferSize );
    int ret = 0, recvlen = 0;

    recvlen = recv ( m_sock, buf, m_bufferSize - 1, 0 );
    ret = errno;

    _output = std::string ( buf );

    delete [] buf;

    return ( recvlen == 0 ) ? CC_ERR_NONE : errno;
}

int
CoreSocket::Read ( char *_output, unsigned int *_len )
{
    // Sanity checks.
    if ( m_sock == INVALID_SOCKET ) return CC_ERR_ENOTSOCK;
    if ( _len == NULL ) return CC_ERR_BADPARAMETER;
    if ( _output == NULL ) return CC_ERR_BADPARAMETER;

    // Set up a buffer.
    int recvlen = 0;
    memset ( _output, 0, *_len );

    // Receive some data.
    recvlen = recv ( m_sock, _output, *_len, 0 );
    if ( recvlen < 0 )
    {
        // Something's wrong here...
        return GetError();
    }

    *_len = recvlen;

    return CC_ERR_NONE;
}

CrissCross::Errors
CoreSocket::GetError ()
{
    CoreAssert ( m_sock != 0 );
    int retval = 0;

#if !defined ( TARGET_OS_WINDOWS )
    //int retsize = sizeof ( int ), ret = 0;
    //ret = getsockopt ( m_sock, SOL_SOCKET, SO_ERROR, (char *)&retval, (socklen_t*)&retsize );
    //if ( ret != 0 ) return CC_ERR_INTERNAL;
    retval = errno;
#else
    retval = WSAGetLastError ();
#endif
    return GetErrorNumber ( retval );
}

int
CoreSocket::Send ( const void *_data, size_t _length )
{
    CoreAssert ( m_sock != 0 );

    int sent = 0;
#ifdef PACKET_DEBUG
    char *temp_buf = new char[m_bufferSize];
    memset ( temp_buf, 0, m_bufferSize );
    char *p = temp_buf, *d = (char *)_data;
    while ( *d != '\x0' )
    {
        if ( !( *d == '\n' || *d == '\r' ) )
            *p = *d;
        p++; d++;
    }
    fprintf ( stdout, "<<< '%s'\n", temp_buf );
    delete [] temp_buf;
#endif
    sent = send ( m_sock, (const char *)_data, (int)_length, 0 );
    return sent;
}

int
CoreSocket::Send ( std::string _data )
{
    CoreAssert ( m_sock != 0 );

    int sent = 0;
#ifdef PACKET_DEBUG
    char *temp_buf = new char[m_bufferSize];
    memset ( temp_buf, 0, m_bufferSize );
    char *p = temp_buf, *d = (char *)_data.c_str();
    while ( *d != '\x0' )
    {
        if ( !( *d == '\n' || *d == '\r' ) )
            *p = *d;
        p++; d++;
    }
    fprintf ( stdout, "<<< '%s'\n", temp_buf );
    delete [] temp_buf;
#endif
    sent = send ( m_sock, _data.c_str(), (int)_data.size(), 0 );
    return sent;
}

socketState
CoreSocket::State() const
{
    // SO_ACCEPTCONN (DWORD:boolean, get) : determine whether a socket is listening.
    // SO_CONDITIONAL_ACCEPT (DWORD:boolean, get/set): determines whether a socket on
    //    the stack level will accept connections or not.
    // SO_ERROR (DWORD, get): per-socket error code.
    //
    return m_state;
}
