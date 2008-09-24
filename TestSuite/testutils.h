/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_testutils_h
#define __included_testutils_h

#include <crisscross/console.h>

extern CrissCross::IO::Console *g_console;

void WritePrefix(const char *_prefix);
int WriteResult(int _result);
char *newStr(const char *_string);

#endif
