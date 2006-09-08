/*
 *
 *                               C R I S S C R O S S _ N E T
 *                           A cross platform networking library.
 *                              formerly Codename "Rivendell"
 *                             project started August 30, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "universal_include.h"
#include "core_debug.h"
#include "core_network.h"
#include "core_socket.h"

#if !defined ( TARGET_OS_WINDOWS )
#    include <asm/ioctls.h>
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

CoreSocket::CoreSocket()
    : m_sock ( INVALID_SOCKET ), m_calledInitialise ( 1 )
{
    __initialise_network();
    memset ( &m_sock, 0, sizeof ( socket_t ) );
}

CoreSocket::CoreSocket ( socket_t socket )
    : m_sock ( INVALID_SOCKET ), m_calledInitialise ( 0 )
{
    /* Calling __initialise_network() is NOT
       necessary if we have a socket to copy. */
    CoreAssert ( socket != 0 );
    m_sock = socket;
}

CoreSocket::~CoreSocket()
{
    if ( m_sock != INVALID_SOCKET )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
    }
    if ( m_calledInitialise == 1 )
        __cleanup_network();
}

socket_t CoreSocket::GetSocket()
{
    return m_sock;
}

int CoreSocket::Ban ( unsigned long _host )
{
    if ( m_banned_hosts.findNode ( &_host ) == NULL )
        m_banned_hosts.insert ( &_host, (char *)1 );
    else
        return -1;
    return 0;
}

bool CoreSocket::IsBanned ( unsigned long _host ) const
{
    if ( m_banned_hosts.find ( &_host ) )
        return true;
    else
        return false;
}

int CoreSocket::Close()
{
#ifdef TARGET_OS_WINDOWS
    int retval = closesocket ( m_sock );
#else
    int retval = close ( m_sock );
#endif
    m_sock = 0;
    return retval;
}

int CoreSocket::Connect ( const char *_address, unsigned short _port )
{
    struct sockaddr_in sin;
    struct hostent *host;

    m_sock = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( m_sock == INVALID_SOCKET )
        return 1;

    SetAttributes ( m_sock );

    host = gethostbyname ( _address );

    memset ( &sin, 0, sizeof ( sin ) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ( ( struct in_addr * ) ( host->h_addr ) )->s_addr;
    sin.sin_port = htons ( _port );

    if ( connect ( m_sock, ( ( struct sockaddr * ) 
        &sin ), sizeof ( sin ) ) == SOCKET_ERROR )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
        return 2;
    }
    return 0;
}
CoreSocket *CoreSocket::Accept()
{
    /* TODO: Implement a much more elegant ability to
             REJECT a connection if it IsBanned(). */
#if !defined ( TARGET_OS_WINDOWS )
    struct sockaddr_in saddr_sock; int sock_size = sizeof(saddr_sock);
    memset ( &saddr_sock, 0, sizeof(saddr_sock) );
    getpeername ( m_sock, (sockaddr *)&saddr_sock, &sock_size );
    if ( IsBanned ( saddr_sock.sin_addr.s_addr ) )
    {
        return NULL;
    }

    socket_t sock = accept ( m_sock, 0, 0 );
#else
    socket_t sock = accept ( m_sock, 0, 0 );

    struct sockaddr_in saddr_sock; int sock_size = sizeof(saddr_sock);
    memset ( &saddr_sock, 0, sizeof(saddr_sock) );
    getpeername ( sock, (sockaddr *)&saddr_sock, &sock_size );
    if ( IsBanned ( saddr_sock.sin_addr.s_addr ) )
    {
        closesocket ( sock );
        return NULL;
    }
#endif

    if ( sock != INVALID_SOCKET )
    {
        SetAttributes ( sock );
        CoreSocket *csock = new CoreSocket ( sock );
        return csock;
    }
    return NULL;
}

int CoreSocket::Listen ( unsigned short _port )
{
    struct sockaddr_in sin;
    memset ( &sin, 0, sizeof ( sin ) );

    sin.sin_family = PF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons ( _port );
    m_sock = socket ( AF_INET, SOCK_STREAM, 0 );

    if ( m_sock == INVALID_SOCKET )
        return 1;

    SetAttributes ( m_sock );

    unsigned long arg = 1;
#if defined ( TARGET_OS_WINDOWS )
    ioctlsocket ( m_sock, FIONBIO, &arg );
#else
    ioctl ( m_sock, FIONBIO, &arg );
#endif

    if ( bind ( m_sock, (sockaddr *)&sin, sizeof ( sin ) ) == SOCKET_ERROR )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
        return 2;
    }

    if ( listen ( m_sock, 10 ) == SOCKET_ERROR )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
        return 3;
    }

    return 0;
}

char *CoreSocket::Internal_Read ( int _len ) const
{
    CoreAssert ( m_sock != 0 );

    char *buf = new char[_len + 1];
    memset ( buf, 0, _len + 1 );

    recv ( m_sock, buf, _len, 0 );

    return buf;

}

int CoreSocket::Read ( std::string &_output, int _len ) const
{
    CoreAssert ( m_sock != 0 );

    char *buf = new char[_len + 1];
    memset ( buf, 0, _len + 1 );
    int ret = 0, recvlen = 0;

    recvlen = recv ( m_sock, buf, _len, 0 );
    ret = errno;

    _output = std::string ( buf );

    delete [] buf;

    if ( recvlen == 0 ) return -2;
    return ret;
}

int CoreSocket::Read ( char **_output, int _len ) const
{
    /* TODO: MERGE INTERNAL_READ HERE */
    *_output = Internal_Read ( _len );
    return 0;
}

int CoreSocket::Send ( const char *_packet, size_t _length )
{
    CoreAssert ( m_sock != 0 );

    int sent = 0;
    sent = send ( m_sock, _packet, (int)_length, 0 );
    return sent;
}

int CoreSocket::Send ( std::string _packet )
{
    CoreAssert ( m_sock != 0 );

    int sent = 0;
    sent = send ( m_sock, _packet.c_str(), (int)_packet.size(), 0 );
    return sent;
}

int CoreSocket::SetAttributes ( socket_t _socket )
{
    int optval = 1, optlen = sizeof optval;
    int err = setsockopt ( _socket, IPPROTO_TCP,
        TCP_NODELAY, (char *) &optval, optlen );
    if ( err != 0 ) return -1;
    err = setsockopt ( _socket, IPPROTO_TCP,
        SO_KEEPALIVE, (char *) &optval, optlen );
    if ( err != 0 ) return -1;
    return 0;
}