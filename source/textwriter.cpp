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
#include <crisscross/textwriter.h>

using namespace CrissCross::IO;

TextWriter::TextWriter ( bool _unicode ):
CoreIO ( NULL, _unicode ), m_filePath ( NULL )
{
}

TextWriter::~TextWriter ()
{
    Close ();
}

CrissCross::Errors TextWriter::Open ( CONST CHAR *_file, FileWriteMode _writeMode, CoreIO::LineEndingType _lnEnding )
{

	Close ();

	SetLineEndings ( _lnEnding );

	CHAR openModes[4];

    size_t _filePathLength = 0;

	if ( _file == NULL )
		return CC_ERR_BADPARAMETER;

	if ( ( _filePathLength = strlen ( _file ) ) < 1 )
		return CC_ERR_BADPARAMETER;

	delete [] (char *)m_filePath;
    m_filePath = new CHAR[_filePathLength + 1];
    strcpy ( (CHAR *) m_filePath, _file );

	sprintf ( openModes, "%s%s", ( _writeMode == CC_FILE_APPEND ? "a" : "w" ), "t" );
    m_fileBuffer = fopen ( m_filePath, openModes );

    if ( m_fileBuffer == NULL )
		return CC_ERR_FILE_OPEN;
	else
		return CC_ERR_NONE;
}

CrissCross::Errors TextWriter::Close ()
{
    Flush ();

	if ( m_fileBuffer )
		fclose ( m_fileBuffer );
	m_fileBuffer = NULL;

    delete [] (char *)m_filePath;
	m_filePath = NULL;

	return CC_ERR_NONE;
}
