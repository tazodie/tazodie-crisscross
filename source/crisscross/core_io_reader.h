/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006 IO.IN Research
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

#ifndef __included_core_io_reader_h
#define __included_core_io_reader_h

#include <crisscross/core_error.h>
#include <crisscross/core_mutex.h>
#include <crisscross/core_io.h>

namespace CrissCross
{
    namespace IO
    {
        //! The core input class.
        /*!
            A class inherited by most I/O classes, including CoreConsole and TextReader.
        */
        class CoreIOReader
        {
          protected:

            //! Line ending buffer.
            /*!
               Stores the line ending selected by CoreIOReader::SetLineEndings.
             */
            char m_lineEnding[4];

            //! Input/output FILE pointer.
            FILE *m_fileInputPointer;

            //! Indicates whether the buffer is to be read in unicode or not. (UNIMPLEMENTED)
            bool m_unicode;

        #ifndef TARGET_COMPILER_GCC
            //! Thread-safe mutex.
            /*!
               Prevents more than one read from occurring simultaneously.
             */
            CrissCross::System::CoreMutex *m_ioMutex;
        #endif

          public:
            //! The constructor.
            /*!
               Creates a new CoreIOReader instance. Will initialize line endings to the platform's
               default, also initializes CoreIOReader::m_ioMutex.
               \param _inputBuffer The buffer to be used for read operations.
               \param _isUnicode The buffer is going to be a Unicode read buffer. (UNIMPLEMENTED)
               \param _lnEnding The line ending to use.
             */
            CoreIOReader ( FILE * _inputBuffer, bool _isUnicode, LineEndingType _lnEnding = CC_LN_NATIVE );

            //! The destructor.
            virtual ~CoreIOReader ();

            //! Determines whether the end of the file has been reached.
            /*!
               \return Boolean indicating whether the end of the file has been reached.
             */
            virtual bool EndOfFile ();

            //! Determines the length of the file buffer.
            /*!
               \return Indicates the length of the buffer in bytes.
             */
            virtual int Length ();

            //! Validates that the file buffer isn't NULL.
            /*!
               \return Boolean indicating whether the file is safe to read from.
             */
            virtual bool IsOpen ();

            //! Reads one character from the file buffer.
            /*!
               \param _destination A pointer to where the character can be stored.
               \return Number of total bytes read (this is here for future multibyte character support).
             */
            virtual int Read ( char *_destination );

            //! Reads a block of data from the file buffer.
            /*!
               \param _buffer The output buffer to read to.
               \param _bufferLength The size of _buffer (in bytes).
               \param _bufferIndex The position in _buffer to begin writing.
               \param _count The number of bytes to read.
               \return The actual number of bytes read.
             */
            virtual int Read ( char *_buffer, int _bufferLength, int _bufferIndex, int _count );

            //! Reads a line of data.
            /*!
               Data returned by this function should be copied to another location before being parsed.
               \param _string A reference of an std::string where the data will be stored.
               \return The number of bytes read.
             */
            virtual int ReadLine ( std::string &_string );

            //! Sets the line ending convention used by this CoreIOReader instance.
            /*!
               \param _ending Any of the LineEndingType values.
             */
            virtual CrissCross::Errors SetLineEndings ( LineEndingType _ending );

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

            //! Flushes the input buffer.
            void Flush ();

          protected:
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
