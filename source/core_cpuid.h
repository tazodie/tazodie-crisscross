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

#ifndef __included_core_cpuid_h
#define __included_core_cpuid_h

#ifdef ENABLE_CPUID

#ifdef TARGET_OS_WINDOWS
#include <windows.h>
#endif

#include "datastructures/darray.h"
#include "datastructures/rbtree.h"

class Feature {
public:
	bool Enabled;
	Feature(){ Enabled = 0; };
	~Feature(){};
};

/*
struct Features {
	//EDX register
	int FPU;
	int VME;
	int DE;
	int PSE;
	int TSC;
	int MSR;
	int PAE;
	int MCE;
	int CX8;
	int APIC;
	int SEP;
	int MTRR;
	int PGE;
	int MCA;
	int CMOV;
	int PAT;
	int PSE36;
	int PSNUM;
	int CLFLUSH;
	int DTS;
	int ACPI;
	int MMX;
	int FXSR;
	int SSE;
	int SSE2;
	int SS;
	int HTT;
	int TM1;
	int IA64;
	int PBE;

	// ECX register
	int SSE3;
	int LAHF;
	int DS_CPL;
	int MONITOR;
	int EIST;
	int TM2;
	int CID;
	int SYSCALL;
	int CX16;
	int XTPR;
	int XD;
	int EM64T;

	// AMD EDX 8000_0001
	int NX;
	int MMXEXT;
	int FFXSR;
	int RDTSCP;
	int LM;
	int _3DNOWEXT;
	int _3DNOW;
};*/

class Processor {
public:
	char *Manufacturer;
	char *ProcessorName;
	char Count;
	char Family;
	char Model;
	char Stepping;
	char BrandID;
	char APICID;
	RedBlackTree<Feature *, char *> features;
	DArray<char *> caches;
public:
	Processor() {};
	~Processor() {};
};


class CoreCPUID {

protected:

#ifdef TARGET_OS_WINDOWS

	struct GoThreadProc_Params {
		CoreCPUID *cpuid_class;
		int processor;
	};

	static DWORD CALLBACK s_GoThreadProc(LPVOID lpParameter) {
		return ((GoThreadProc_Params *)lpParameter)->cpuid_class->GoThread ( (LPVOID *)&((GoThreadProc_Params *)lpParameter)->processor );
	};
	DWORD WINAPI GoThread(LPVOID *params);
#else
	long int GoThread ( int processor );
#endif

	void AddCacheDescription ( int processor, char *description );
	void AddCacheData ( int processor, int x );
	void DetectManufacturer ( int processor );
	void DetectProcessorName ( int processor );
	void DetectCacheInfo ( int processor );
	void DetectFMS ( int processor );
	void DetectBrandID ( int processor );
	void DetectCount ( int processor );
	void DetectAPIC ( int processor );
	void DetectFeatures ( int processor );
	void DetectFeature (unsigned const int *_register, int _flag, int _processor, char * _name );

public:
	CoreCPUID();
	~CoreCPUID();
	void Go();
	int GetCPUCount();

	Processor *proc[MAX_PROCESSORS]; // Support up to MAX_PROCESSORS

};

#endif

#endif
