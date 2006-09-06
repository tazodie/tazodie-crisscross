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
#include "core_network.h"
#include "core_socket.h"

using namespace CrissCross::Network;

CoreSocket::CoreSocket()
{
    __initialise_network();
    memset ( &m_sock, 0, sizeof ( socket_t ) );
}

CoreSocket::~CoreSocket()
{
#ifdef TARGET_OS_WINDOWS
    closesocket ( m_sock );
#else
    close ( m_sock );
#endif
    __cleanup_network();
}

void CoreSocket::Connect ( const char *_address, unsigned short _port )
{
    struct sockaddr_in sin;
    struct hostent *host;

    m_sock = socket ( AF_INET, SOCK_STREAM, 0 );

    host = gethostbyname ( _address );

    memset ( &sin, 0, sizeof ( sin ) );
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ( ( struct in_addr * ) ( host->h_addr ) )->s_addr;
    sin.sin_port = htons ( _port );

    if ( connect ( m_sock, ( ( struct sockaddr * ) &sin ), sizeof ( sin ) ) < 0 )
    {
#ifdef TARGET_OS_WINDOWS
        closesocket ( m_sock );
#else
        close ( m_sock );
#endif
    }
}

std::string CoreSocket::Read ( int len ) const
{
    char *buf = new char[len];
    std::string ret;
#ifdef TARGET_OS_WINDOWS 
    recv (m_sock, buf, len, 0 );
#else
    read ( m_sock, buf, len );
#endif
    
    ret = std::string(buf);

    delete [] buf;

    return ret;

}

std::string CoreSocket::ReadLine () const
{
    const char *current;
    char line[8192];
    std::string retval;

    do {
        current = this->Read(1).c_str();

        if ( *current != '\n' && *current != '\r')
            strcat ( line, current );
    } while ( *current != '\n' && *current != '\r');

    retval = std::string ( line );

    return retval;
}

bool CoreSocket::Send ( const char *_packet, size_t _length )
{
    int n = 0, sent = 0;
    send ( m_sock, _packet, (int)_length, 0 );
    return sent > 0;
}

bool CoreSocket::Send ( std::string _packet )
{
    int n = 0, sent = 0;
    send ( m_sock, _packet.c_str(), (int)_packet.size(), 0 );
    return sent > 0;
}

#if 0

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#ifdef __WIN32__
# include <winsock.h>
#else
# include <sys/param.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#endif

#include <fcntl.h>
#include <unistd.h>
#include "Socket.h"

using namespace Warlock;

Socket::Socket(const char *server, int port)
{
    struct sockaddr_in sin;
    struct hostent *host;
    int opt;
    //socket_t sock;

#ifdef __WIN32__
    WORD version = MAKEWORD(1,1);
    WSADATA wsaData;

    WSAStartup(version, &wsaData);
#endif

    sock = socket(AF_INET, SOCK_STREAM, 0);

    host = gethostbyname(server);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
    sin.sin_port = htons(port);

    if ( connect(sock, ((struct sockaddr *)&sin), sizeof(sin)) < 0 )
    {
#ifdef __WIN32__
    closesocket(sock);
#else
        close(sock);
#endif
    }

}

char* Socket::Read(int len)
{
    char *buf = new char[len];
#ifdef __WIN32__ 
    recv(sock, buf, len, 0);
#else
    read(sock, buf, len);
#endif

    /*if (n == 0) return -1;
    if (n == -1 && errno == EWOULDBLOCK) return 0;*/
  
return buf;

}

string Socket::ReadLine ()
{
    char *current;
    string line;

    do {
        current = this->Read(1);

        if ( *current != '\n' && *current != '\r')
            line += current;
    } while ( *current != '\n' && *current != '\r');

    return line;
}

bool Socket::Write(char *data)
{
    int n = 0, sent = 0;
    int len = strlen(data) + 1;
    
    /*do
    {
        n = send(sock, data+sent, len-sent, 0);
        if (n == 0) return -1;
        if (n == -1)
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN) continue;
            return -1;
        }
        sent += n;
    }
    while (sent != len);*/

    send(this->sock, data, len, 0);
    return sent > 0;
}

/*bool Socket::Write(string data)
{
    cout << "Writing " << data.c_str() << " to socket";
    return this->Write(data.c_str());
}*/
#endif
