/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#ifndef __included_core_debug_h
#define __included_core_debug_h

#    include <crisscross/core_console.h>

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
    \sa CoreAssert()
*/
void Assert ( bool _condition, const char *_testcase, const char *_file,
              int _line );

//! Prints a stack trace to _outputBuffer.
/*!
    \param _outputBuffer The CoreIO output buffer to write to.
*/
void PrintStackTrace ( CrissCross::IO::CoreIOWriter * _outputBuffer );

//! An assertion macro.
/*!
    Will abort program execution if _condition is false. Also includes file and line numbers.
    \param x The condition to validate.
    \sa Assert()
*/
#    define CoreAssert(x)       Assert((x), #x, __FILE__, __LINE__ )

extern CrissCross::IO::CoreConsole *g_stderr;
extern CrissCross::IO::CoreConsole *g_stdout;

#endif
