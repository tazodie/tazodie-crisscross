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

#ifndef __included_crisscross_universal_include_h
#define __included_crisscross_universal_include_h
    
#    define CC_LIB_NAME                "CrissCross"

//#  define CC_LIB_CODENAME            "Technetium"    // v0.1.0 codename ( Milestone 1 )
//#  define CC_LIB_CODENAME            "Freya"         // v0.2.0 codename
//#  define CC_LIB_CODENAME            "Hodur"         // v0.3.0 codename
//#  define CC_LIB_CODENAME            "Baldur"        // v0.4.0 codename
//#  define CC_LIB_CODENAME            "Loki"          // v0.5.0 codename ( Milestone 2 )
#    define CC_LIB_CODENAME            "Ragnarok"      // v0.6.0 codename
//#  define CC_LIB_CODENAME            "Heimdall"      // v0.7.0 codename
//#  define CC_LIB_CODENAME            "Odin"          // v0.8.0 codename ( Milestone 3 )
//#  define CC_LIB_CODENAME            "Thor"          // v0.9.0 codename ( Milestone 4 )
//#  define CC_LIB_CODENAME            "Valhalla"      // v1.0.0 codename ( Milestone 5 )

#   define CC_LIB_VERSION             "0.5.9999.1-SVN"
#   define CC_LIB_BRANCH_AT_VERSION   "0.6.0"
#   define CC_LIB_URL                 "http://www.uplinklabs.net/crisscross/"
#   define CC_LIB_COPYRIGHT           "(c) 2006-2007 by IO.IN Research. Licensed under the New BSD License."

// Disabling these will save space.
//#   define ENABLE_CPUID
//#   define ENABLE_POSIX_THREADING

// Enables non-blocking sockets. This isn't finished yet, don't use it.
#   define ENABLE_NONBLOCKING

//NOTE: By disabling this line, you will not be in compliance with the New BSD License.
//      If you disable this line, you must display the copyright notice in the program
//      elsewhere.
#   define ENABLE_CREDITS

// Sorry, this is Windows-only... (Use Valgrind on Linux)
#   define DETECT_MEMORY_LEAKS

// Linux backtrace()
#   define ENABLE_BACKTRACE

// ============================================================================
// Dont edit anything below this line   
// ============================================================================

#    define MAX_PROCESSORS 8

#    include <crisscross/platform_detect.h>

// -----------------------
// RESULTANT CONFIGURATION
// -----------------------

#   if !defined ( PROCESSOR_DETECTED )
#       error "Could not detect target CPU."
#   endif

#   if !defined ( COMPILER_DETECTED )
#       error "Could not detect target compiler."
#   endif

#   if !defined ( OS_DETECTED )
#       error "Could not detect target OS."
#   endif

#   if !defined ( TARGET_COMPILER_VC )
#       undef DETECT_MEMORY_LEAKS
#   endif

// Doesn't work on non-x86, and Cygwin doesn't have the functionality for cpu_set_t.
#   if !defined ( TARGET_CPU_X86 ) || defined ( TARGET_COMPILER_CYGWIN ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD ) || defined ( TARGET_OS_MACOSX )
#       undef ENABLE_CPUID
#   endif
    
#    if defined ( TARGET_COMPILER_VC )
#		ifndef _CRT_SECURE_NO_DEPRECATE
#	       define _CRT_SECURE_NO_DEPRECATE
#		endif
#		ifndef _CRT_NONSTDC_NO_DEPRECATE
#	       define _CRT_NONSTDC_NO_DEPRECATE
#		endif
#       define ENABLE_SYMBOL_ENGINE
#    endif

#   include <sys/stat.h>
    
#   if defined ( TARGET_COMPILER_VC )
#       if _MSC_VER > 1200 && _MSC_VER < 1400
#           pragma warning ( disable : 4345 4100 4800 )
#       endif
#       if _MSC_VER <= 1100
#           undef DETECT_MEMORY_LEAKS
#       endif
#       if defined ( DETECT_MEMORY_LEAKS )
#           define _CRTDBG_MAP_ALLOC
#       endif
#       include <io.h>
#       include <fcntl.h>
#       include <windows.h>
#       if defined ( DETECT_MEMORY_LEAKS )
#           include <dbghelp.h>
#       endif
#       include <process.h>
#       include <shlobj.h>
#       define stat _stat
#       define strcasecmp stricmp
#   else
#       undef ENABLE_SYMBOL_ENGINE
#   endif
    
#   if defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
#       define ANSI_COLOUR
#       include <cxxabi.h>
#       include <pthread.h>
#       include <sys/types.h>
#       include <unistd.h>
#       include <errno.h>
#       include <sched.h>
#       include <ctype.h>
#    endif

#	if defined ( TARGET_OS_MACOSX )
#		include <Carbon/Carbon.h>
#	endif

#   if defined ( TARGET_COMPILER_CYGWIN )
#       undef ENABLE_BACKTRACE
#   endif

#   if defined ( TARGET_OS_LINUX ) && defined ( ENABLE_BACKTRACE )
#       include <execinfo.h>
#   endif

#    include <string.h>
#    include <assert.h>
#    include <math.h>
#    include <memory.h>
#    include <stdarg.h>
#    include <stdio.h>
#    include <stdlib.h>
#    if _MSC_VER < 1300 && defined ( TARGET_COMPILER_VC )
#       include <xstring>
        typedef long intptr_t;
#    endif
#    include <iostream>
#    include <istream>
#    include <fstream>
#    include <sstream>

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

#ifdef TARGET_OS_MACOSX
extern "C" {
	int CrissCrossInitialise ( int argc, char **argv );
}
#endif

#endif
