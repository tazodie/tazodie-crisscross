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

#ifndef __included_core_socket_h
#define __included_core_socket_h

#include "core_network.h"

#include "datastructures/rbtree.h"

#ifdef TARGET_OS_WINDOWS
# include <winsock2.h>
# define socket_t SOCKET
#else
# define socket_t int
#endif

namespace CrissCross
{
    namespace Network
    {
        class CoreSocket
        {
        private:
            RedBlackTree<char*,u_long*> m_banned_hosts;
            char m_calledInitialise;
            socket_t m_sock;
            char *Internal_Read ( int _len ) const;
            int SetAttributes ( socket_t _socket );
        public:
            CoreSocket ();
            CoreSocket ( socket_t socket );
            ~CoreSocket ();

            CoreSocket *Accept ();
            int Ban ( unsigned long _host );
            bool IsBanned ( unsigned long _host ) const;
            int Close ();
            int Connect ( const char *_address, unsigned short _port );
            /* int State () const; */
            int Listen ( unsigned short _port );
            int Read ( char **_output, int _len ) const;
            int Read ( std::string &_output, int _len ) const;
            int Send ( const char *_packet, size_t _length );
            int Send ( std::string _packet );
            socket_t GetSocket ();

        };
    }
}

#endif
