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

#include "universal_include.h"

#include "core_system.h"

CoreSystem::CoreSystem ()
{
    InitTimer ();
}

CoreSystem::~CoreSystem ()
{
}

void
CoreSystem::InitTimer ()
{
#if defined ( TARGET_OS_WINDOWS )
    LARGE_INTEGER freq;

    QueryPerformanceFrequency ( &freq );
    m_tickInterval = 1.0 / ( double ) freq.QuadPart;
#elif defined ( TARGET_OS_MACOSX )
    mach_timebase_info ( &m_timebase );
    m_start = mach_absolute_time ();
#elif defined ( TARGET_OS_LINUX )
    gettimeofday ( &m_start, NULL );
#endif
}

double
CoreSystem::GetHighResTime ()
{
#if defined ( TARGET_OS_WINDOWS )
    LARGE_INTEGER count;

    QueryPerformanceCounter ( &count );
    return ( double ) count.QuadPart * m_tickInterval;
#elif defined ( TARGET_OS_MACOSX )
    uint64_t elapsed = mach_absolute_time () - m_start;
    return double ( elapsed ) * ( m_timebase.numer / m_timebase.denom ) /
        1000000000.0;
#elif defined ( TARGET_OS_LINUX )
    timeval now;
    double t1, t2;

    gettimeofday ( &now, NULL );

    t1 = ( double ) m_start.tv_sec +
        ( double ) m_start.tv_usec / ( 1000 * 1000 );
    t2 = ( double ) now.tv_sec + ( double ) now.tv_usec / ( 1000 * 1000 );
    return t2 - t1;
#endif
}

void
CoreSystem::ThreadSleep ( int _msec )
{
    /* TODO: Linux and Mac OS X ports of this function. */
    /* NOTE: Linux uses usleep, which is slightly different. */
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
CoreSystem::WaitForThread ( HANDLE _thread, DWORD _timeout )
{
    WaitForSingleObject ( _thread, INFINITE );
    return 0;
}
#elif defined ( TARGET_OS_LINUX )
int
CoreSystem::WaitForThread ( pthread_t _thread, int _timeout )
{
    pthread_join ( _thread, NULL );
    return 0;
}
#endif
