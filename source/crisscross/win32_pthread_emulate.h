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
    
#if defined ( TARGET_OS_WINDOWS )
/* Windows requires definitions for the POSIX file I/O functions */ 
#        include <io.h>
#        define _INTEGRAL_MAX_BITS 64
#        define read(fd,pbuffer,count) _read(fd,pbuffer,count)
#        define write(fd,pbuffer,count) _write(fd,pbuffer,count)
#        define open(fn,flag) _open(fn,flag)
#        define open3(fn,flag,mode) _open(fn,flag,mode)
//# define close(fd) _close(fd)
#        define lseek64(handle,offset,origin) _lseeki64(handle,offset,origin)
#        define sleep(t) Sleep(1000*(t))
#        define sync() ;
#        define off64_t __int64
#        define size64_t __int64
#elif defined ( TARGET_OS_LINUX )
#        define open3(fn,flag,mode) open(fn,flag,mode)
#        define lseek64(handle,offset,origin) lseek(handle,offset,origin)
#        define FlushFileBuffers(i) 1
#        define off64_t long long
#        define size64_t long long
#else
#        define open3(fn,flag,mode) open(fn,flag,mode)
#        define FlushFileBuffers(i) 1
#        define size64_t long long
#endif
    
#if defined ( TARGET_OS_WINDOWS )
#        define _WIN32_WINNT 0x500 /* Require Windows NT5 (2K, XP, 2K3) */
#        include <windows.h>
#        include <time.h>
#else
#        include <unistd.h>
#		 include <errno.h>
#        include <sys/time.h>
#endif
    
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

    
/* Thread_emulation.h */ 
/* Author: Johnson M. Hart */ 
/* Emulate the Pthreads model for the Win32 platform */ 
/* The emulation is not complete, but it does provide a subset */ 
/* required for a first project */ 
    
#ifndef _THREAD_EMULATION
#    define _THREAD_EMULATION
    
/* Thread management macros */ 
#    if defined ( TARGET_OS_WINDOWS )
/* Win32 */ 
#            define _WIN32_WINNT 0x500 /* WINBASE.H - Enable SignalObjectAndWait */
#            include <process.h>
#            include <windows.h>
#            define THREAD_FUNCTION unsigned int __stdcall
#            define THREAD_FUNCTION_RETURN unsigned int
#            define THREAD_SPECIFIC_INDEX DWORD
#            define pthread_t unsigned long
#            define pthread_attr_t DWORD
#            define pthread_create(thhandle,attr,thfunc,tharg) (int)( (*thhandle = (HANDLE)_beginthreadex(NULL,0,&thfunc,tharg,0,NULL) ) == NULL)
#            define pthread_join(thread, result) ((WaitForSingleObject((thread),INFINITE)!=WAIT_OBJECT_0) || !CloseHandle(thread))
#            define pthread_detach(thread) if(thread!=NULL)CloseHandle(thread)
#            define thread_sleep(nms) Sleep(nms)
#            define pthread_cancel(thread) TerminateThread(thread,0)
#            define ts_key_create(ts_key, destructor) {ts_key = TlsAlloc();};
#            define pthread_getspecific(ts_key) TlsGetValue(ts_key)
#            define pthread_setspecific(ts_key, value) TlsSetValue(ts_key, (void *)value)
#            define pthread_self() GetCurrentThreadId()
#    else
/* pthreads */ 
/* Nearly everything is already defined */ 
#            define THREAD_FUNCTION void *
#            define THREAD_FUNCTION_RETURN void *
#            define THREAD_SPECIFIC_INDEX pthread_key_t
#            define thread_sleep(nms) sleep((nms+500)/1000)
#            define ts_key_create(ts_key, destructor) pthread_key_create (&(ts_key), destructor);
#    endif
    
/* Syncrhronization macros: Win32 and Pthreads */ 
#    if defined ( TARGET_OS_WINDOWS )
#            define pthread_mutex_t HANDLE
#            define pthread_cond_t HANDLE
#            define pthread_mutex_lock(pobject) WaitForSingleObject(*pobject,INFINITE)
#            define pthread_mutex_unlock(pobject) ReleaseMutex(*pobject)
#            define pthread_mutex_init(pobject,pattr) (*pobject=CreateMutex(NULL,FALSE,NULL))
#            define pthread_cond_init(pobject,pattr) (*pobject=CreateEvent(NULL,FALSE,FALSE,NULL))
#            define pthread_mutex_destroy(pobject) CloseHandle(*pobject)
#            define pthread_cond_destroy(pobject) CloseHandle(*pobject)
#            define CV_TIMEOUT INFINITE /* Tunable value */
#            define pthread_cond_wait(pcv,pmutex) {SignalObjectAndWait(*pmutex,*pcv,INFINITE,FALSE);WaitForSingleObject(*pmutex,INFINITE);};
#            define pthread_cond_signal(pcv) SetEvent(*pcv)
#    else
    /* Not Windows. Assume pthreads */ 
#    endif
    
#endif
