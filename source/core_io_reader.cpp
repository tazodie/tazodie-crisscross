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

#include <crisscross/universal_include.h>

#include <crisscross/core_debug.h>
#include <crisscross/core_io.h>
#include <crisscross/core_system.h>

using namespace CrissCross::IO;
using namespace CrissCross::System;

CoreIOReader::CoreIOReader ( FILE * _fileBuffer, bool _isUnicode, LineEndingType _lnEnding ):
m_lineEnding ( NULL ),
m_fileBuffer ( _fileBuffer ),
m_unicode ( _isUnicode )
#ifndef __GNUC__
, m_ioMutex ( new CoreMutex () )
#endif
{
	SetLineEndings ( _lnEnding );
}

CoreIOReader::~CoreIOReader ()
{
    delete [] m_lineEnding;
    m_lineEnding = NULL;
#ifndef __GNUC__
    delete m_ioMutex;
    m_ioMutex = NULL;
#endif
}

bool
CoreIOReader::EndOfFile ()
{
    CoreAssert ( this != NULL );

    if ( !m_fileBuffer )
        return true;

    return ( feof ( m_fileBuffer ) != 0 );
}

bool
CoreIOReader::IsOpen ()
{
    CoreAssert ( this != NULL );

    if ( m_fileBuffer == NULL )
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
    fgetpos ( m_fileBuffer, &lastpos );
    fseek ( m_fileBuffer, 0, SEEK_END );
    fpos_t endpos;
    fgetpos ( m_fileBuffer, &endpos );
    fsetpos ( m_fileBuffer, &lastpos );
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
    *_destination = (char)fgetc ( m_fileBuffer );
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
    retval = fread ( &_buffer[_bufferIndex], sizeof(char), _count, m_fileBuffer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return (int)retval;
}

int
CoreIOReader::ReadLine ( std::string &_string )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    char c = (char) fgetc ( m_fileBuffer );

    if ( c == (char)EOF )
        return 0;

    static std::string buffer;

    while ( c != (char)EOF && c != '\n' )
    {
        buffer += c;
        c = (char)fgetc ( m_fileBuffer );
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
    int res = fseek ( m_fileBuffer, _position, _origin );
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
        delete [] m_lineEnding;
        m_lineEnding = NULL;
        m_lineEnding = new char[2];
        sprintf ( m_lineEnding, "\r" );
        break;
    case CC_LN_LF:
        delete [] m_lineEnding;
        m_lineEnding = NULL;
        m_lineEnding = new char[2];
        sprintf ( m_lineEnding, "\n" );
        break;
    case CC_LN_CRLF:
        delete [] m_lineEnding;
        m_lineEnding = NULL;
        m_lineEnding = new char[3];
        sprintf ( m_lineEnding, "\r\n" );
        break;
    default:
        // Don't delete m_lineEnding, or else
        // it'll remain unassigned.
        return CC_ERR_BADPARAMETER;
    }
	return CC_ERR_NONE;
}
