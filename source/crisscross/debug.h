/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_debug_h
#define __included_cc_debug_h

#include <crisscross/console.h>

#define USE_FAST_ASSERT

//! @cond

#ifndef USE_FAST_ASSERT

void Assert ( bool _condition, const char *_testcase, const char *_file,
              int _line );
#    define CoreAssert(x)       Assert((x), #x, __FILE__, __LINE__ )

#else

#	define CoreAssert(x) { \
		if ( !(x) ) { \
			g_stderr->WriteLine ( "\nAssertion failed : '%s'\nFile: %s\nLine: %d\n", \
			#x, __FILE__, __LINE__ ); \
			g_stderr->WriteLine ( "===== STACK TRACE =====" ); \
			PrintStackTrace ( g_stderr ); \
			abort(); \
		} \
	}

#endif
//! @endcond

//! Prints a stack trace to _outputBuffer.
/*!
    \param _outputBuffer The CoreIO output buffer to write to.
*/
void PrintStackTrace ( CrissCross::IO::CoreIOWriter * _outputBuffer );

extern CrissCross::IO::Console *g_stderr;
extern CrissCross::IO::Console *g_stdout;

#endif
