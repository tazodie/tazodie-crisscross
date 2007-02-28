/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
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

CoreIOWriter::CoreIOWriter ( FILE * _fileBuffer, bool _isUnicode, LineEndingType _lnEnding ):
m_fileOutputPointer ( _fileBuffer ),
m_unicode ( _isUnicode )
#ifndef __GNUC__
, m_ioMutex ( new CoreMutex () )
#endif
{
	SetLineEndings ( _lnEnding );
}

CoreIOWriter::~CoreIOWriter ()
{
#ifndef __GNUC__
    delete m_ioMutex;
    m_ioMutex = NULL;
#endif
}

void
CoreIOWriter::Flush ()
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif
    fflush ( m_fileOutputPointer );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif
}

bool
CoreIOWriter::IsOpen ()
{
    CoreAssert ( this != NULL );

    if ( m_fileOutputPointer == NULL )
        return false;
	else
		return true;
}

CrissCross::Errors
CoreIOWriter::SetLineEndings ( LineEndingType _ending )
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

CrissCross::Errors
CoreIOWriter::WriteLine ( const char *_format, ... )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    if ( _format == NULL )
        return CC_ERR_BADPARAMETER;
#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    va_list args;

    va_start ( args, _format );

    // Print out the string
    vfprintf ( m_fileOutputPointer, _format, args );

    if ( fprintf ( m_fileOutputPointer, "%s", m_lineEnding ) < 0 )
		return CC_ERR_WRITE;

    va_end ( args );

#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

	return CC_ERR_NONE;
}

CrissCross::Errors
CoreIOWriter::WriteLine ( std::string _string )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;
    
    if ( _string.empty() == true )
        return CC_ERR_BADPARAMETER;

#ifndef __GNUC__        
    m_ioMutex->Lock ();
#endif
    
    if ( fprintf ( m_fileOutputPointer, "%s%s", _string.c_str(), m_lineEnding ) < 0 )
		return CC_ERR_WRITE;

#ifndef __GNUC__    
    m_ioMutex->Unlock ();
#endif

	return CC_ERR_NONE;
}

CrissCross::Errors
CoreIOWriter::Write ( std::string _string )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    if ( _string.empty() == true )
        return CC_ERR_BADPARAMETER;

#ifndef __GNUC__        
    m_ioMutex->Lock ();
#endif
    
    if ( fprintf ( m_fileOutputPointer, "%s", _string.c_str() ) < 0 )
		return CC_ERR_WRITE;

#ifndef __GNUC__    
    m_ioMutex->Unlock ();
#endif

	return CC_ERR_NONE;
}


CrissCross::Errors
CoreIOWriter::WriteLine ()
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    if ( fprintf ( m_fileOutputPointer, m_lineEnding ) < 0 )
	    return CC_ERR_WRITE;

#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

	return CC_ERR_NONE;
}

CrissCross::Errors
CoreIOWriter::Write ( const char *_format, ... )
{
    CoreAssert ( this != NULL );
    if ( !IsOpen() ) return CC_ERR_INVALID_BUFFER;

    if ( _format == NULL )
        return CC_ERR_BADPARAMETER;

#ifndef __GNUC__
    m_ioMutex->Lock ();
#endif

    va_list args;

    va_start ( args, _format );

    // Print out the string
    if ( vfprintf ( m_fileOutputPointer, _format, args ) < 0 )
		return CC_ERR_WRITE;

    va_end ( args );
#ifndef __GNUC__
    m_ioMutex->Unlock ();
#endif

	return CC_ERR_NONE;
}
