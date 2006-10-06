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
#include "core_socket.h"
#include "udpsocket.h"

#if !defined ( TARGET_OS_WINDOWS )
#    include <arpa/inet.h>
#    include <asm/ioctls.h>
#    include <asm/socket.h>
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

UDPSocket::UDPSocket()
    : CoreSocket()
{
    m_proto = PROTOCOL_UDP;
}

UDPSocket::~UDPSocket ()
{
}

CrissCross::Errors UDPSocket::Bind ( const char *_address, unsigned short _port )
{
    struct sockaddr_in sin;
    struct hostent *host;

    if ( m_sock != INVALID_SOCKET ) return CC_ERR_SOCK_SOCKET_IN_USE;

    m_sock = socket ( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    if ( m_sock == INVALID_SOCKET )
        return CC_ERR_SOCK_CREATE_SOCKET;

    SetAttributes ( m_sock );

    host = gethostbyname ( _address );
    if ( !host ) return CC_ERR_SOCK_DNS;

    memset ( &sin, 0, sizeof ( sin ) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ( ( struct in_addr * ) ( host->h_addr ) )->s_addr;
    sin.sin_port = htons ( _port );

    if ( int retval = connect ( m_sock, ( ( struct sockaddr * ) 
        &sin ), sizeof ( sin ) ) == SOCKET_ERROR )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
        return CC_ERR_SOCK_CONNECT;
    }
    return CC_ERR_NONE;
}

CrissCross::Errors UDPSocket::Listen ( unsigned short _port )
{
    struct sockaddr_in sin;

    if ( m_sock != INVALID_SOCKET ) return CC_ERR_SOCK_SOCKET_IN_USE;

    memset ( &sin, 0, sizeof ( sin ) );

    sin.sin_family = PF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons ( _port );
    m_sock = socket ( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

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

    return CC_ERR_NONE;
}
