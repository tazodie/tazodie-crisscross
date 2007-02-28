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

#ifndef __included_udpsocket_h
#define __included_udpsocket_h

#include <crisscross/core_error.h>
#include <crisscross/core_socket.h>

namespace CrissCross
{
    namespace Network
    {
        //! UDP/IP socket class.
        /*!
            Used for connectionless UDP/IP communication. Note that this is one-way,
            and there must be a second UDP/IP socket created for communication in
            the opposite direction.
         */
        class UDPSocket : public CoreSocket
        {
        public:
            //! The constructor.
            UDPSocket ();
            //! The destructor.
            ~UDPSocket ();

            //! Binds an outbound UDP/IP socket to the specified address and port.
            /*!
                \param _address The remote address to bind to. Can be a hostname, as it will be resolved by gethostbyname().
                \param _port The remote port to bind to.
                \return Due to the use of Berkley sockets, this returns zero on success, and a nonzero value on failure.
             */
            CrissCross::Errors Bind ( const char *_address, unsigned short _port );
            
            //! Binds an inbound UDP/IP socket on the specified port.
            /*!
                \param _port The port to bind.
                \return Due to the use of Berkley sockets, this returns zero on success, and a nonzero value on failure.
             */
            CrissCross::Errors Listen ( unsigned short _port );

        };
    }
}

#endif
