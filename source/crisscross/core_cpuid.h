/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
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

#ifndef __included_core_cpuid_h
#define __included_core_cpuid_h

#    ifdef ENABLE_CPUID

#        ifdef TARGET_OS_WINDOWS
#            include <windows.h>
#        endif

#        include "darray.h"
#        include "rbtree.h"

class Feature
{
  public:
    bool Enabled;
    Feature ()
    {
        Enabled = 0;
    };

    ~Feature ()
    {
    };
};

class Processor
{
  public:
    const char *Manufacturer;
    const char *ProcessorName;
    char LogicalCount;
	char PhysicalCount;
    char Family;
    char Model;
    char Stepping;
    char BrandID;
    char APICID;
      RedBlackTree < Feature *, char *> features;
      DArray <char *> caches;
  public:
      Processor ()
    {
    };

    ~Processor ()
    {
    };
};


class CoreCPUID
{

  protected:

#        ifdef TARGET_OS_WINDOWS

    struct GoThreadProc_Params
    {
        CoreCPUID *cpuid_class;
        int processor;
    };

    static DWORD CALLBACK s_GoThreadProc ( LPVOID lpParameter )
    {
        return ( ( GoThreadProc_Params * ) lpParameter )->cpuid_class->
            GoThread ( ( LPVOID * ) &
                       ( ( GoThreadProc_Params * ) lpParameter )->processor );
    };
    DWORD WINAPI GoThread ( LPVOID * params );
#        else
    long int GoThread ( int processor );
#        endif

    void AddCacheDescription ( int processor, const char *description );
    void AddCacheData ( int processor, int x );
    void DetectManufacturer ( int processor );
    void DetectProcessorName ( int processor );
    void DetectCacheInfo ( int processor );
    void DetectFMS ( int processor );
    void DetectBrandID ( int processor );
    void DetectCount ( int processor );
    void DetectAPIC ( int processor );
    void DetectFeatures ( int processor );
    void DetectFeature ( unsigned const int *_register, int _flag,
                         int _processor, const char *_name );

  public:
      CoreCPUID ();
     ~CoreCPUID ();
    void Go ();
    int GetLogicalCPUCount ();
    int GetPhysicalCPUCount ();
    int GetVirtualCPUCount ();

    Processor *proc[MAX_PROCESSORS];    // Support up to MAX_PROCESSORS

};

#    endif

#endif
