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
	
#ifndef __included_universal_include_h
#    define __included_universal_include_h
	
#    define APP_NAME        "CrissCross"
#    define APP_CODENAME    "Technetium"
#    define APP_VERSION     "private-0.3.0"
#    define APP_URL         "http://www.uplinklabs.net/crisscross/"
#    define APP_COPYRIGHT   "(c) 2006 by Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>"
#    define APP_COPYRIGHT_CONSOLE   "(c) 2006 by Steven Noonan <steven@uplinklabs.net>,\n" \
									"    Rudolf Olah <omouse@gmail.com>, and Miah Clayton <miah@io-in.com>"
	
#    define ENABLE_CPUID
#    define ENABLE_DEBUGLOG

//NOTE: By disabling this line, you will not be in compliance with article 2
//      of the BSD License. If you disable this line, you must display the
//      copyright notice in the program elsewhere.
#    define ENABLE_CREDITS
	
#    define DETECT_MEMORY_LEAKS
	
// ============================================================================
// Dont edit anything below this line   
// ============================================================================
	
#    define MAX_PROCESSORS 4

#    if defined ( _ARCH_PPC ) || defined ( __ppc__ ) || \
    defined ( __ppc64__ ) || defined ( __PPC ) || \
    defined ( powerpc ) || defined ( __PPC__ ) || \
    defined ( __powerpc64__ ) || defined ( __powerpc64 )
#        	if defined ( __ppc64__ ) || defined ( __powerpc64__ ) || defined ( __powerpc64 )
#        	define TARGET_CPU_PPC 64
#        	else
#        	define TARGET_CPU_PPC 32
#        	endif
#    endif
	
#    if defined ( __i386__ ) || defined ( __i386 ) || \
	defined ( i386 ) 
#        	define TARGET_CPU_X86
#    endif
	
#    if defined ( __alpha ) || defined ( __alpha__ )
#        	define TARGET_CPU_ALPHA
#    endif
	
#    if defined ( __x86_64__ ) || defined ( __x86_64 ) || \
	defined ( __amd64 ) || defined ( __amd64__ ) 
#        	define TARGET_CPU_X64
#    endif
	
#    if defined ( WIN32 ) || defined ( WIN64 )
#        	if defined ( WIN32 )
#        		define TARGET_CPU_X86
#        	elif defined ( WIN64 )
#        		define TARGET_CPU_X64
#        	endif
#        	define TARGET_OS_WINDOWS
#        	define _CRT_SECURE_NO_DEPRECATE
#    endif
	

#    ifdef _DEBUG
#        	define TARGET_DEBUG
#    endif
	
#    if defined ( __linux__ ) || defined ( linux ) || \
	defined ( __linux ) || defined ( __gnu_linux__ ) 
#        	define TARGET_OS_LINUX
#        	undef TARGET_OS_WINDOWS
#        	undef TARGET_OS_MACOSX
#        	undef DETECT_MEMORY_LEAKS
#    endif
	
#    if defined (__FreeBSD__)
#        	define TARGET_OS_FREEBSD
#    endif
	
#    if defined (__OpenBSD__)
#        	define TARGET_OS_OPENBSD
#    endif
	
#    if defined (__APPLE__) || defined (__MACH__)
#        	define TARGET_OS_MACOSX
#        	undef TARGET_OS_LINUX
#        	undef TARGET_OS_WINDOWS
#        	undef ENABLE_CPUID
#        	undef DETECT_MEMORY_LEAKS
#    endif
	
#    if !defined(TARGET_OS_WINDOWS) \
		&&!defined ( TARGET_OS_LINUX ) \
		&&!defined ( TARGET_OS_MACOSX ) 
#        error Compiling on an unsupported target. Cannot continue.
#    endif
	
#    ifdef TARGET_RELEASE
	
#    endif
	
#    if defined ( TARGET_DEBUG ) && defined ( TARGET_OS_WINDOWS ) && _MSC_VER >= 1300
#        	define ENABLE_SYMBOL_ENGINE
#    endif
	
#    if defined ( TARGET_OS_WINDOWS )
#			if _MSC_VER > 1200 && _MSC_VER < 1400
#				pragma warning ( disable : 4345 )
#				pragma warning ( disable : 4100 )
#				pragma warning ( disable : 4800 )
#			endif
#        	if defined ( DETECT_MEMORY_LEAKS )
#        		define _CRTDBG_MAP_ALLOC
#        	endif
#        	include <io.h>
#        	include <fcntl.h>
#        	include <windows.h>
#        	include <dbghelp.h>
#        	include <process.h>
#    else
#        	undef ENABLE_SYMBOL_ENGINE
#    endif
	
#    if defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX )
#           define ANSI_COLOUR
#           include <cxxabi.h>
#        	include <pthread.h>
#        	include <sys/types.h>
#           include <unistd.h>
#			include <sched.h>
#			include <ctype.h>
#    endif

#    if defined ( TARGET_OS_LINUX )
#           include <execinfo.h>
#endif

#    include <assert.h>
#    include <math.h>
#    include <memory.h>
#    include <stdarg.h>
#    include <stdio.h>
#    include <stdlib.h>
#    include <string.h>
	
#    if _MSC_VER < 1300 && defined ( TARGET_OS_WINDOWS )
#       include <xstring>
		typedef long intptr_t;
#    endif
#    include <iostream>
#    include <fstream>
#    include <sstream>
	
#    if defined ( TARGET_OS_WINDOWS )
#        	if defined ( DETECT_MEMORY_LEAKS )
#        		ifndef _DBG_NEW
#        			include <crtdbg.h>
	 inline void *
	 __operator_new ( size_t __n )
{
	
return::operator  new ( __n, _NORMAL_BLOCK, __FILE__, __LINE__ );

}

inline void *_cdecl operator
new ( size_t __n, const char *__fname, int __line )
{
	
return::operator  new ( __n, _NORMAL_BLOCK, __fname, __line );

}

inline void _cdecl operator
delete ( void *__p, const char *, int )
{
	
::operator  delete ( __p );

} 

#        			define _DBG_NEW new(__FILE__,__LINE__)
#        			define new _DBG_NEW
#        		endif
#        		undef THIS_FILE
static char THIS_FILE[] = __FILE__;


#        	endif
#        	include "win32_pthread_emulate.h"
#    endif

extern int RunApplication ( int argc, char **argv );

#endif
