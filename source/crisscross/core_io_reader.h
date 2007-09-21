/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_core_io_reader_h
#define __included_cc_core_io_reader_h

#include <crisscross/error.h>
#include <crisscross/mutex.h>
#include <crisscross/core_io.h>

namespace CrissCross
{
    namespace IO
    {
        //! The core input class.
        /*!
            A class inherited by most I/O classes, including Console and TextReader.
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
            CrissCross::System::Mutex m_ioMutex;
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
            virtual cc_int64_t Length ();

            //! Validates that the file buffer isn't NULL.
            /*!
               \return Boolean indicating whether the file is safe to read from.
             */
            virtual bool IsOpen ();

            //! Reads one character from the file buffer.
            /*!
               \param _destination A pointer to where the character can be stored.
               \return Number of total bytes read.
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
            virtual int Read ( char *_buffer, size_t _bufferLength, size_t _bufferIndex, size_t _count );

            //! Reads a line of data.
            /*!
               Data returned by this function should be copied to another location before being parsed.
               \param _string A reference of an std::string where the data will be stored.
               \return The number of bytes read.
             */
            virtual int ReadLine ( std::string &_string );

            //! Reads a line of data.
            /*!
               \param _buffer A character buffer for the data to be stored in.
               \param _bufferLength The length of the buffer specified in _buffer.
               \return The number of bytes read.
             */
            virtual int ReadLine ( char *_buffer, size_t _bufferLength );

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
            virtual int Seek ( cc_int64_t _position );

            //! Moves forward to a location in the buffer.
            /*!
               \param _position Position to seek to, relative to the current position in the buffer.
               \return An integer indicating the result of the operation. 0 indicates
               success. Any non-zero number indicates failure.
             */
            virtual int Forward ( cc_int64_t _position );

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
            int Seek ( cc_int64_t _position, int _origin );

        };
    }
}
#endif
