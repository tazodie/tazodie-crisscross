/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>.
 * All rights reserved.
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
#include "core_thread.h"
#include "core_system.h"

CoreThread::CoreThread ( CoreSystem * _system )
{
	m_system = _system;
#if defined ( TARGET_OS_WINDOWS )
	m_hThread = NULL;
	m_hMainThread =::GetCurrentThread (  );
#endif
	m_hThreadId = 0;
	m_hMainThreadId = pthread_self (  );
	m_Timeout = 2000;			//milliseconds
	m_Priority = PRIORITY_NORMAL;
	m_Affinity = CPU_ANY;
}

CoreThread::~CoreThread (  )
{
	//waiting for the thread to terminate
	if ( m_hThread )
	{
		Wait (  );
		pthread_detach ( m_hThread );
	}
}

int
CoreThread::IsRunning (  )
{
	return ( m_hThread != 0 );
}

HANDLE
CoreThread::GetMainThreadHandle (  )
{
	return m_hMainThread;
}

DWORD
CoreThread::GetMainThreadId (  )
{
	return m_hMainThreadId;
}

HANDLE
CoreThread::GetThreadHandle (  )
{
	return m_hThread;
}

DWORD
CoreThread::GetThreadId (  )
{
	return m_hThreadId;
}

unsigned int
CoreThread::Process ( void *_parameter )
{

	//a mechanism for terminating thread should be implemented
	//not allowing the method to be run from the main thread
	if ( pthread_self (  ) == m_hMainThreadId )
		return 0;
	else
	{

		return 0;
	}

}

bool
CoreThread::CreateThread (  )
{

	if ( !IsRunning (  ) )
	{
		param *this_param = new param;

		this_param->pThread = this;
		//::CreateThread ( NULL, NULL, &runProcess, (void *)this_param, NULL, &m_hThreadId );
		pthread_create ( &m_hThread, NULL, runProcess,
						 ( void * ) this_param );
		return m_hThread ? true : false;
	}
	return false;

}

void
CoreThread::Terminate (  )
{
	if ( IsRunning (  ) )
		pthread_cancel ( m_hThread );
}

THREAD_FUNCTION
CoreThread::runProcess ( void *Param )
{
	CoreThread *thread;
	unsigned int retval;

	thread = ( CoreThread * ) ( ( param * ) Param )->pThread;
	delete ( ( param * ) Param );

	int affinity = thread->LocalAffinity ( thread->m_Affinity );

	thread->m_hThreadId = pthread_self (  );

#if defined ( TARGET_OS_WINDOWS )
	/* TODO: Implement this for Linux / Mac OS X */
	if ( affinity != -1 )
		SetThreadAffinityMask ( thread->m_hThread, affinity );

	SetThreadPriority ( thread->m_hThread,
						thread->LocalPriorityType ( thread->m_Priority ) );
#endif

	retval = thread->Process ( thread->m_threadParams );

	thread->m_hThreadId = 0;
	thread->m_hThread = 0;

	return NULL;
}

int
CoreThread::LocalPriorityType ( ThreadPriority _priority )
{
	/* TODO: Mac OS X port of this function. */
#if defined ( TARGET_OS_WINDOWS )
	switch ( _priority )
	{
	case PRIORITY_IDLE:
		return THREAD_PRIORITY_IDLE;
	case PRIORITY_LOWEST:
		return THREAD_PRIORITY_LOWEST;
	case PRIORITY_BELOW_NORMAL:
		return THREAD_PRIORITY_BELOW_NORMAL;
	case PRIORITY_NORMAL:
		return THREAD_PRIORITY_NORMAL;
	case PRIORITY_ABOVE_NORMAL:
		return THREAD_PRIORITY_ABOVE_NORMAL;
	case PRIORITY_HIGHEST:
		return THREAD_PRIORITY_HIGHEST;
	case PRIORITY_TIME_CRITICAL:
		return THREAD_PRIORITY_TIME_CRITICAL;
	}
#elif defined ( TARGET_OS_LINUX )
	// Approximate to 'niceness' equivalents
	switch ( _priority )
	{
	case PRIORITY_IDLE:
		return 19;
	case PRIORITY_LOWEST:
		return 14;
	case PRIORITY_BELOW_NORMAL:
		return 7;
	case PRIORITY_NORMAL:
		return 0;
	case PRIORITY_ABOVE_NORMAL:
		return -7;
	case PRIORITY_HIGHEST:
		return -14;
	case PRIORITY_TIME_CRITICAL:
		return -20;
	}
#endif
	return 0;
}

void
CoreThread::Wait (  )
{
#if defined ( TARGET_OS_WINDOWS )
	WaitForSingleObject ( m_hThread, INFINITE );
#else
	while ( IsRunning (  ) )
	{
		m_system->ThreadSleep ( 100 );
	}
#endif
}

int
CoreThread::LocalAffinity ( ThreadAffinity _affinity )
{
	/* TODO: Linux and Mac OS X ports of this function. */
#if defined ( TARGET_OS_WINDOWS )
	switch ( _affinity )
	{
	case CPU_ANY:
		return -1;
	default:
		return ( int ) pow ( ( double ) 2, _affinity );
	}
#endif
}
