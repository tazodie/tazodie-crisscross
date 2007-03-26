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
