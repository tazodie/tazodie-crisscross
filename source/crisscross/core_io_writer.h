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

#ifndef __included_core_io_writer_h
#define __included_core_io_writer_h

#include <crisscross/error.h>
#include <crisscross/mutex.h>
#include <crisscross/core_io.h>

namespace CrissCross
{
    namespace IO
    {
        //! The core output class.
        /*!
            A class inherited by most I/O classes, including Console and TextWriter.
        */
        class CoreIOWriter
        {
          protected:

            //! Line ending buffer.
            /*!
               Stores the line ending selected by SetLineEndings.
             */
            char m_lineEnding[4];

            //! Input/output FILE pointer.
            FILE *m_fileOutputPointer;

            //! Indicates whether the buffer is to be written in unicode or not. (UNIMPLEMENTED)
            bool m_unicode;

        #ifndef TARGET_COMPILER_GCC
            //! Thread-safe mutex.
            /*!
               Prevents more than one read or write from occurring simultaneously.
             */
            CrissCross::System::Mutex m_ioMutex;
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
