/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2007 Steven Noonan.
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
			char buffer[10240]; \
			sprintf ( buffer, "\nAssertion failed : '%s'\nFile: %s\nLine: %d\n\n", \
			#x, __FILE__, __LINE__ ); \
			fprintf ( stderr, "%s", buffer ); \
			fprintf ( stderr, "=== STACK TRACE ===\n" ); \
			CrissCross::IO::CoreIOWriter *stderror = \
				new	CrissCross::IO::CoreIOWriter ( stderr, false, CrissCross::IO::CC_LN_LF ); \
			PrintStackTrace ( stderror ); \
			delete stderror; \
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
