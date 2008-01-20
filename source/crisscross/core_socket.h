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

#ifndef __included_cc_core_socket_h
#define __included_cc_core_socket_h

#ifndef __GNUC__
#include <crisscross/universal_include.h>
#endif

#include <crisscross/core_network.h>
#include <crisscross/rbtree.h>

//#define ENABLE_PROTECTION

#ifdef TARGET_OS_WINDOWS
# include <windows.h>
# define socket_t SOCKET
#else
# define socket_t int
#endif

/* We're leaving sockets unimplemented on the Nintendo DS for the moment. We
   need to familiarize ourselves with the devkitARM API for sockets first */
#if !defined ( TARGET_OS_NDSFIRMWARE )

namespace CrissCross
{
    namespace Network
    {
        //! Possible states of socket instances.
        typedef enum
        {
            SOCKET_STATE_UNKNOWN,           //!< The state has not yet been specified or is currently not known.
            SOCKET_STATE_NOT_CREATED,       //!< The socket is not yet instantiated.
            SOCKET_STATE_CLOSED,            //!< The socket is closed.
            SOCKET_STATE_LISTENING,         //!< The socket is listening for incoming connections (or data, if UDP).
            SOCKET_STATE_CONNECTED          //!< The socket is connected to a remote host.
        } socketState;

        //! Socket protocols.
        typedef enum
        {
            PROTOCOL_NONE,                          //!< No protocol specified.
            PROTOCOL_TCP,                            //!< Transmission Control Protocol.
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
            //! A #include of banned hosts.
            #include<char*,u_long*> m_banned_hosts;
#endif

            //! The maximum number of bytes to read per CoreSocket::Read or CoreSocket::ReadLine call.
            int m_bufferSize;

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
                \return CC_ERR_NONE if no error is encountered, otherwise returns 'errno'.
             */
            virtual int SetAttributes ( socket_t _socket ) = 0;
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
                \return Currently always returns CC_ERR_NONE.
             */
            CrissCross::Errors Ban ( unsigned long _host );

            //! Close the socket.
            /*!
                Doesn't need to be called before an instance is destructed, because
                it is automatically called in the destructor.
                \return Currently always returns CC_ERR_NONE.
             */
            virtual CrissCross::Errors Close ();

            //! Get the error value for the socket.
            /*!
                \return The error value for the socket.
             */
            virtual CrissCross::Errors GetError();

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

            //! Fetches the IP address of the remote host.
            /*!
                \return The host represented in old-style sockaddr_in format.
             */
            u_long GetLocalHost ();

            //! Fetches the IP address of the remote host.
            /*!
                \return A pointer to the IP address string in dot notation. Note that the
                pointer this returns will be reused on the next GetRemoteIP call, so the
                data pointed at by the return value should be copied into another buffer.
             */
            const char *GetLocalIP ();

            //! Gives access to the socket itself (for extensibility only).
            /*!
                \return CoreSocket::m_sock
             */
            socket_t GetSocket ();

            //! Indicates whether the specified host is banned or not.
            /*!
                \param _host The host to ban (retrieve this with GetRemoteHost()).
                \return True or false, depending on whether the host is banned or not.
             */
            bool IsBanned ( unsigned long _host ) const;

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
            virtual CrissCross::Errors Listen ( unsigned short _port ) = 0;

            //! Reads a block of data with a specified maximum size.
            /*!
                \param _output A buffer with size _len. Will contain the received
                data on return.
                \param _len The maximum number of bytes to read. On return, this
                will contain the size of data received.
                \return  If the return value is greater than zero, it is an 'errno'
                value. If it is less than zero, it is a socketError value.
             */
            virtual int Read ( char *_output, unsigned int *_len );

            //! Reads a block of data with a specified maximum size.
            /*!
                \param _output An std::string in which the data will be stored.
                \return  If the return value is greater than zero, it is an 'errno'
                value. If it is less than zero, it is a socketError value.
             */
            virtual int Read ( std::string &_output );

            //! Sends a block of data.
            /*!
                \param _data The data to be sent.
                \param _length The number of bytes of _data to send (must NOT exceed the size of _data).
                \return The actual number of bytes sent.
             */
            virtual int Send ( const void *_data, size_t _length );
            
            //! Sends a string.
            /*!
                \param _data The string to be sent.
                \return The actual number of bytes sent.
             */
            virtual int Send ( std::string _data );

        };
    }
}

#endif

#endif
