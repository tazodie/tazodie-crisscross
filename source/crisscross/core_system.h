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

#ifndef __included_core_system_h
#define __included_core_system_h

#    include "core_cpuid.h"

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