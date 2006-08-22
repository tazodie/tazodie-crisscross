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

#ifndef __included_core_system_h
#define __included_core_system_h

#include "core_cpuid.h"

#if defined ( TARGET_OS_WINDOWS )
#	include <windows.h>
#elif defined ( TARGET_OS_MACOSX )
#	include <CoreServices/CoreServices.h>
#	include <mach/mach.h>
#	include <mach/mach_time.h>
#elif defined ( TARGET_OS_LINUX )
#	include <sys/time.h>
#	include <sched.h>
#	include <time.h>
#endif

//! Class for platform-specific API calls.
class CoreSystem
{
protected:
#if defined ( TARGET_OS_WINDOWS )

	//! The result of QueryPerformanceFrequency(). (Windows only)
	double			m_tickInterval;

#elif defined ( TARGET_OS_MACOSX )

	//! The time index at which the timer started. ( Mac OS X only)
	uint64_t		m_start;

	//! The time base information. (Mac OS X only)
	mach_timebase_info_data_t 		m_timebase;

#elif defined ( TARGET_OS_LINUX )

	//! The time index at which the timer started. (Linux only)
	timeval			m_start;

#endif
public:
	//! The constructor.
	CoreSystem		();

	//! The destructor.
	~CoreSystem		();

	//! (Re)initializes the timer. Automatically called in CoreSystem::CoreSystem().
	/*!
		Resets the start time to zero.
	*/
	void			InitTimer ();

	//! Sleeps the current thread for a specified time.
	/*!
		\param _msec Time to sleep for, in milliseconds.
	*/
	void			ThreadSleep ( int _msec );

#if defined ( TARGET_OS_WINDOWS )
	//! Waits for the specified thread to finish executing.
	/*!
		\param _thread Thread to wait for.
		\param _timeout The maximum wait time. (currently ignored)
		\return Always zero, until _timeout is implemented.
	*/
	int				WaitForThread ( HANDLE _thread, DWORD _timeout );
#elif defined ( TARGET_OS_LINUX )
	//! Waits for the specified thread to finish executing.
	/*!
		\param _thread Thread to wait for.
		\param _timeout The maximum wait time. (currently ignored)
		\return Always zero, until _timeout is implemented.
	*/
	int				WaitForThread ( pthread_t _thread, int _timeout );
#endif

	//! Queries the high resolution timer.
	/*!
		\return The number of seconds that the high resolution timer is currently at.
	*/
	double			GetHighResTime ();
};

#endif
