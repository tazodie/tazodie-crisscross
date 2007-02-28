/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
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

#include <crisscross/universal_include.h>

#include <crisscross/core_system.h>

namespace CrissCross
{
    namespace System
    {
    #if defined ( TARGET_OS_WINDOWS )

        //! The result of QueryPerformanceFrequency(). (Windows only)
        double __m_tickInterval;

    #elif defined ( TARGET_OS_MACOSX )

        //! The time index at which the timer started. ( Mac OS X only)
        uint64_t __m_start;

        //! The time base information. (Mac OS X only)
        mach_timebase_info_data_t __m_timebase;

    #elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )

        //! The time index at which the timer started. (Linux only)
        timeval __m_start;

    #endif

        void
        InitTimer ()
        {
    #if defined ( TARGET_OS_WINDOWS )
            LARGE_INTEGER freq;

            QueryPerformanceFrequency ( &freq );
            __m_tickInterval = 1.0 / ( double ) freq.QuadPart;
    #elif defined ( TARGET_OS_MACOSX )
            mach_timebase_info ( &__m_timebase );
            __m_start = mach_absolute_time ();
    #elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
            gettimeofday ( &__m_start, NULL );
    #endif
        }

        double
        GetHighResTime ()
        {
    #if defined ( TARGET_OS_WINDOWS )
            LARGE_INTEGER count;

            QueryPerformanceCounter ( &count );
            return ( double ) count.QuadPart * __m_tickInterval;
    #elif defined ( TARGET_OS_MACOSX )
            uint64_t elapsed = mach_absolute_time () - __m_start;
            return double ( elapsed ) * ( __m_timebase.numer / __m_timebase.denom ) /
                1000000000.0;
    #elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
            timeval now;
            double t1, t2;

            gettimeofday ( &now, NULL );

            t1 = ( double ) __m_start.tv_sec +
                ( double ) __m_start.tv_usec / ( 1000 * 1000 );
            t2 = ( double ) now.tv_sec + ( double ) now.tv_usec / ( 1000 * 1000 );
            return t2 - t1;
    #endif
        }

        void
        ThreadSleep ( int _msec )
        {
            /* TODO: Mac OS X port of this function. */
    #if defined ( TARGET_OS_WINDOWS )
            Sleep ( _msec );
    #elif defined ( TARGET_OS_LINUX )
            unsigned sleep_time = _msec * 1000;

            while ( sleep_time > 1000000 )
            {
                usleep ( 1000000 );
                sleep_time -= 1000000;
            }
            usleep ( sleep_time );
    #endif
        }

    #if defined ( TARGET_OS_WINDOWS )
        int
        WaitForThread ( HANDLE _thread, DWORD _timeout )
        {
            WaitForSingleObject ( _thread, INFINITE );
            return 0;
        }
    #elif defined ( TARGET_OS_LINUX )
        int
        WaitForThread ( pthread_t _thread, int _timeout )
        {
            pthread_join ( _thread, NULL );
            return 0;
        }
    #endif
        int
        RandomNumber()
        {
            return rand();
        }

        void
        SeedRandom()
        {
#if defined ( TARGET_OS_WINDOWS )
            srand ( GetTickCount() );
#else
            srand ( time(NULL) );
#endif
        }
    }
}
