/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/stopwatch.h>

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
