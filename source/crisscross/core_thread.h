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

#ifndef __included_core_thread_h
#define __included_core_thread_h

#include <crisscross/win32_pthread_emulate.h>

#include <crisscross/core_system.h>

#    if defined ( TARGET_OS_WINDOWS )
#            include <windows.h>
#    else
typedef pthread_t DWORD;
typedef pthread_t HANDLE;
#    endif

namespace CrissCross
{
    namespace System
    {
        //! The core thread class.
        /*!
            Should not be used standalone. Needs to be inherited by another class, with
            the function CoreThread::Process overridden.
        */
        class CoreThread
        {

          public:
            //! Thread priority specification.
            enum ThreadPriority
            {
                PRIORITY_IDLE,
                PRIORITY_LOWEST,
                PRIORITY_BELOW_NORMAL,
                PRIORITY_NORMAL,
                PRIORITY_ABOVE_NORMAL,
                PRIORITY_HIGHEST,
                PRIORITY_TIME_CRITICAL
            };

            //! Thread affinity specification.
            /*!
               Specifies what CPU the thread should be allowed to run on.
             */
            enum ThreadAffinity
            {
                CPU_ANY = -1,            //!< Allows the thread to run on any CPU available.
                CPU_ZERO = 0,            //!< Allows the thread to run only on the first CPU.
                CPU_ONE = 1,            //!< Allows the thread to run only on the second CPU.
                CPU_TWO = 2,            //!< Allows the thread to run only on the third CPU.
                CPU_THREE = 3            //!< Allows the thread to run only on the fourth CPU.
            };

            //! Specifies this thread's affinity.
            /*!
               \sa CoreThread::ThreadAffinity
             */
            ThreadAffinity m_Affinity;

            //! Specifies this thread's priority.
            /*!
               \sa CoreThread::ThreadPriority
             */
            ThreadPriority m_Priority;

            //! The maximum time the thread should run.
            /*!
               Currently unused.
             */
            unsigned int m_Timeout;

            //! The parameter to be passed to the thread.
            /*!
               Can be a pointer to a struct, a class, or whatever other information
               may be needed by CoreThread::Process during the thread's execution.
             */
            void *m_threadParams;

          protected:

            //! The ID of the thread.
              pthread_t m_hThreadId;

            //! The ID of the parent thread.
            pthread_t m_hMainThreadId;

        #    if defined ( TARGET_OS_WINDOWS )

            //! The handle of the thread.
            HANDLE m_hThread;

            //! The handle of the parent thread.
            HANDLE m_hMainThread;

        #    else
        #            define            m_hThread m_hThreadId
        #            define            m_hMainThread m_hMainThreadId
        #    endif

          public:

            //! The constructor.
              CoreThread ();

            //! The destructor.
            /*!
               Virtual so it can be overridden by any derived classes.
             */
              virtual ~ CoreThread ();

            //! Specifies whether the thread is currently executing.
            /*!
               \return Zero if not executing. Otherwise, nonzero.
             */
            int IsRunning ();

            //! Starts the thread.
            /*!
               \return True if the thread was successfully started. Otherwise, false.
             */
            bool CreateThread ();

            //! Ends the thread execution.
            void Terminate ();

            //! Waits indefinitely for the thread to finish executing.
            void Wait ();

            /*!
               \return Handle to the thread.
             */
            HANDLE GetThreadHandle ();

            /*!
               \return ID of the thread.
             */
            DWORD GetThreadId ();

            /*!
               \return Handle of the main thread.
             */
            HANDLE GetMainThreadHandle ();

            /*!
               \return ID of the main thread.
             */
            DWORD GetMainThreadId ();

          protected:
            //! Gets a platform-specific identifier for the thread priority.
            /*!
               \param _priority The priority to be translated.
               \return The value to be used in platform-specific API calls.
             */
            int LocalPriorityType ( ThreadPriority _priority );

            //! Gets a platform-specific identifier for the thread affinity.
            /*!
               \param _affinity The affinity to be translated.
               \return The value to be used in platform-specific API calls.
             */
            int LocalAffinity ( ThreadAffinity _affinity );

          protected:
            //! The thread code itself.
            /*!
               \param _parameter CoreThread::m_threadParams
               \return The return value of the thread.
             */
              virtual unsigned int Process ( void *_parameter );

          private:
            //! Calls the main thread code.
            /*!
               \param _parameter CoreThread::m_threadParams
               \return The return value of the thread.
             */
            static THREAD_FUNCTION runProcess ( void *_parameter );

        };

        //! @cond
        struct param
        {
            CoreThread *pThread;
        };
        //! @endcond
    }
}

#endif
