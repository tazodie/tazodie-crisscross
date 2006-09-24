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

#define PACKET_DEBUG
 
#include "universal_include.h"
#include "core_debug.h"
#include "core_network.h"
#include "core_socket.h"

#if !defined ( TARGET_OS_WINDOWS )
#    include <arpa/inet.h>
#    include <asm/ioctls.h>
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

CoreSocket::CoreSocket()
{
    __initialise_network(); m_calledInitialise = 1;
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
int
CoreSocket::Ban ( unsigned long _host )
{
#if defined ( ENABLE_PROTECTION )
    if ( m_banned_hosts.findNode ( &_host ) == NULL )
        m_banned_hosts.insert ( &_host, (char *)1 );
#endif
    return ERROR_NONE;
}

int
CoreSocket::Close()
{
#ifdef TARGET_OS_WINDOWS
    closesocket ( m_sock );
#else
    close ( m_sock );
#endif
    m_sock = 0;
    return ERROR_NONE;
}

const char *
CoreSocket::GetRemoteIP ()
{
    if ( m_sock == INVALID_SOCKET ) return NULL;

    static char buffer[15];
    struct sockaddr_in sock; int sock_size = sizeof(sock);
    memset ( &sock, 0, sizeof(sock) );
    getpeername ( m_sock, (sockaddr *)&sock, (socklen_t *)&sock_size );
    sprintf ( buffer, inet_ntoa ( sock.sin_addr ) );
    return buffer;
}

u_long
CoreSocket::GetRemoteHost ()
{
    if ( m_sock == INVALID_SOCKET ) return 0;

    struct sockaddr_in sock; int sock_size = sizeof(sock);
    memset ( &sock, 0, sizeof(sock) );
    getpeername ( m_sock, (sockaddr *)&sock, (socklen_t *)&sock_size );
    return sock.sin_addr.s_addr;
}

socket_t
CoreSocket::GetSocket()
{
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
CoreSocket::Listen ( unsigned short _port )
{
    /* CoreSocket::Listen does nothing. This is an abstract class. */
    return ERROR_NOT_IMPLEMENTED;
}

int
CoreSocket::Read ( std::string &_output ) const
{
    if ( m_sock == INVALID_SOCKET ) return ERROR_SOCKET_NOT_INITIALISED;

    char *buf = new char[m_bufferSize];
    memset ( buf, 0, m_bufferSize );
    int ret = 0, recvlen = 0;

    recvlen = recv ( m_sock, buf, m_bufferSize - 1, 0 );
    ret = errno;

    _output = std::string ( buf );

    delete [] buf;

    return ( recvlen == 0 ) ? ERROR_NONE : errno;
}

int
CoreSocket::Read ( char **_output, unsigned int *_len ) const
{
    if ( m_sock == INVALID_SOCKET ) return ERROR_SOCKET_NOT_INITIALISED;
    if ( _len == NULL ) return ERROR_BAD_PARAMETER;

    char *buf = new char[m_bufferSize];
    int ret = 0, recvlen = 0;
    memset ( buf, 0, m_bufferSize );

    recvlen = recv ( m_sock, buf, m_bufferSize - 1, 0 );
    if ( recvlen < 0 )
    {
        *_output = NULL;
        *_len = 0;
        delete [] buf;
        return ERROR_DATA_NOTAVAIL;
    }
    ret = errno;

    *_output = buf;
    *_len = recvlen;

    return ( recvlen == 0 ) ? ERROR_NONE : errno;
}

int
CoreSocket::ReadLine ( char **_output, unsigned int *_len ) const
{
    if ( m_sock == INVALID_SOCKET ) return ERROR_SOCKET_NOT_INITIALISED;
    if ( _len == NULL ) return ERROR_BAD_PARAMETER;
    char *buf = new char[m_bufferSize];
    char temp[2];
    int recvlen = 0;
    memset ( buf, 0, m_bufferSize );
    memset ( temp, 0, sizeof ( temp ) );

    recvlen = recv ( m_sock, temp, 1, 0 );
    if ( recvlen == 0 )
    {
        delete [] buf;
        return ERROR_DATA_NOTAVAIL;
    }
    if ( temp[0] == '\n' || temp[0] == '\r' )
    {
        *_output = buf;
        *_len = (unsigned int)strlen ( buf );
        return ERROR_NONE;
    } else {
        strcat ( buf, temp );
    }
    
    while ( true )
    {
        recvlen = recv ( m_sock, temp, 1, 0 );
        if ( recvlen > 0 )
        {
            if ( temp[0] == '\n' || temp[0] == '\r' )
            {
                *_output = buf;
                *_len = (unsigned int)strlen ( buf );
                break;
            } else {
                strcat ( buf, temp );
            }
        } else if ( recvlen < 0 ) {
            delete [] buf;
#if defined ( TARGET_OS_WINDOWS )
            if ( WSAGetLastError () == 10035 )
                return ERROR_DATA_NOTAVAIL;
            else
#endif
            {
                return ERROR_CONNECTIONLOST;
            }
        } else {
            fprintf ( stdout, "CoreSocket WARNING: Packet pipeline bubble!\n" );
        }
    }

    return ERROR_NONE;
}

int
CoreSocket::Send ( const char *_data, size_t _length )
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
    //fprintf ( stdout, "Writing packet: '%s'\n", temp_buf );
    delete [] temp_buf;
#endif
    sent = send ( m_sock, _data, (int)_length, 0 );
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
    //fprintf ( stdout, "Writing packet: '%s'\n", temp_buf );
    delete [] temp_buf;
#endif
    sent = send ( m_sock, _data.c_str(), (int)_data.size(), 0 );
    return sent;
}

int
CoreSocket::SetAttributes ( socket_t _socket )
{
    return ERROR_NOT_IMPLEMENTED;
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
