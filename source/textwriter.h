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
	
#ifndef __included_textwriter_h
#define __included_textwriter_h

#include "core_exception.h"
	
//! The text file output class.
/*!
	Inherits CoreIO, so functions like CoreIO::Write and CoreIO::WriteLine are accessible to the programmer.
*/ 
class TextWriter : public CoreIO 
{

protected:
	//! The path to the file being written. 
	const char *m_filePath;

public:
	//! The constructor.
	/*!
		Creates an instance of CoreIO with write access to the file specified in _file.
		\param _file The path to the file being read.
		*/ 
	TextWriter ( const char *_file );

	//! The destructor
	/*!
		Flushes the output buffer, closes the file, and deallocates memory used by TextWriter.
		*/ 
	~TextWriter (  );

private:
	bool EndOfFile (  )
		{ throw new InvalidCallException(); };
	unsigned long Length (  )
		{ throw new InvalidCallException(); };
	char Read (  )
		{ throw new InvalidCallException(); };
	size_t Read ( char *_buffer, int _bufferLength, int _bufferIndex, int _count )
		{ throw new InvalidCallException(); };
	const char *ReadLine (  )
		{ throw new InvalidCallException(); };
	int Seek ( int _position )
		{ throw new InvalidCallException(); };
	int Forward ( int _position )
		{ throw new InvalidCallException(); };

};

#endif
