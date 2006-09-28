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

#ifndef __included_core_debug_h
#define __included_core_debug_h

#    include "core_console.h"

//! An assertion function.
/*!
    Will abort program execution if _condition is false.
    <div style="color: #FF0000;"><b>NOTE:</b>
        To know what line and file your code failed in, use the CoreAssert macro instead!
    </div>
    \param _condition The result of the condition tested.
    \param _testcase The condition that was validated.
    \param _file The file _testcase is in.
    \param _line The line in _file that _testcase is in.
    \sa CoreAssert
*/
void Assert ( bool _condition, const char *_testcase, const char *_file,
              int _line );

//! Prints a stack trace to _outputBuffer.
/*!
    \param _outputBuffer The CoreIO output buffer to write to.
*/
void PrintStackTrace ( CrissCross::IO::CoreIO * _outputBuffer );

//! An assertion macro.
/*!
    Will abort program execution if _condition is false. Also includes file and line numbers.
    \param x The condition to validate.
    \sa Assert
*/
#    define CoreAssert(x)       Assert((x), #x, __FILE__, __LINE__ )

extern CrissCross::IO::CoreConsole *g_stderr;
extern CrissCross::IO::CoreConsole *g_stdout;

#endif
