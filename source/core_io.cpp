/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
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

#include "universal_include.h"

#include "core_debug.h"
#include "core_io.h"
#include "core_system.h"

CoreIO::CoreIO ( FILE *_fileBuffer ) :
	m_lineEnding ( NULL ),
	m_fileBuffer ( _fileBuffer ),
	m_ioMutex ( new CoreMutex() )
{
#if defined ( TARGET_OS_WINDOWS )
	SetLineEndings ( CRLF );
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX )
	SetLineEndings ( CR );
#endif
}

CoreIO::~CoreIO()
{
	delete [] m_lineEnding;
	m_lineEnding = NULL;
	delete m_ioMutex;
	m_ioMutex = NULL;
}

bool CoreIO::EndOfFile ()
{
	if ( !m_fileBuffer )
		return true;
	return ( feof ( m_fileBuffer ) != 0 );
}

void CoreIO::Flush ()
{
	m_ioMutex->Lock();
	fflush ( m_fileBuffer );
	m_ioMutex->Unlock();
}

int CoreIO::Forward ( int _position )
{
	int res = Seek ( _position, SEEK_CUR );
	return (res == 0);
}

unsigned long CoreIO::Length ()
{
	m_ioMutex->Lock();
	fpos_t lastpos;
	fgetpos ( m_fileBuffer, &lastpos );

	fseek ( m_fileBuffer, 0, SEEK_END );

	fpos_t endpos;
	fgetpos ( m_fileBuffer, &endpos );

	fsetpos ( m_fileBuffer, &lastpos );

	m_ioMutex->Unlock();
#if defined (TARGET_OS_WINDOWS) || defined (TARGET_OS_MACOSX)
	return (unsigned long)endpos;
#elif defined (TARGET_OS_LINUX)
	return (unsigned long)endpos.__pos;
#endif
}

char CoreIO::Read ()
{
	char retval;
	m_ioMutex->Lock();
	retval = (char)fgetc ( m_fileBuffer );
	m_ioMutex->Unlock();
	return retval;
}

size_t CoreIO::Read ( char *_buffer, int _bufferLength, int _bufferIndex, int _count )
{
	size_t retval;
	CoreAssert ( _buffer != NULL );
	CoreAssert ( _bufferLength - _bufferIndex < _count );
	CoreAssert ( _bufferIndex > 0 ); CoreAssert ( _count > 0 );
	m_ioMutex->Lock();
	retval = fread ( &_buffer[_bufferIndex], 1, _count, m_fileBuffer );
	m_ioMutex->Unlock();
	return retval;
}

const char *CoreIO::ReadLine ()
{
	m_ioMutex->Lock();
	char c = getc ( m_fileBuffer );

	if ( c == EOF )
		return NULL;

	static std::string buffer;

	buffer = "";

	while ( c != EOF && c != '\n' )
	{
		buffer += c;
		c = getc ( m_fileBuffer );
	}

	size_t len = buffer.length();
	if ( len && buffer[len - 1] == '\r' )
		buffer.resize ( len - 1 );

	m_ioMutex->Unlock();
	return buffer.c_str();
}

int CoreIO::Seek ( int _position, int _origin )
{
	m_ioMutex->Lock();
	int res = fseek ( m_fileBuffer, _position, _origin );
	m_ioMutex->Unlock();
	return res;
}

int CoreIO::Seek ( int _position )
{
	int res = Seek ( _position, SEEK_SET );
	return (res == 0);
}

void CoreIO::SetLineEndings ( LineEndingType _ending )
{
	delete [] m_lineEnding;
	switch ( _ending )
	{
	case CR:
		m_lineEnding = new char[2];
		sprintf ( m_lineEnding, "\r" );
		break;
	case LF:
		m_lineEnding = new char[2];
		sprintf ( m_lineEnding, "\n" );
		break;
	case CRLF:
		m_lineEnding = new char[3];
		sprintf ( m_lineEnding, "\r\n" );
		break;
	default:
		CoreAssert ( 0 );
	}
}

void CoreIO::WriteLine ( const char *_format, ... )
{
	if ( _format == NULL )
		return;

	m_ioMutex->Lock();
	char *format_buffer = NULL;
	va_list args;
	va_start ( args, _format );

	CoreAssert ( _format != NULL );

	// Add our newline character to the format string
	format_buffer = new char[strlen(_format) + 2];
	CoreAssert ( format_buffer != NULL );

	strcpy ( format_buffer, _format );
	strcat ( format_buffer, "\n" );

	// Print out the string
	vfprintf ( m_fileBuffer, format_buffer, args );

	va_end ( args );

	delete [] format_buffer;
	m_ioMutex->Unlock();
}

void CoreIO::WriteLine ()
{
	m_ioMutex->Lock();
	fprintf ( m_fileBuffer, "\n" );
	m_ioMutex->Unlock();
}

void CoreIO::Write ( const char *_format, ... )
{

	if ( _format == NULL )
		return;
	m_ioMutex->Lock();

	va_list args;
	va_start ( args, _format );

	// Print out the string
	vfprintf ( m_fileBuffer, _format, args );

	va_end ( args );
	m_ioMutex->Unlock();
}
