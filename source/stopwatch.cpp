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

#include "universal_include.h"
#include "stopwatch.h"

namespace CrissCross
{
    namespace System
    {
        Stopwatch::Stopwatch()
        {
        #if defined ( TARGET_OS_WINDOWS )
            LARGE_INTEGER freq;
            QueryPerformanceFrequency ( &freq );
            m_tickInterval = 1.0 / (double)freq.QuadPart;
        #elif defined ( TARGET_OS_MACOSX )
	        mach_timebase_info ( &m_timebase );
        #endif
        }

        Stopwatch::~Stopwatch()
        {
        }

        void Stopwatch::Start()
        {
#if defined ( TARGET_OS_WINDOWS )
            QueryPerformanceCounter ( &m_start );
#elif defined ( TARGET_OS_MACOSX )
	        m_start = mach_absolute_time ();
#elif defined ( TARGET_OS_LINUX )
            gettimeofday ( &m_start, NULL );
#endif
        }

        void Stopwatch::Stop()
        {
#if defined ( TARGET_OS_WINDOWS )
            QueryPerformanceCounter ( &m_finish );
#elif defined ( TARGET_OS_MACOSX )
	        m_finish = mach_absolute_time ();
#elif defined ( TARGET_OS_LINUX )
            gettimeofday ( &m_finish, NULL );
#endif
        }

        double Stopwatch::Elapsed()
        {
#if defined ( TARGET_OS_WINDOWS )
            return ( (double)m_finish.QuadPart - (double)m_start.QuadPart ) * m_tickInterval;
#elif defined ( TARGET_OS_MACOSX )
            uint64_t elapsed = m_finish - m_start;
            return double(elapsed) * ( m_timebase.numer / m_timebase.denom ) / 1000000000.0;
#elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_FREEBSD ) || defined ( TARGET_OS_NETBSD ) || defined ( TARGET_OS_OPENBSD )
            return (double)(m_finish.tv_sec - m_start.tv_sec) +
                ( (double)(m_finish.tv_usec) - (double)(m_start.tv_usec) ) / 1000000.0;
#endif
        }
    }
}
