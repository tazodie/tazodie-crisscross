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

#ifndef __included_core_mutex_h
#define __included_core_mutex_h

#include "datastructures/llist.h"

//! The safe threading mutex class.
/*!
	Allows for safe threading by locking via thread ID.
*/
class CoreMutex
{
protected:
	//! The currently active thread.
	/*!
		The thread currently permitted to execute between CoreMutex::Lock() and CoreMutex::Unlock()
	*/
	pthread_t	m_currentThread;

	//! The queue of threads waiting for access.
	/*!
		A linked list of threads waiting for access to objects locked by the mutex.
	*/
	LList <pthread_t> *m_threadQueue;

	//! Indicates whether the mutex is locked or not.
	bool			m_mutexLocked;
public:

	//! The constructor.
	CoreMutex		();

	//! The destructor.
	~CoreMutex		();

	//! Determines whether the mutex is locked or not.
	/*!
		\return Indicates the state of the mutex lock.
	*/
	bool			IsLocked();

	//! Locks the mutex.
	void			Lock ();

	//! Unlocks the mutex.
	void			Unlock ();
protected:


	//! Sleeps the current thread for a specified time.
	/*!
		\param _msec Time to sleep for, in milliseconds.
		\sa CoreSystem::ThreadSleep
	*/
	void			ThreadSleep ( int _msec );

	//! Sleeps until the mutex is unlocked.
	/*!
		Waits for the mutex to unlock or switch to allow the pending thread.
	*/
	void			WaitForUnlock ();
};

#endif
