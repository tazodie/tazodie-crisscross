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

#include <crisscross/universal_include.h>
#include <crisscross/debug.h>
#include <crisscross/textwriter.h>

namespace CrissCross
{
    namespace IO
    {
        TextWriter::TextWriter () : CoreIOWriter ( NULL, false ), m_filePath ( NULL )
        {
        }

        TextWriter::~TextWriter ()
        {
            Close ();
        }

        CrissCross::Errors TextWriter::Open ( const char *_file, FileWriteMode _writeMode, LineEndingType _lnEnding )
        {

            Close ();

            SetLineEndings ( _lnEnding );

            char openModes[4];

            int _filePathLength = 0;

            if ( _file == NULL )
                return CC_ERR_BADPARAMETER;

            if ( ( _filePathLength = (int)strlen ( _file ) ) < 1 )
                return CC_ERR_BADPARAMETER;

            delete [] (char *)m_filePath;
            m_filePath = new char[_filePathLength + 1];
            strcpy ( (char *)m_filePath, _file );

            sprintf ( openModes, "%s%s", ( _writeMode == CC_FILE_APPEND ? "a" : "w" ), "t" );
            m_fileOutputPointer = fopen ( m_filePath, openModes );

            if ( m_fileOutputPointer == NULL )
                return CC_ERR_FILE_OPEN;
            else
                return CC_ERR_NONE;
        }

        CrissCross::Errors TextWriter::Close ()
        {
            Flush ();

            if ( m_fileOutputPointer )
                fclose ( m_fileOutputPointer );

            m_fileOutputPointer = NULL;

            delete [] (char *)m_filePath;
            m_filePath = NULL;

            return CC_ERR_NONE;
        }
    }
}
