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

#include <crisscross/universal_include.h>
#include <crisscross/core_debug.h>
#include <crisscross/textreader.h>

using namespace CrissCross::IO;

TextReader::TextReader ():
CoreIOReader ( NULL, false ), m_filePath ( NULL )
{
}

TextReader::~TextReader ()
{
    Close ();
}

CrissCross::Errors TextReader::Open ( const char *_file )
{
	Close ();

    int _filePathLength = 0;

	if ( _file == NULL )
		return CC_ERR_BADPARAMETER;

	if ( ( _filePathLength = (int)strlen ( _file ) ) < 1 )
		return CC_ERR_BADPARAMETER;

    delete [] (char *) m_filePath;
    m_filePath = new char[_filePathLength + 1];
    strcpy ( (char *) m_filePath, _file );

    m_fileInputPointer = fopen ( m_filePath, "rt" );

    if ( m_fileInputPointer == NULL )
		return CC_ERR_FILE_OPEN;
	else
		return CC_ERR_NONE;
}

CrissCross::Errors TextReader::Close ()
{
	if ( m_fileInputPointer )
		fclose ( m_fileInputPointer );
	m_fileInputPointer = NULL;

	delete [] (char *)m_filePath;
	m_filePath = NULL;
	
	return CC_ERR_NONE;
}
