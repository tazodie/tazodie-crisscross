/*
 *
 *                               C R I S S C R O S S _ N E T
 *                           A cross platform networking library.
 *                              formerly Codename "Rivendell"
 *                             project started August 30, 2006
 *
 * Copyright (c) 2006 IO.IN Research
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of the I.O. Independent Network nor the names of its contributors
 *       may be used to endorse or promote products derived from this software without
 *       specific prior written permission.
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
#include "core_socket.h"
#include "tcpsocket.h"

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

TCPSocket::TCPSocket()
    : CoreSocket()
{
    m_proto = PROTOCOL_TCP;
}

TCPSocket::TCPSocket ( socket_t _socket )
    : CoreSocket ( _socket )
{
    m_proto = PROTOCOL_TCP;
}

TCPSocket::~TCPSocket ()
{
}

TCPSocket *TCPSocket::Accept()
{
    /* TODO: Implement a much more elegant ability to
             REJECT a connection if it IsBanned(). */
    socket_t sock = accept ( m_sock, 0, 0 );

    if ( sock != INVALID_SOCKET )
    {
#if defined ( ENABLE_PROTECTION )
        struct sockaddr_in saddr_sock; int sock_size = sizeof(saddr_sock);
        memset ( &saddr_sock, 0, sizeof(saddr_sock) );
        getpeername ( sock, (sockaddr *)&saddr_sock, (socklen_t *)&sock_size );
        if ( IsBanned ( saddr_sock.sin_addr.s_addr ) )
        {
#ifdef TARGET_OS_WINDOWS
            closesocket ( sock );
#else
            close ( sock );
#endif
            return NULL;
        }
#endif
        SetAttributes ( sock );

        unsigned long arg = 1;
#if defined ( TARGET_OS_WINDOWS )
        ioctlsocket ( m_sock, FIONBIO, &arg );
#else
        ioctl ( m_sock, FIONBIO, &arg );
#endif
        TCPSocket *csock = new TCPSocket ( sock );

        return csock;
    }
    return NULL;
}

int TCPSocket::Connect ( CONST CHAR *_address, unsigned short _port )
{
    struct sockaddr_in sin;
    struct hostent *host;

    if ( m_sock != INVALID_SOCKET ) return CC_ERR_SOCK_SOCKET_IN_USE;

    m_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( m_sock == INVALID_SOCKET )
        return CC_ERR_SOCK_CREATE_SOCKET;

    SetAttributes ( m_sock );

    host = gethostbyname ( _address );
    if ( !host ) return errno;

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
        return CC_ERR_SOCK_CONNECT;
    }

    unsigned long arg = 1;
#if defined ( TARGET_OS_WINDOWS )
    ioctlsocket ( m_sock, FIONBIO, &arg );
#else
    ioctl ( m_sock, FIONBIO, &arg );
#endif

    return CC_ERR_NONE;
}

CrissCross::Errors TCPSocket::Listen ( unsigned short _port )
{
    struct sockaddr_in sin;

    if ( m_sock != INVALID_SOCKET ) return CC_ERR_SOCK_SOCKET_IN_USE;

    memset ( &sin, 0, sizeof ( sin ) );

    sin.sin_family = PF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons ( _port );
    m_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( m_sock == INVALID_SOCKET )
        return CC_ERR_SOCK_CREATE_SOCKET;

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
        return CC_ERR_SOCK_BIND;
    }

    if ( listen ( m_sock, 10 ) == SOCKET_ERROR )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
        return CC_ERR_SOCK_LISTEN;
    }

    return CC_ERR_NONE;
}

int TCPSocket::SetAttributes ( socket_t _socket )
{
    /* TCP_NODELAY */
    int err, optval = 1, optlen = sizeof optval;
    err = setsockopt ( _socket, IPPROTO_TCP,
          TCP_NODELAY, (CHAR *) &optval, optlen );
    if ( err == -1 ) return errno; 

    /* SO_LINGER */
    struct linger linger_opts;
    linger_opts.l_onoff = 1;
    linger_opts.l_linger = 10;
    optlen = sizeof linger_opts;
    err = setsockopt ( _socket, SOL_SOCKET,
          SO_LINGER, (CHAR *) &linger_opts, optlen );
    if ( err == -1 ) return errno;

    /* SO_KEEPALIVE */
    optlen = sizeof optval;
    err = setsockopt ( _socket, SOL_SOCKET,
          SO_KEEPALIVE, (CHAR *) &optval, optlen );
    if ( err == -1 ) return errno;

    return CC_ERR_NONE;
}
