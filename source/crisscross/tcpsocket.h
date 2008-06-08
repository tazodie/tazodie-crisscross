/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_tcpsocket_h
#define __included_cc_tcpsocket_h

#include <crisscross/core_socket.h>

/* We're leaving sockets unimplemented on the Nintendo DS for the moment. We
 * need to familiarize ourselves with the devkitARM API for sockets first */
#if !defined ( TARGET_OS_NDSFIRMWARE )

namespace CrissCross
{
	namespace Network
	{
		//! TCP/IP socket class.
		/*!
		 *  Used for two-way TCP/IP communication.
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
				 * \param _socket A pointer to a NULL TCPSocket pointer variable. (e.g. TCPSocket *blah = NULL; socket->Accept ( &blah ); )
				 * \return A pointer to a newly created TCPSocket instance for the new
				 *  connection. If no incoming connections are pending, this returns NULL.
				 */
				CrissCross::Errors Accept ( TCPSocket **_socket );

				//! Establishes an outbound connection to the specified address and port.
				/*!
				 * \param _address The remote address to connect to. Can be a hostname, as it will be resolved by gethostbyname().
				 * \param _port The remote port to connect to.
				 */
				CrissCross::Errors Connect ( const char *_address, unsigned short _port );

				//! Listens for connections on the specified port.
				/*!
				 *  You need to Accept() connections after calling this.
				 * \param _port The local port to listen on.
				 */
				CrissCross::Errors Listen ( unsigned short _port );

				//! In asynchronous sockets, this verifies that no state changes have occurred.
				/*!
				 * \sa State
				 */
				void UpdateState ();

				//! Fetch the state of the socket.
				/*!
				 * \return The current state of m_sock.
				 * \sa CrissCross::Network::socketState
				 */
				socketState State () const;
		};
	}
}

#endif

#endif
