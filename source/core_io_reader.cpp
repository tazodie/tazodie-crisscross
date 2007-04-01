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
#include <crisscross/core_io.h>
#include <crisscross/core_system.h>

using namespace CrissCross::IO;
using namespace CrissCross::System;

CoreIOReader::CoreIOReader ( FILE * _fileBuffer, bool _isUnicode, LineEndingType _lnEnding ):
m_fileInputPointer ( _fileBuffer ),
m_unicode ( _isUnicode )
#ifndef __GNUC__
, m_ioMutex ( new CoreMutex () )
#endif
{
    SetLineEndings ( _lnEnding );
}

CoreIOReader::~CoreIOReader ()
{
#ifndef __GNUC__
    delete m_ioMutex;
    m_ioMutex = NULL;
#endif
}

bool
CoreIOReader::EndOfFile ()
{
    CoreAssert ( this != NULL );

    if ( !m_fileInputPointer )
        return true;

    return ( feof ( m_fileInputPointer ) != 0 );
}

void
CoreIOReader::Flush ()
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    fflush ( m_fileInputPointer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
}

bool
CoreIOReader::IsOpen ()
{
    CoreAssert ( this != NULL );

    if ( m_fileInputPointer == NULL )
        return false;
	else
		return true;
}

int
CoreIOReader::Forward ( int _position )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    int res = Seek ( _position, SEEK_CUR );
    return ( res == 0 );
}

int
CoreIOReader::Length ()
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    fpos_t lastpos;
    fgetpos ( m_fileInputPointer, &lastpos );
    fseek ( m_fileInputPointer, 0, SEEK_END );
    fpos_t endpos;
    fgetpos ( m_fileInputPointer, &endpos );
    fsetpos ( m_fileInputPointer, &lastpos );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

#if defined ( TARGET_OS_WINDOWS ) || defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_FREEBSD ) || \
    defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD ) || defined ( TARGET_COMPILER_CYGWIN )
    return ( int ) endpos;
#elif defined ( TARGET_OS_LINUX )
    return ( int ) endpos.__pos;
#endif
}

int
CoreIOReader::Read ( char *_destination )
{
    CoreAssert ( this != NULL );
    CoreAssert ( _destination != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    *_destination = (char)fgetc ( m_fileInputPointer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return sizeof(char);
}

int
CoreIOReader::Read ( char *_buffer, int _bufferLength, int _bufferIndex,
               int _count )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    size_t retval;

    CoreAssert ( _buffer != NULL );
    CoreAssert ( _bufferLength - _bufferIndex < _count );
    CoreAssert ( _bufferIndex > 0 );
    CoreAssert ( _count > 0 );
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    retval = fread ( &_buffer[_bufferIndex], sizeof(char), _count, m_fileInputPointer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return (int)retval;
}

int
CoreIOReader::ReadLine ( char *_buffer, int _bufferLength )
{
	CoreAssert ( this != NULL );
	if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;
	
#ifndef __GNUC__
	m_ioMutex->Lock ();
#endif

	size_t bytesRead = 0, lineEndingSize = strlen(m_lineEnding);
	char c = '\x0';
		
	for ( char *bufptr = _buffer; (bufptr - _buffer) < _bufferLength; bufptr++ )
	{
		c = (char) fgetc ( m_fileInputPointer );
		
		if ( c == (char)EOF )
			break;
		bytesRead++;		
		
		*bufptr = c;
		
		if ( bytesRead >= lineEndingSize )
			if ( strncmp ( bufptr - (lineEndingSize - 1), m_lineEnding, lineEndingSize ) == 0 )
			{
				*(bufptr - (lineEndingSize - 1 )) = '\x0';
				break;
			}
	}

#ifndef __GNUC__
	m_ioMutex->Unlock ();
#endif

	return bytesRead;
}

int
CoreIOReader::ReadLine ( std::string &_string )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    char c = (char) fgetc ( m_fileInputPointer );

    if ( c == (char)EOF )
        return 0;

    static std::string buffer;

    while ( c != (char)EOF && c != '\n' )
    {
        buffer += c;
        c = (char)fgetc ( m_fileInputPointer );
    }

    int len = (int)buffer.length ();

    if ( len && buffer[len - 1] == '\r' )
        buffer.resize ( len - 1 );

#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

    _string = buffer;

    return (int)_string.length() * sizeof ( char );
}

int
CoreIOReader::Seek ( int _position, int _origin )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    int res = fseek ( m_fileInputPointer, _position, _origin );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return res;
}

int
CoreIOReader::Seek ( int _position )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    int res = Seek ( _position, SEEK_SET );

    return ( res == 0 );
}

CrissCross::Errors
CoreIOReader::SetLineEndings ( LineEndingType _ending )
{
    CoreAssert ( this != NULL );

	if ( _ending == CC_LN_NATIVE )
	{
#if defined ( TARGET_OS_WINDOWS )
		_ending = CC_LN_CRLF;
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
		_ending = CC_LN_LF;
#else
#		error You are not using a supported OS.
#endif
	}
    
    switch ( _ending )
    {
    case CC_LN_CR:
        sprintf ( m_lineEnding, "\r" );
        break;
    case CC_LN_LF:
        sprintf ( m_lineEnding, "\n" );
        break;
    case CC_LN_CRLF:
        sprintf ( m_lineEnding, "\r\n" );
        break;
    default:
        return CC_ERR_BADPARAMETER;
    }
	return CC_ERR_NONE;
}
