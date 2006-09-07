/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
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

CoreIO::CoreIO ( FILE * _fileBuffer ):
m_lineEnding ( NULL ),
m_fileBuffer ( _fileBuffer )
#ifndef __GNUC__
, m_ioMutex ( new CoreMutex () )
#endif
{
#if defined ( TARGET_OS_WINDOWS )
    SetLineEndings ( CRLF );
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX )
    SetLineEndings ( LF );
#else
#    error You are not using a supported OS.
#endif
}

CoreIO::~CoreIO ()
{
    delete [] m_lineEnding;
    m_lineEnding = NULL;
#ifndef __GNUC__
    delete m_ioMutex;
    m_ioMutex = NULL;
#endif
}

bool
CoreIO::EndOfFile ()
{
    CoreAssert ( this != NULL );

    if ( !m_fileBuffer )
        return true;
    return ( feof ( m_fileBuffer ) != 0 );
}

void
CoreIO::Flush ()
{
    CoreAssert ( this != NULL );
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    fflush ( m_fileBuffer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
}

int
CoreIO::Forward ( int _position )
{
    CoreAssert ( this != NULL );
    int res = Seek ( _position, SEEK_CUR );
    return ( res == 0 );
}

size_t
CoreIO::Length ()
{
    CoreAssert ( this != NULL );
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

#if defined (TARGET_OS_WINDOWS) || defined (TARGET_OS_MACOSX) || defined (TARGET_OS_FREEBSD)
    return ( size_t ) endpos;
#elif defined (TARGET_OS_LINUX)
    return ( size_t ) endpos.__pos;
#endif
}

char
CoreIO::Read ()
{
    CoreAssert ( this != NULL );

    char retval;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    retval = ( char ) fgetc ( m_fileBuffer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return retval;
}

size_t
CoreIO::Read ( char *_buffer, int _bufferLength, int _bufferIndex,
               int _count )
{
    CoreAssert ( this != NULL );

    size_t retval;

    CoreAssert ( _buffer != NULL );
    CoreAssert ( _bufferLength - _bufferIndex < _count );
    CoreAssert ( _bufferIndex > 0 );
    CoreAssert ( _count > 0 );
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    retval = fread ( &_buffer[_bufferIndex], 1, _count, m_fileBuffer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
    return retval;
}

std::string
CoreIO::ReadLine ()
{
    CoreAssert ( this != NULL );

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    char c = ( char ) getc ( m_fileBuffer );

    if ( c == EOF )
        return NULL;

    static std::string buffer;

    buffer = "";

    while ( c != EOF && c != '\n' )
    {
        buffer += c;
        c = ( char ) getc ( m_fileBuffer );
    }

    size_t len = buffer.length ();

    if ( len && buffer[len - 1] == '\r' )
        buffer.resize ( len - 1 );

#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

    return buffer;
}

int
CoreIO::Seek ( int _position, int _origin )
{
    CoreAssert ( this != NULL );

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
CoreIO::Seek ( int _position )
{
    CoreAssert ( this != NULL );

    int res = Seek ( _position, SEEK_SET );

    return ( res == 0 );
}

void
CoreIO::SetLineEndings ( LineEndingType _ending )
{
    CoreAssert ( this != NULL );

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

void
CoreIO::WriteLine ( const char *_format, ... )
{
    CoreAssert ( this != NULL );

    if ( _format == NULL )
        return;
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    va_list args;

    va_start ( args, _format );

    // Print out the string
    vfprintf ( m_fileBuffer, _format, args );
    fprintf ( m_fileBuffer, m_lineEnding );

    va_end ( args );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

}

void
CoreIO::WriteLine ( std::string _string )
{
    CoreAssert ( this != NULL );
    
    if ( _string.empty() == true )
        return;

#ifndef __GNUC__        
    m_ioMutex->Lock ();
#endif
    
    fprintf ( m_fileBuffer, "%s%s", _string.c_str(), m_lineEnding );

#ifndef __GNUC__    
    m_ioMutex->Unlock ();
#endif

}

void
CoreIO::Write ( std::string _string )
{
    CoreAssert ( this != NULL );
    
    if ( _string.empty() == true )
        return;
#ifndef __GNUC__        
    m_ioMutex->Lock ();
#endif
    
    fprintf ( m_fileBuffer, "%s", _string.c_str() );

#ifndef __GNUC__    
    m_ioMutex->Unlock ();
#endif

}

void
CoreIO::WriteLine ()
{
    CoreAssert ( this != NULL );
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    fprintf ( m_fileBuffer, m_lineEnding );

#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
}

void
CoreIO::Write ( const char *_format, ... )
{
    CoreAssert ( this != NULL );

    if ( _format == NULL )
        return;
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    va_list args;

    va_start ( args, _format );

    // Print out the string
    vfprintf ( m_fileBuffer, _format, args );

    va_end ( args );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
}

