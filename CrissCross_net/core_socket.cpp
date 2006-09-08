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

using namespace CrissCross::Network;

CoreSocket::CoreSocket()
    : m_sock ( 0 )
{
    __initialise_network();
    memset ( &m_sock, 0, sizeof ( socket_t ) );
}

CoreSocket::CoreSocket ( socket_t socket )
    : m_sock ( 0 )
{
    /* Calling __initialise_network() is NOT
       necessary if we have a socket to copy. */
    CoreAssert ( socket != NULL );
    m_sock = socket;
}

CoreSocket::~CoreSocket()
{
    if ( m_sock != 0 )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
    }
    __cleanup_network();
}

int CoreSocket::Close()
{
#ifdef TARGET_OS_WINDOWS
    return closesocket ( m_sock );
#else
    close ( m_sock );
#endif
}

int CoreSocket::Connect ( const char *_address, unsigned short _port )
{
    struct sockaddr_in sin;
    struct hostent *host;

    m_sock = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( m_sock == INVALID_SOCKET )
        return 1;

    int optval = 1, optlen = sizeof optval;
    int err = setsockopt ( m_sock, IPPROTO_TCP,
        TCP_NODELAY, (char *) &optval, optlen );
    CoreAssert ( err == 0 );

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
    struct sockaddr_in sin; int sin_size = sizeof ( sin );
    memset ( &sin, 0, sizeof ( sin ) );
    socket_t sock = accept ( m_sock, (sockaddr *)&sin, &sin_size );
    if ( sock != INVALID_SOCKET )
    {
        CoreSocket *csock = new CoreSocket ( sock  );
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

    int optval = 1, optlen = sizeof optval;
    int err = setsockopt ( m_sock, IPPROTO_TCP,
        TCP_NODELAY, (char *) &optval, optlen );
    CoreAssert ( err == 0 );

    unsigned long arg = 1;
    ioctlsocket ( m_sock, FIONBIO, &arg );

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

char *CoreSocket::Internal_Read ( int len ) const
{
    CoreAssert ( m_sock != NULL );

    char *buf = new char[len];

#ifdef TARGET_OS_WINDOWS
    recv (m_sock, buf, len, 0 );
#else
    read ( m_sock, buf, len );
#endif

    return buf;

}

std::string CoreSocket::Read ( int len ) const
{
    CoreAssert ( m_sock != NULL );

    char *buf = new char[len];
    std::string ret;

#ifdef TARGET_OS_WINDOWS
    recv (m_sock, buf, len, 0 );
#else
    read ( m_sock, buf, len );
#endif

    ret = std::string ( buf );

    delete [] buf;

    return ret;
}

std::string CoreSocket::ReadLine () const
{
    CoreAssert ( m_sock != NULL );

    const char *current;
    char line[8192];
    std::string retval;

    do {

        current = this->Internal_Read(1);

        if ( *current != '\n' && *current != '\r')
            strcat ( line, current );

        delete [] current;

    } while ( *current != '\n' && *current != '\r');

    retval = std::string ( line );

    return retval;
}

int CoreSocket::Send ( const char *_packet, size_t _length )
{
    CoreAssert ( m_sock != NULL );

    int n = 0, sent = 0;
    sent = send ( m_sock, _packet, (int)_length, 0 );
    return sent;
}

int CoreSocket::Send ( std::string _packet )
{
    CoreAssert ( m_sock != NULL );

    int n = 0, sent = 0;
    sent = send ( m_sock, _packet.c_str(), (int)_packet.size(), 0 );
    return sent;
}