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

//#define ENABLE_PROTECTION

#ifdef TARGET_OS_WINDOWS
# include <windows.h>
# define socket_t SOCKET
#else
# define socket_t int
#endif

namespace CrissCross
{
    namespace Network
    {
        typedef enum
        {
            SOCKET_STATE_UNKNOWN,           //!< The state has not yet been specified or is currently not known.
            SOCKET_STATE_NOT_CREATED,       //!< The socket is not yet instantiated.
            SOCKET_STATE_CLOSED,            //!< The socket is closed.
            SOCKET_STATE_LISTENING,         //!< The socket is listening for incoming connections.
            SOCKET_STATE_CONNECTED          //!< The socket is connected to a remote host.
        } socketState;

        typedef enum
        {
            ERROR_CONNECT = -11,                    //!< The connect() call failed.
            ERROR_LISTEN = -10,                     //!< The listen() call failed.
            ERROR_BIND = -9,                        //!< The bind() call failed.
            ERROR_DNS = -8,                         //!< The host couldn't be resolved via DNS.
            ERROR_CREATE_SOCKET = -7,               //!< The socket() call failed.
            ERROR_SOCKET_IN_USE = -6,               //!< The socket is in use. The call being attempted is invalid for the current socketState.
            ERROR_SOCKET_NOT_INITIALISED = -5,      //!< The socket has not yet been initialised.
            ERROR_NOT_IMPLEMENTED = -4,             //!< The call has not yet been implemented or will not be implemented in the abstract class.
            ERROR_BAD_PARAMETER = -3,               //!< One of the parameters given was invalid.
            ERROR_NONE = 0                          //!< Success.
        } socketError;

        typedef enum
        {
            PROTOCOL_NONE,                          //!< No protocol specified.
            PROTOCOL_TCP,                           //!< Transmission Control Protocol.
            PROTOCOL_UDP                            //!< User Datagram Protocol.
        } socketProtocol;

        //! The abstract core socket class.
        /*!
            Abstract class only. Must be inherited.
         */
        class CoreSocket
        {
        protected:
#if defined ( ENABLE_PROTECTION )
            //! A RedBlackTree of banned hosts.
            RedBlackTree<char*,u_long*> m_banned_hosts;
#endif
            //! Indicates whether __socket_initialise() was called when the class was initialized.
            char m_calledInitialise;

            //! Stores the socket data.
            socket_t m_sock;

            //! Indicates the protocol used by this socket instance.
            socketProtocol m_proto;

            //! Indicates the current state of m_sock.
            socketState m_state;

            //! Sets some important attributes on the socket.
            /*!
                Will set SO_LINGER and TCP_NODELAY on TCP sockets.
                \param _socket The socket to modify.
                \return ERROR_NONE if no error is encountered, otherwise returns 'errno'.
             */
            int SetAttributes ( socket_t _socket );
        public:

            //! The default constructor.
            CoreSocket ();

            //! The constructor for an existing socket.
            CoreSocket ( socket_t socket );

            //! The destructor.
            virtual ~CoreSocket ();

            //! Will add a host to the banned hosts list.
            /*!
                Doing this, when ENABLE_PROTECTION is defined will prevent the banned
                host from connecting (or, if the instance is a non-streaming socket,
                ignore data sent by the host).
                \param _host The host to ban (retrieve this with GetRemoteHost()).
                \return Currently always returns ERROR_NONE.
             */
            int Ban ( unsigned long _host );

            //! Indicates whether the specified host is banned or not.
            /*!
                \param _host The host to ban (retrieve this with GetRemoteHost()).
                \return True or false, depending on whether the host is banned or not.
             */
            bool IsBanned ( unsigned long _host ) const;

            //! Fetches the IP address of the remote host.
            /*!
                \return The host represented in old-style sockaddr_in format.
             */
            u_long GetRemoteHost ();

            //! Fetches the IP address of the remote host.
            /*!
                \return A pointer to the IP address string in dot notation. Note that the
                pointer this returns will be reused on the next GetRemoteIP call, so the
                data pointed at by the return value should be copied into another buffer.
             */
            const char *GetRemoteIP ();

            //! Close the socket.
            /*!
                Doesn't need to be called before an instance is destructed, because
                it is automatically called in the destructor.
                \return Currently always returns ERROR_NONE.
             */
            virtual int Close ();

            //! Fetch the state of the socket.
            /*!
                \return The current state of m_sock.
                \sa CrissCross::Network::socketState
             */
            socketState State () const;

            //! Opens the port specified to listen for incoming connections.
            /*!
                \param _port The port to listen on.
                \return If the return value is greater than zero, it is an 'errno'
                value. If it is less than zero, it is a socketError value.
             */
            virtual int Listen ( unsigned short _port );

            //! Reads a block of data with a specified maximum size.
            /*!
                \param _output The address of a NULL char* pointer. The _output will
                point to the internal data buffer. The data in _output should be copied
                somewhereelse if it is needed longer than until the next
                Read(char**,int) call.
                \param _len The maximum number of bytes to read.
                \return  If the return value is greater than zero, it is an 'errno'
                value. If it is less than zero, it is a socketError value.
             */
            virtual int Read ( char **_output, unsigned int _len ) const;

            //! Reads a block of data with a specified maximum size.
            /*!
                \param _output An std::string in which the data will be stored.
                \param _len The maximum number of bytes to read.
                \return  If the return value is greater than zero, it is an 'errno'
                value. If it is less than zero, it is a socketError value.
             */
            virtual int Read ( std::string &_output, unsigned int _len ) const;

            //! Sends a block of data.
            /*!
                \param _data The data to be sent.
                \param _length The number of bytes of _data to send (must NOT exceed the size of _data).
                \return The actual number of bytes sent.
             */
            virtual int Send ( const char *_data, size_t _length );
            
            //! Sends a string.
            /*!
                \param _data The string to be sent.
                \return The actual number of bytes sent.
             */
            virtual int Send ( std::string _data );

            //! Gives access to the socket itself (for extensibility only).
            /*!
                \return CoreSocket::m_sock
             */
            socket_t GetSocket ();

        };
    }
}

#endif
