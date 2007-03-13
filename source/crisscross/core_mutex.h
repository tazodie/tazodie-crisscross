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

#ifndef __included_core_mutex_h
#define __included_core_mutex_h

#if defined ( WIN32 )
#	include <windows.h>
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
