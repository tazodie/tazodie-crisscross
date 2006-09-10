/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
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

#ifndef __included_core_io_h
#define __included_core_io_h

#if defined ( WIN32 ) && _MSC_VER < 1300
#	include "universal_include.h"
#endif

#    include "core_mutex.h"

//! The core input/output class.
/*!
    An abstract class inherited by most I/O classes, including CoreConsole, TextReader
    and TextWriter. Programmers can write their own I/O classes which inherit CoreIO.
*/
namespace CrissCross
{
    namespace IO
    {
        class CoreIO
        {
          public:
            //! Line ending conventions.
            /*!
               An enumeration of different ending types.
             */
            enum LineEndingType
            {
                CR,                        /*!< Carriage return only. (default for UNIX and UNIX-like systems, Linux, AIX, Xenix, Mac OS X, BeOS, Amiga, RISC OS and others) */
                LF,                        /*!< Line feed only. (default for Commodore machines, Apple II family and Mac OS through version 9) */
                CRLF                    /*!< Carriage return and line feed. (default for CP/M, MP/M, DOS, Microsoft Windows) */
            };

          protected:

            //! Line ending buffer.
            /*!
               Stores the line ending selected by CoreIO::SetLineEndings.
             */
            char *m_lineEnding;

            //! Input/output buffer.
            FILE *m_fileBuffer;

        #ifndef __GNUC__
            //! Thread-safe mutex.
            /*!
               Prevents more than one read or write from occurring simultaneously.
             */
            CoreMutex *m_ioMutex;
        #endif

          public:
            //! The constructor.
            /*!
               Creates a new CoreIO instance. Will initialize line endings to the platform's
               default, also initializes CoreIO::m_ioMutex.
               \param _fileBuffer The buffer to be used for I/O operations.
             */
            CoreIO ( FILE * _fileBuffer );

            //! The destructor.
            virtual ~CoreIO ();

            //! Determines whether the end of the file has been reached.
            /*!
               \return Boolean indicating whether the end of the file has been reached.
             */
            virtual bool EndOfFile ();

            //! Determines the length of the file buffer.
            /*!
               \return An unsigned long indicating the length of the buffer in bytes.
             */
            virtual size_t Length ();

            //! Reads one byte from the file buffer.
            /*!
               \return A char containing the next byte from the buffer.
             */
            virtual char Read ();

            //! Reads a block of data from the file buffer.
            /*!
               \param _buffer The output buffer to read to.
               \param _bufferLength The size of _buffer (in bytes).
               \param _bufferIndex The position in _buffer to begin writing.
               \param _count The number of bytes to read.
             */
            virtual size_t Read ( char *_buffer, int _bufferLength, int _bufferIndex,
                          int _count );

            //! Reads a line of data.
            /*!
               Data returned by this function should be copied to another location before being parsed.
               <div style="color: #FF0000;"><b>WARNING:</b>
               This function is NOT thread-safe. A fix for this is in the works.
               </div>
               \return A pointer to the next line of data.
             */
            virtual std::string ReadLine ();

            //! Sets the line ending convention used by this CoreIO instance.
            /*!
               \param _ending Any of the CoreIO::LineEndingType values.
             */
            virtual void SetLineEndings ( LineEndingType _ending );

            //! Writes a string to the buffer.
            /*!
               \param _format The format of the string to be written.
             */
            virtual void Write ( const char *_format, ... );

            //! Writes a string to the buffer.
            /*!
               \param _string The string to be written.
             */
            virtual void Write ( std::string _string );

            //! Writes an empty line to the buffer.
            /*!
               Writes CoreIO::m_lineEnding to the buffer.
             */
            virtual void WriteLine ();

            //! Writes a string to the buffer with a newline appended.
            /*
               Prints the string to the buffer, and then prints the line terminator as specified in CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual void WriteLine ( const char *_format, ... );

            //! Writes a string to the buffer with a newline appended.
            /*
               Prints the string to the buffer, and then prints the line terminator as specified in CoreIO::m_lineEnding.
               \param _format The format of the string to be written.
             */
            virtual void WriteLine ( std::string _string );

            //! Seeks to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to the first byte of the buffer.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            virtual int Seek ( int _position );

            //! Moves forward to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to the current position in the buffer.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            virtual int Forward ( int _position );

          protected:
            //! Flushes the output buffer.
            void Flush ();

            //! Seeks to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to _origin.
               \param _origin Can be one of SEEK_SET, SEEK_CUR, or SEEK_END.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            int Seek ( int _position, int _origin );

        };
    }
}
#endif
