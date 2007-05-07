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

#ifndef __included_textwriter_h
#define __included_textwriter_h

#include <crisscross/core_error.h>

namespace CrissCross
{
    namespace IO
    {
            
        //! The text file output class.
        /*!
            Inherits CoreIO, so functions like CoreIO::Write and CoreIO::WriteLine are accessible to the programmer.
        */
        class TextWriter : public CoreIOWriter
        {

        protected:
            //! The path to the file being written. 
            const char *m_filePath;

        public:
            //! The constructor.
            TextWriter ();

            //! The destructor
            /*!
                Flushes the output buffer, closes the file, and deallocates memory used by TextWriter.
                */ 
            ~TextWriter ();

            //! Opens the provided file.
            /*!
                Opens the file for reading.
                \param _file The path of the file to be read.
                \param _writeMode The mode with which to open the file.
                \param _lnEnding The line ending type to use.
                \return Standard CrissCross::Errors values.
             */ 
            CrissCross::Errors Open ( const char *_file, FileWriteMode _writeMode = CC_FILE_CREATE, LineEndingType _lnEnding = CC_LN_NATIVE );

            //! Closes the file.
            /*!
                Flushes the output buffer, closes the file, and deallocates memory used by TextWriter.
                \return Standard CrissCross::Errors values.
             */ 
            CrissCross::Errors Close ();
        };
    }
}
#endif
