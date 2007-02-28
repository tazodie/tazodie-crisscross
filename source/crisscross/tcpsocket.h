/*
 *
 *                               C R I S S C R O S S _ N E T
 *                           A cross platform networking library.
 *                              formerly Codename "Rivendell"
 *                             project started August 30, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
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

#ifndef __included_tcpsocket_h
#define __included_tcpsocket_h

#include <crisscross/core_socket.h>

namespace CrissCross
{
    namespace Network
    {
        //! TCP/IP socket class.
        /*!
            Used for two-way TCP/IP communication.
         */
        class TCPSocket : public CoreSocket
        {
        private:
            int SetAttributes ( socket_t _socket );
        public:
            //! The default constructor.
            TCPSocket ();
            //! The constructor for existing sockets.
            TCPSocket ( socket_t _socket );
            //! The destructor.
            ~TCPSocket ();

            //! Accepts an incoming connection. Only good when listening for a connection.
            /*!
		\param _socket A pointer to a NULL TCPSocket pointer variable. (e.g. TCPSocket *blah = NULL; socket->Accept ( &blah ); ) 
                \return A pointer to a newly created TCPSocket instance for the new
                connection. If no incoming connections are pending, this returns NULL.
             */
            CrissCross::Errors Accept( TCPSocket **_socket );

            //! Establishes an outbound connection to the specified address and port.
            /*!
                \param _address The remote address to connect to. Can be a hostname, as it will be resolved by gethostbyname().
                \param _port The remote port to connect to.
             */
			CrissCross::Errors Connect ( const char *_address, unsigned short _port );

            //! Listens for connections on the specified port.
            /*!
                You need to Accept() connections after calling this.
                \param _port The local port to listen on.
             */
			CrissCross::Errors Listen ( unsigned short _port );

        };
    }
}

#endif
