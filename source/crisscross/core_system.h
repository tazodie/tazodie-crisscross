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

#ifndef __included_core_system_h
#define __included_core_system_h

#include <crisscross/core_cpuid.h>

#    if defined ( TARGET_OS_WINDOWS )
#            include <windows.h>
#    elif defined ( TARGET_OS_MACOSX )
#            include <CoreServices/CoreServices.h>
#            include <mach/mach.h>
#            include <mach/mach_time.h>
#    elif defined ( TARGET_OS_LINUX )
#            include <sys/time.h>
#            include <sched.h>
#            include <time.h>
#    endif

namespace CrissCross
{
    namespace System
    {

        //! Sleeps the current thread for a specified time.
        /*!
           \param _msec Time to sleep for, in milliseconds.
         */
        void ThreadSleep ( int _msec );

        //! Generates a random number.
        /*!
           Don't forget to use SeedRandom() first!
           \sa SeedRandom()
         */
        int RandomNumber();

        //! Generates a random number.
        /*!
           Seeds the random number generator with the current time.
         */
        void SeedRandom ();

#if defined ( TARGET_OS_WINDOWS )
        //! Waits for the specified thread to finish executing.
        /*!
           \param _thread Thread to wait for.
           \param _timeout The maximum wait time. (currently ignored)
           \return Always zero, until _timeout is implemented.
         */
        int WaitForThread ( HANDLE _thread, DWORD _timeout );
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
        //! Waits for the specified thread to finish executing.
        /*!
           \param _thread Thread to wait for.
           \param _timeout The maximum wait time. (currently ignored)
           \return Always zero, until _timeout is implemented.
         */
        int WaitForThread ( pthread_t _thread, int _timeout );
#endif
    }
}
#endif
