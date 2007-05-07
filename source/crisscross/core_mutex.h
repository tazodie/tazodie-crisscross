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

#ifndef __included_core_mutex_h
#define __included_core_mutex_h

#ifndef __GNUC__
#include <crisscross/universal_include.h>
#endif

#if defined ( TARGET_OS_WINDOWS )
#    include <windows.h>
#else
#    include <pthread.h>
#endif

namespace CrissCross
{
    namespace System
    {
        //! The safe threading mutex class.
        /*!
            Allows for safe threading by locking via thread ID.
        */
        class CoreMutex
        {
          protected:

        #    ifdef _WIN32
            //! The critical section for the mutex.
            /*!
               Windows uses "critical sections" for safe threading.
             */
            CRITICAL_SECTION m_criticalSection;
        #    else
            //! POSIX threading mutex.
            pthread_mutex_t m_hMutex;
        #    endif
          public:

            //! The constructor.
              CoreMutex ();

            //! The destructor.
             ~CoreMutex ();

            //! Locks the mutex.
            void Lock ();

            //! Unlocks the mutex.
            void Unlock ();

        };
    }
}
#endif
