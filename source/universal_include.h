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
#define __included_universal_include_h
    
#    define APP_NAME                "CrissCross"

//#  define APP_CODENAME            "Technetium"    // v0.1.0 codename ( Milestone 1 )
//#  define APP_CODENAME            "Freya"         // v0.2.0 codename
//#  define APP_CODENAME            "Hodur"         // v0.3.0 codename
//#  define APP_CODENAME            "Baldur"        // v0.4.0 codename
#    define APP_CODENAME            "Loki"          // v0.5.0 codename ( Milestone 2 )
//#  define APP_CODENAME            "Ragnarok"      // v0.6.0 codename
//#  define APP_CODENAME            "Heimdall"      // v0.7.0 codename
//#  define APP_CODENAME            "Odin"          // v0.8.0 codename ( Milestone 3 )
//#  define APP_CODENAME            "Thor"          // v0.9.0 codename ( Milestone 4 )
//#  define APP_CODENAME            "Valhalla"      // v1.0.0 codename ( Milestone 5 )

#    define APP_VERSION             "0.5.0-RC1"
#    define APP_BRANCH_AT_VERSION   "0.5.0"
#    define APP_URL                 "http://www.uplinklabs.net/crisscross/"
#    define APP_COPYRIGHT           "(c) 2006 by Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>, Miah Clayton <miah@io-in.com"
#    define APP_COPYRIGHT_CONSOLE   "(c) 2006 by Steven Noonan <steven@uplinklabs.net>,\n" \
                                    "    Rudolf Olah <omouse@gmail.com>, and Miah Clayton <miah@io-in.com>"

// Disabling these two will save space.
#    define ENABLE_CPUID
//#    define ENABLE_DEBUGLOG

// WARNING: Highly experimental. To be improved upon in 0.6.0 branch.
//#    define ENABLE_UNICODE

//NOTE: By disabling this line, you will not be in compliance with article 2
//      of the New BSD License. If you disable this line, you must display the
//      copyright notice in the program elsewhere.
#    define ENABLE_CREDITS

#    define DETECT_MEMORY_LEAKS

// ============================================================================
// Dont edit anything below this line   
// ============================================================================

#    define MAX_PROCESSORS 4

/*

Preprocessor Definitions
------------------------

TARGET_CPU_X86
    x86 processor
TARGET_CPU_X64
    64-bit processor
TARGET_CPU_PPC
    PowerPC processor
TARGET_CPU_ALPHA
    Alpha processor (not supported)

TARGET_OS_WINDOWS
    Windows
TARGET_OS_LINUX
    Linux
TARGET_OS_MACOSX
    Mac OS X
TARGET_OS_OPENBSD
    OpenBSD (not supported)
TARGET_OS_FREEBSD
    FreeBSD (not supported)

TARGET_COMPILER_GCC
    GNU C++ Compiler
TARGET_COMPILER_VC
    Visual C++
TARGET_COMPILER_ICC
    Intel C++ Compiler

 */

// -------------------
// PROCESSOR DETECTION
// -------------------

#   if defined ( _ARCH_PPC ) || defined ( __ppc__ ) || defined ( __ppc64__ ) || defined ( __PPC ) || defined ( powerpc ) || defined ( __PPC__ ) || defined ( __powerpc64__ ) || defined ( __powerpc64 )
#       if defined ( __ppc64__ ) || defined ( __powerpc64__ ) || defined ( __powerpc64 )
#           define TARGET_CPU_PPC 64
#       else
#           define TARGET_CPU_PPC 32
#       endif
#   endif
    
#   if defined ( __i386__ ) || defined ( __i386 ) || defined ( i386 ) || defined ( _X86_ ) || defined ( _WIN32 )
#       define TARGET_CPU_X86
#   endif
    
#   if defined ( __alpha ) || defined ( __alpha__ )
#       define TARGET_CPU_ALPHA
#   endif
    
#   if defined ( __x86_64__ ) || defined ( __x86_64 ) || defined ( __amd64 ) || defined ( __amd64__ ) || defined ( _IA64_ ) || defined ( _AMD64_ ) || defined ( _WIN64 )
#       define TARGET_CPU_X64
#   endif

// -------------------
// COMPILER DETECTION
// -------------------

#   if defined ( __GNUC__ ) || defined ( __CYGWIN__ ) || defined ( __CYGWIN32__ )
#       define TARGET_COMPILER_GCC
#   endif

#   if defined ( _MSC_VER )
#       define TARGET_COMPILER_VC
#   endif

#   if defined ( __INTEL_COMPILER )
#       define TARGET_COMPILER_ICC
#   endif
// ------------
// OS DETECTION
// ------------

#   if defined ( TARGET_COMPILER_VC ) || defined ( __CYGWIN__ )
#       define TARGET_OS_WINDOWS
#   endif
    
#   if defined ( __linux__ ) || defined ( linux ) || defined ( __linux ) || defined ( __gnu_linux__ )
#       define TARGET_OS_LINUX
#    endif
    
#   if defined (__FreeBSD__)
#       define TARGET_OS_FREEBSD
#   endif
    
#   if defined (__OpenBSD__)
#       define TARGET_OS_OPENBSD
#   endif
    
#   if defined (__APPLE__) || defined (__MACH__)
#       define TARGET_OS_MACOSX
#   endif

// -----------------------
// RESULTANT CONFIGURATION
// -----------------------

#   if !defined ( TARGET_COMPILER_VC )
#       undef DETECT_MEMORY_LEAKS
#   endif

#   if !defined ( TARGET_CPU_X86 )
#       undef ENABLE_CPUID
#   endif
   
#    if !defined(TARGET_OS_WINDOWS) && !defined ( TARGET_OS_LINUX ) && !defined ( TARGET_OS_MACOSX )
#       error Compiling on an unsupported target. Cannot continue.
#    endif

#    if ( defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_OS_MACOSX ) ) || \
        ( defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_OS_LINUX ) ) || \
        ( defined ( TARGET_OS_LINUX )   && defined ( TARGET_OS_MACOSX ) )
#       error Compilation detected multiple targets. Only select one.
#    endif
    
#    if defined ( TARGET_COMPILER_VC )
#       define ENABLE_SYMBOL_ENGINE
#    endif
    
#   if defined ( TARGET_COMPILER_VC )
#       define _CRT_SECURE_NO_DEPRECATE
#       define _CRT_NONSTDC_NO_DEPRECATE
#       if _MSC_VER > 1200 && _MSC_VER < 1400
#           pragma warning ( disable : 4345 4100 4800 )
#       endif
#       if defined ( DETECT_MEMORY_LEAKS )
#           define _CRTDBG_MAP_ALLOC
#       endif
#       include <io.h>
#       include <fcntl.h>
#       include <windows.h>
#       include <dbghelp.h>
#       include <process.h>
#       include <shlobj.h>
#       define stat _stat
#       define strcasecmp stricmp
#   else
#       undef ENABLE_SYMBOL_ENGINE
#   endif
    
#    if defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX )
#           define ANSI_COLOUR
#           include <cxxabi.h>
#           include <pthread.h>
#           include <sys/stat.h>
#           include <sys/types.h>
#           include <unistd.h>
#           include <errno.h>
#           include <sched.h>
#           include <ctype.h>
#    endif

#    if defined ( TARGET_OS_LINUX )
#           include <execinfo.h>
#    endif

#    if defined ( ENABLE_UNICODE )
#       include <wchar.h>
#    endif
#    include <assert.h>
#    include <math.h>
#    include <memory.h>
#    include <stdarg.h>
#    include <stdio.h>
#    include <stdlib.h>
#    include <string.h>
    
#    if _MSC_VER < 1300 && defined ( TARGET_COMPILER_VC )
#       include <xstring>
        typedef long intptr_t;
#    endif
#    include <iostream>
#    include <fstream>
#    include <sstream>

#ifndef CONST
#define CONST const
#endif

#ifndef CHAR
typedef char CHAR;
#endif

#ifndef WCHAR
typedef wchar_t WCHAR;
#endif

    
#    if defined ( TARGET_OS_WINDOWS )
#            if defined ( DETECT_MEMORY_LEAKS )
#                ifndef _DBG_NEW
#                    include <crtdbg.h>
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

#                    define _DBG_NEW new(__FILE__,__LINE__)
#                    define new _DBG_NEW
#                endif
#                undef THIS_FILE
static char THIS_FILE[] = __FILE__;


#            endif
#            include "win32_pthread_emulate.h"
#    endif

extern int RunApplication ( int argc, char **argv );

// Namespace Definitions
//! The CrissCross main namespace.
/*!
    All CrissCross classes and functions are kept in this namespace.
 */
namespace CrissCross
{
    //! The data structure namespace.
    /*!
        Contains basic data structures to assist in sorting and searching
        for data.
     */
    namespace Data
    {
        //! Data comparison namespace.
        /*!
            The functions contained here are designed to compare two items of a
            given data type. Return values are similar to those of strcmp().
         */
        namespace Comparison
        {
        }
    }

    //! The debug namespace.
    /*!
        Contains classes and functions designed to assist programmers
        in debugging their software.
     */
    namespace Debug
    {
    }

    //! The file system namespace.
    /*!
        This namespace is maintained by Rudolf Olah <omouse@gmail.com>
     */   
    namespace FileSystem
    {
    }

    //! The input/output namespace.
    /*!
        Contains classes for console and file I/O.
     */
    namespace IO
    {
    }
    
    //! The network communication class.
    /*!
        Contains classes which enable programmers to use TCP, UDP,
        and other network protocols to transfer data.
     */
    namespace Network
    {
    }

    //! The system call namespace.
    /*!
        Contains platform-specific API call wrappers, which allow the programmer
        to write code which is cross-platform and functions identically on all
        platforms.
     */
    namespace System
    {
    }
}

#endif
