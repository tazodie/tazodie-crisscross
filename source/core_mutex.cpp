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
#include <crisscross/core_debug.h>
#include <crisscross/core_mutex.h>

using namespace CrissCross::System;

CoreMutex::CoreMutex ()
{
#ifdef TARGET_OS_WINDOWS
    InitializeCriticalSection(&m_criticalSection);
#else
    int error = pthread_mutex_init(&m_hMutex, 0);
    CoreAssert ( error == 0 );
#endif
}

CoreMutex::~CoreMutex ()
{
    Unlock();
#ifdef TARGET_OS_WINDOWS
    DeleteCriticalSection(&m_criticalSection);
#else
    pthread_mutex_destroy(&m_hMutex);
#endif
}

void
CoreMutex::Lock ()
{
#ifdef TARGET_OS_WINDOWS
    EnterCriticalSection(&m_criticalSection);
#else
    int error = pthread_mutex_lock(&m_hMutex);
    CoreAssert ( error == 0 );
#endif
}

void
CoreMutex::Unlock ()
{
#ifdef TARGET_OS_WINDOWS
    LeaveCriticalSection(&m_criticalSection);
#else
    int error = pthread_mutex_unlock(&m_hMutex);
    CoreAssert ( error == 0 );
#endif
}
