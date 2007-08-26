/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/debug.h>
#include <crisscross/mutex.h>

namespace CrissCross
{
	namespace System
	{
		Mutex::Mutex ()
		{
		#ifdef TARGET_OS_WINDOWS
			InitializeCriticalSection(&m_criticalSection);
		#else
			int error = pthread_mutex_init(&m_hMutex, 0);
			CoreAssert ( error == 0 );
		#endif
		}

		Mutex::~Mutex ()
		{
			Unlock();
		#ifdef TARGET_OS_WINDOWS
			DeleteCriticalSection(&m_criticalSection);
		#else
			pthread_mutex_destroy(&m_hMutex);
		#endif
		}

		void
		Mutex::Lock ()
		{
		#ifdef TARGET_OS_WINDOWS
			EnterCriticalSection(&m_criticalSection);
		#else
			int error = pthread_mutex_lock(&m_hMutex);
			CoreAssert ( error == 0 );
		#endif
		}

		void
		Mutex::Unlock ()
		{
		#ifdef TARGET_OS_WINDOWS
			LeaveCriticalSection(&m_criticalSection);
		#else
			int error = pthread_mutex_unlock(&m_hMutex);
			CoreAssert ( error == 0 );
		#endif
		}
	}
}
