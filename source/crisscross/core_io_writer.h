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

#ifndef __included_core_io_writer_h
#define __included_core_io_writer_h

#include <crisscross/core_error.h>
#include <crisscross/core_mutex.h>
#include <crisscross/core_io.h>

namespace CrissCross
{
    namespace IO
    {
        //! The core output class.
        /*!
            A class inherited by most I/O classes, including CoreConsole and TextWriter.
        */
        class CoreIOWriter
        {
          protected:

            //! Line ending buffer.
            /*!
               Stores the line ending selected by SetLineEndings.
             */
            char *m_lineEnding;

            //! Input/output buffer.
            FILE *m_fileBuffer;

            //! Indicates whether the buffer is to be written in unicode or not. (UNIMPLEMENTED)
            bool m_unicode;

        #ifndef TARGET_COMPILER_GCC
            //! Thread-safe mutex.
            /*!
               Prevents more than one read or write from occurring simultaneously.
             */
            CrissCross::System::CoreMutex *m_ioMutex;
        #endif

          public:
            //! The constructor.
            /*!
               Creates a new CoreIOWriter instance. Will initialize line endings to the platform's
               default, also initializes CoreIOWriter::m_ioMutex.
               \param _outputBuffer The buffer to be used for write operations.
               \param _isUnicode The buffer is going to be a Unicode I/O buffer. (UNIMPLEMENTED)
               \param _lnEnding The line ending to use.
             */
            CoreIOWriter ( FILE * _outputBuffer, bool _isUnicode, LineEndingType _lnEnding = CC_LN_NATIVE );

            //! The destructor.
            virtual ~CoreIOWriter ();

            //! Validates that the file buffer isn't NULL.
            /*!
               \return Boolean indicating whether the file is safe to write to.
             */
            virtual bool IsOpen ();

            //! Sets the line ending convention used by this CoreIOWriter instance.
            /*!
               \param _ending Any of the LineEndingType values.
             */
            virtual CrissCross::Errors SetLineEndings ( LineEndingType _ending );

            //! Writes a string to the buffer.
            /*!
               \param _format The format of the string to be written.
             */
            virtual CrissCross::Errors Write ( const char *_format, ... );

            //! Writes a string to the buffer.
            /*!
               \param _string The string to be written.
             */
            virtual CrissCross::Errors Write ( std::string _string );

            //! Writes an empty line to the buffer.
            /*!
               Writes CoreIOWriter::m_lineEnding to the buffer.
             */
            virtual CrissCross::Errors WriteLine ();

            //! Writes a string to the buffer with a newline appended.
            /*!
               Prints the string to the buffer, and then prints the line terminator in the
               format specified by CoreIOWriter::m_lineEnding.
               \param _format The format of the string to be written.
               \return Standard CrissCross::Errors values.
             */
            virtual CrissCross::Errors WriteLine ( const char *_format, ... );

            //! Writes a string to the buffer with a newline appended.
            /*!
               Prints the string to the buffer, and then prints the line terminator in the
               format specified by CoreIOWriter::m_lineEnding.
               \param _string The std::string to write.
               \return Standard CrissCross::Errors values.
             */
            virtual CrissCross::Errors WriteLine ( std::string _string );

            //! Flushes the output buffer.
            void Flush ();

        };
    }
}
#endif
