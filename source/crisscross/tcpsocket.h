/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
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
            //! The default constructor (streaming socket).
            TCPSocket ();
            //! The constructor for existing sockets.
            TCPSocket ( bool _streamingSocket );
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
