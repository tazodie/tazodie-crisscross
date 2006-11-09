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

#ifndef __included_core_io_h
#define __included_core_io_h

namespace CrissCross
{
    namespace IO
    {
		//! File write modes.
		/*!
		   Provides the choice of creating a file when opening it or appending to it.
	     */
        enum FileWriteMode
        {
			CC_FILE_CREATE,                   /*!< Default. Will create a new file if the one opened does not exist. */
            CC_FILE_APPEND                    /*!< Write operations will append data to the end of the file. */
        };
        
        //! Line ending conventions.
        /*!
           An enumeration of different ending types.
        */
        enum LineEndingType
        {
            CC_LN_NATIVE,                     /*!< Automatically selects the appropriate line ending for the running platform. */
            CC_LN_CR,                         /*!< Carriage return only. (default for Commodore machines, Apple II family and Mac OS through version 9) */
            CC_LN_LF,                         /*!< Line feed only. (default for UNIX and UNIX-like systems, Linux, AIX, Xenix, Mac OS X, BeOS, Amiga, RISC OS and others) */
            CC_LN_CRLF                        /*!< Carriage return and line feed. (default for CP/M, MP/M, DOS, OS/2, Microsoft Windows) */
        };
    }
}

#include <crisscross/core_io_reader.h>
#include <crisscross/core_io_writer.h>

#endif
