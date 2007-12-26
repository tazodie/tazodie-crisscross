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

#ifndef __included_cc_textreader_h
#define __included_cc_textreader_h

#include <crisscross/error.h>
   
namespace CrissCross
{
    namespace IO
    {
        //! The text file input class.
        /*!
            Inherits CoreIO, so functions like CoreIO::Read and CoreIO::ReadLine are accessible to the programmer.
        */ 
        class TextReader : public CoreIOReader
        {

        protected:
            //! The path to the file being read.
            const char *m_filePath;

        public:
            //! The constructor.
            TextReader ();

            //! The destructor
            /*!
                Closes the file and deallocates memory used by TextReader.
             */ 
            ~TextReader ();

            //! Opens the provided file for read access.
            /*!
                \param _file The path of the file to be read.
                \return Standard CrissCross::Errors values.
             */ 
            CrissCross::Errors Open ( const char *_file );

            //! Closes the file.
            /*!
                Closes the file and deallocates memory used by TextReader.
                \return Standard CrissCross::Errors values.
             */ 
            CrissCross::Errors Close ();

        };
    }
}

#endif
