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

#ifdef ENABLE_CPUID

#    include "core_cpuid.h"
#    include "core_io.h"
#    include "core_thread.h"

#    define FPU_FLAG 0x0001
#    define VME_FLAG 0x0002
#    define DE_FLAG 0x0004
#    define PSE_FLAG 0x0008
#    define TSC_FLAG 0x0010
#    define MSR_FLAG 0x0020
#    define PAE_FLAG 0x0040
#    define MCE_FLAG 0x0080
#    define CX8_FLAG 0x0100
#    define APIC_FLAG 0x0200
#    define SEP_FLAG 0x0800
#    define MTRR_FLAG 0x1000
#    define PGE_FLAG 0x2000
#    define MCA_FLAG 0x4000
#    define CMOV_FLAG 0x8000
#    define PAT_FLAG 0x10000
#    define PSE36_FLAG 0x20000
#    define PSNUM_FLAG 0x40000
#    define CLFLUSH_FLAG 0x80000
#    define DTS_FLAG 0x200000
#    define ACPI_FLAG 0x400000
#    define MMX_FLAG 0x800000
#    define FXSR_FLAG 0x1000000
#    define SSE_FLAG 0x2000000
#    define SSE2_FLAG 0x4000000
#    define SS_FLAG 0x8000000
#    define HTT_FLAG 0x10000000
#    define TM1_FLAG 0x20000000
#    define IA64_FLAG 0x40000000
#    define PBE_FLAG 0x80000000
#    define SSE3_FLAG 0x0001
#    define MONITOR_FLAG 0x0008
#    define DS_CPL_FLAG 0x0010
#    define EIST_FLAG 0x0080
#    define TM2_FLAG 0x0100
#    define CID_FLAG 0x0400
#    define CX16_FLAG 0x2000
#    define XTPR_FLAG 0x4000
#    define LAHF_FLAG 0x00000001
#    define SYSCALL_FLAG 0x00000800
#    define XD_FLAG 0x00100000
#    define EM64T_FLAG 0x20000000

// AMD 8000_0001 EDX flags
#    define _3DNOW_FLAG 0x80000000
#    define _3DNOWEXT_FLAG 0x40000000
#    define LM_FLAG 0x20000000
#    define RDTSCP_FLAG 0x8000000
#    define FFXSR_FLAG 0x2000000
#    define FXSR_FLAG 0x1000000
#    define MMXEXT_FLAG 0x800000
#    define NX_FLAG 0x100000

struct Registers
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
};

struct Registers *Std;
unsigned int StdMax;
struct Registers *Ext;
unsigned int ExtMax;

static inline void
call_cpuid ( unsigned int op, unsigned int *_eax, unsigned int *_ebx,
			 unsigned int *_ecx, unsigned int *_edx )
{
#    ifdef TARGET_OS_WINDOWS
	/* TODO: This ASM block shouldn't be this large, but using "mov [_eax], eax" doesn't seem to work... Fix this. */
	__asm
	{
		mov eax, op;
		cpuid;
#if 1
		mov edi,[_eax];
		mov[edi], eax;
		mov edi,[_ebx];
		mov[edi], ebx;
		mov edi,[_ecx];
		mov[edi], ecx;
		mov edi,[_edx];
		mov[edi], edx;
#else
		mov[_eax], eax;
		mov[_ebx], ebx;
		mov[_ecx], ecx;
		mov[_edx], edx;
#endif
	}
#    else
  __asm__ ( "cpuid"
			: "=a" ( *_eax ),
			  "=b" ( *_ebx ),
			  "=c" ( *_ecx ),
			  "=d" ( *_edx )
			: "0" ( op ) );
#    endif
}

CoreCPUID::CoreCPUID (  )
{
	unsigned int i = 0;

	for ( i = 0; i < MAX_PROCESSORS; i++ )
	{
		proc[i] = new Processor (  );
		CoreAssert ( proc[i] != NULL );
		proc[i]->Manufacturer = NULL;
		proc[i]->ProcessorName = NULL;
	}

	Std = new Registers[32];
	Ext = new Registers[32];

	memset ( Std, 0, sizeof ( Registers ) * 32 );
	memset ( Ext, 0, sizeof ( Registers ) * 32 );

	StdMax = 0;
	ExtMax = 0;

	/* Basic initializations complete */

	call_cpuid ( 0, &Std[0].eax, &Std[0].ebx, &Std[0].ecx, &Std[0].edx );
	StdMax = Std[0].eax;

	if ( StdMax > 31 )
	{
#    ifdef CPUID_DEBUG
		g_console->WriteLine ( "CPUID.0.EAX has an invalid value: %d",
							   StdMax );
#    endif
		StdMax = 31;
	}
	else
	{
#    ifdef CPUID_DEBUG
		g_console->WriteLine ( "Standard CPUID maximum input is %d.",
							   StdMax );
#    endif
	}

	for ( i = 1; i <= StdMax; i++ )
	{
		call_cpuid ( i, &Std[i].eax, &Std[i].ebx, &Std[i].ecx, &Std[i].edx );
	}


	call_cpuid ( 0x80000000, &Ext[0].eax, &Ext[0].ebx, &Ext[0].ecx,
				 &Ext[0].edx );

	if ( Ext[0].eax > ( 0x80000000 + 31 ) )
	{
#    ifdef CPUID_DEBUG
		g_console->
			WriteLine
			( "Extended CPUID maximum input is 0x80000000 + 31 [forced].",
			  Ext[0].eax );
#    endif
		Ext[0].eax = 0x80000000 + 31;
	}
	else
	{
#    ifdef CPUID_DEBUG
		g_console->WriteLine ( "Extended CPUID maximum input is %u.",
							   Ext[0].eax - 0x80000000 );
#    endif
	}

	for ( i = 0; i <= Ext[0].eax - 0x80000000; i++ )
	{
		call_cpuid ( 0x80000000 + i, &Ext[i].eax, &Ext[i].ebx, &Ext[i].ecx,
					 &Ext[i].edx );
	}
}

CoreCPUID::~CoreCPUID (  )
{
	// Time to deallocate all the memory we allocated.
	int i = 0, j = 0;

	delete[]Std;
	delete[]Ext;
	for ( i = 0; i < MAX_PROCESSORS; i++ )
	{
		while ( proc[i]->caches.ValidIndex ( j ) )
		{
			delete[]proc[i]->caches.GetData ( j );
			j++;
		}
		j = 0;
		RedBlackTree < Feature *, char *>::nodeType * node;

		node = proc[i]->features.rootNode;
		node->beenThere =
			RedBlackTree < Feature *, char *>::NODE_ITSELF_VISITED;
		while ( proc[i]->features.ValidNode ( node ) )
		{
			delete ( Feature * ) node->data;
			node->data = NULL;
			proc[i]->features.getNext ( &node );
		}
		delete[]proc[i]->Manufacturer;
		delete[]proc[i]->ProcessorName;
		delete proc[i];
	}
}

int
CoreCPUID::GetCPUCount (  )
{
	int count = 0, i;

	for ( i = 0; i < MAX_PROCESSORS; i++ )
	{
		if ( proc[i]->Manufacturer )
			count++;
	}
	return count;
}

#    ifdef TARGET_OS_WINDOWS
DWORD WINAPI
CoreCPUID::GoThread ( LPVOID * params )
#    else
long int
CoreCPUID::GoThread ( int processor )
#    endif
{
#    ifdef TARGET_OS_WINDOWS
	int processor;
	memcpy ( &processor, params, sizeof ( int ) );
#    endif
	if ( processor < 0 || processor > MAX_PROCESSORS )
	{
		return 1;
	}
	DetectManufacturer ( processor );
	DetectProcessorName ( processor );
	DetectFeatures ( processor );
	DetectCacheInfo ( processor );
	DetectFMS ( processor );
	DetectBrandID ( processor );
	DetectCount ( processor );
	DetectAPIC ( processor );
	return 0;
}

void
CoreCPUID::Go (  )
{
#    ifdef TARGET_OS_WINDOWS
	// TODO: Implement this WIN32-only part in Linux/MacOS
	DWORD dThread = NULL;
	SYSTEM_INFO siSystem;
	int iCount = 0;
	struct GoThreadProc_Params params;

	params.cpuid_class = this;
	GetSystemInfo ( &siSystem );

	iCount = siSystem.dwNumberOfProcessors;

	if ( iCount > MAX_PROCESSORS )
	{
		iCount = MAX_PROCESSORS;
	}

	for ( params.processor = 0; params.processor < iCount;
		  params.processor++ )
	{
		HANDLE hThread =
			CreateThread ( NULL, 0, ( LPTHREAD_START_ROUTINE ) s_GoThreadProc,
						   &params, 0, &dThread );
		SetThreadAffinityMask ( hThread,
								( DWORD ) pow ( ( double ) 2,
												( double ) params.
												processor ) );
		SetThreadPriority ( hThread, THREAD_PRIORITY_ABOVE_NORMAL );
		WaitForSingleObject ( hThread, INFINITE );
	}
#    else
	int NUM_PROCS = sysconf ( _SC_NPROCESSORS_CONF ), i;
	cpu_set_t mask;
	cpu_set_t originalmask;

	sched_getaffinity ( 0, sizeof ( originalmask ), &originalmask );
	for ( i = 0; i < NUM_PROCS; i++ )
	{
		CPU_ZERO ( &mask );
		CPU_SET ( ( int ) pow ( 2, i ), &mask );
		sched_setaffinity ( 0, sizeof ( mask ), &mask );
		GoThread ( i );
	}
	sched_setaffinity ( 0, sizeof ( originalmask ), &originalmask );
#    endif
}

void
CoreCPUID::DetectManufacturer ( int processor )
{
	char *manufacturer = new char[( 4 * 3 ) + 1];
	char *_man = &manufacturer[0];

	memcpy ( _man, &Std[0].ebx, 4 );
	_man += 4;
	memcpy ( _man, &Std[0].edx, 4 );
	_man += 4;
	memcpy ( _man, &Std[0].ecx, 4 );
	_man += 4;
	*_man = '\x0';
	proc[processor]->Manufacturer = manufacturer;
}

void
CoreCPUID::DetectProcessorName ( int processor )
{
	char *processorname = new char[( 4 * 12 ) + 1];
	char *_proc = &processorname[0];

	memcpy ( _proc, &Ext[2].eax, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[2].ebx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[2].ecx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[2].edx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[3].eax, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[3].ebx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[3].ecx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[3].edx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[4].eax, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[4].ebx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[4].ecx, 4 );
	_proc += 4;
	memcpy ( _proc, &Ext[4].edx, 4 );
	_proc += 4;
	*_proc = '\x0';
	proc[processor]->ProcessorName = processorname;
}

void
CoreCPUID::DetectCacheInfo ( int processor )
{
	if ( proc[processor]->Manufacturer )
	{
		if ( strcmp ( proc[processor]->Manufacturer, "GenuineIntel" ) == 0 )
		{
			int ntlb = 255, i;

			for ( i = 0; i < ntlb; i++ )
			{

				ntlb = Std[2].eax & 0xff;

				AddCacheData ( processor, Std[2].eax >> 8 );
				AddCacheData ( processor, Std[2].eax >> 16 );
				AddCacheData ( processor, Std[2].eax >> 24 );

				if ( ( Std[2].ebx & 0x80000000 ) == 0 )
				{
					AddCacheData ( processor, Std[2].ebx );
					AddCacheData ( processor, Std[2].ebx >> 8 );
					AddCacheData ( processor, Std[2].ebx >> 16 );
					AddCacheData ( processor, Std[2].ebx >> 24 );
				}
				if ( ( Std[2].ecx & 0x80000000 ) == 0 )
				{
					AddCacheData ( processor, Std[2].ecx );
					AddCacheData ( processor, Std[2].ecx >> 8 );
					AddCacheData ( processor, Std[2].ecx >> 16 );
					AddCacheData ( processor, Std[2].ecx >> 24 );
				}
				if ( ( Std[2].edx & 0x80000000 ) == 0 )
				{
					AddCacheData ( processor, Std[2].edx );
					AddCacheData ( processor, Std[2].edx >> 8 );
					AddCacheData ( processor, Std[2].edx >> 16 );
					AddCacheData ( processor, Std[2].edx >> 24 );
				}
			}
		}
		else if ( strcmp ( proc[processor]->Manufacturer, "AuthenticAMD" ) ==
				  0 )
		{

		}
	}

}

void
CoreCPUID::AddCacheDescription ( int processor, const char *description )
{
	char *temp = new char[strlen ( description ) + 1];

	CoreAssert ( temp != NULL );
	strcpy ( temp, description );
	proc[processor]->caches.PutData ( temp );
	temp = NULL;
}

void
CoreCPUID::AddCacheData ( int processor, int x )
{
	x &= 0xff;
	switch ( x )
	{
	case 0:
		break;
	case 0x1:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4KB pages, 4-way set associative, 32 entries\n" );
		break;
	case 0x2:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4MB pages, fully associative, 2 entries\n" );
		break;
	case 0x3:
		AddCacheDescription ( processor,
							  "Data TLB: 4KB pages, 4-way set associative, 64 entries\n" );
		break;
	case 0x4:
		AddCacheDescription ( processor,
							  "Data TLB: 4MB pages, 4-way set associative, 8 entries\n" );
		break;
	case 0x6:
		AddCacheDescription ( processor,
							  "1st-level instruction cache: 8KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x8:
		AddCacheDescription ( processor,
							  "1st-level instruction cache: 16KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0xa:
		AddCacheDescription ( processor,
							  "1st-level data cache: 8KB, 2-way set associative, 32 byte line size\n" );
		break;
	case 0xc:
		AddCacheDescription ( processor,
							  "1st-level data cache: 16KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x22:
		AddCacheDescription ( processor,
							  "3rd-level data cache: 512KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x23:
		AddCacheDescription ( processor,
							  "3rd-level data cache: 1MB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x25:
		AddCacheDescription ( processor,
							  "3rd-level data cache: 2MB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x29:
		AddCacheDescription ( processor,
							  "3rd-level data cache: 4MB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x2C:
		AddCacheDescription ( processor,
							  "1st-level data cache: 32KB, 8-way set associative, 64 byte line size\n" );
		break;
	case 0x30:
		AddCacheDescription ( processor,
							  "1st-level instruction cache: 32KB, 8-way set associative, 64 byte line size\n" );
		break;
	case 0x39:
		AddCacheDescription ( processor,
							  "2nd-level cache: 128KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x3A:
		AddCacheDescription ( processor,
							  "2nd-level cache: 192KB, 6-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x3B:
		AddCacheDescription ( processor,
							  "2nd-level cache: 128KB, 2-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x3C:
		AddCacheDescription ( processor,
							  "2nd-level cache: 256KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x3D:
		AddCacheDescription ( processor,
							  "2nd-level cache: 384KB, 6-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x3E:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x40:
		AddCacheDescription ( processor,
							  "No 2nd-level cache, or if 2nd-level cache exists, no 3rd-level cache\n" );
		break;
	case 0x41:
		AddCacheDescription ( processor,
							  "2nd-level cache: 128KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x42:
		AddCacheDescription ( processor,
							  "2nd-level cache: 256KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x43:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x44:
		AddCacheDescription ( processor,
							  "2nd-level cache: 1MB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x45:
		AddCacheDescription ( processor,
							  "2nd-level cache: 2MB, 4-way set associative, 32 byte line size\n" );
		break;
	case 0x46:
		AddCacheDescription ( processor,
							  "3rd-level cache: 4MB, 4-way set associative, 64 byte line size\n" );
		break;
	case 0x47:
		AddCacheDescription ( processor,
							  "3rd-level cache: 8MB, 4-way set associative, 64 byte line size\n" );
		break;
	case 0x49:
		AddCacheDescription ( processor,
							  "3rd-level cache: 4MB, 16-way set associative, 64 byte line size\n" );
		break;
	case 0x4A:
		AddCacheDescription ( processor,
							  "3rd-level cache: 6MB, 12-way set associative, 64 byte line size\n" );
		break;
	case 0x4B:
		AddCacheDescription ( processor,
							  "3rd-level cache: 8MB, 16-way set associative, 64 byte line size\n" );
		break;
	case 0x4C:
		AddCacheDescription ( processor,
							  "3rd-level cache: 12MB, 12-way set associative, 64 byte line size\n" );
		break;
	case 0x4D:
		AddCacheDescription ( processor,
							  "3rd-level cache: 16MB, 16-way set associative, 64 byte line size\n" );
		break;
	case 0x50:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 64 entries\n" );
		break;
	case 0x51:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 128 entries\n" );
		break;
	case 0x52:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 256 entries\n" );
		break;
	case 0x5b:
		AddCacheDescription ( processor,
							  "Data TLB: 4KB or 4MB pages, fully associative, 64 entries\n" );
		break;
	case 0x5c:
		AddCacheDescription ( processor,
							  "Data TLB: 4KB or 4MB pages, fully associative, 128 entries\n" );
		break;
	case 0x5d:
		AddCacheDescription ( processor,
							  "Data TLB: 4KB or 4MB pages, fully associative, 256 entries\n" );
		break;
	case 0x60:
		AddCacheDescription ( processor,
							  "1st-level data cache: 16KB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x66:
		AddCacheDescription ( processor,
							  "1st-level data cache: 8KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x67:
		AddCacheDescription ( processor,
							  "1st-level data cache: 16KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x68:
		AddCacheDescription ( processor,
							  "1st-level data cache: 32KB, 4-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x70:
		AddCacheDescription ( processor,
							  "Trace cache: 12K-uops, 8-way set associative\n" );
		break;
	case 0x71:
		AddCacheDescription ( processor,
							  "Trace cache: 16K-uops, 8-way set associative\n" );
		break;
	case 0x72:
		AddCacheDescription ( processor,
							  "Trace cache: 32K-uops, 8-way set associative\n" );
		break;
	case 0x73:
		AddCacheDescription ( processor,
							  "Trace cache: 64K-uops, 8-way set associative\n" );
		break;
	case 0x78:
		AddCacheDescription ( processor,
							  "2nd-level cache: 1MB, 4-way set associative, 64 byte line size\n" );
		break;
	case 0x79:
		AddCacheDescription ( processor,
							  "2nd-level cache: 128KB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x7a:
		AddCacheDescription ( processor,
							  "2nd-level cache: 256KB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x7b:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x7c:
		AddCacheDescription ( processor,
							  "2nd-level cache: 1MB, 8-way set associative, sectored cache, 64 byte line size\n" );
		break;
	case 0x7d:
		AddCacheDescription ( processor,
							  "2nd-level cache: 2MB, 8-way set associative, 64 byte line size\n" );
		break;
	case 0x7f:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 2-way set associative, 64 byte line size\n" );
		break;
	case 0x82:
		AddCacheDescription ( processor,
							  "2nd-level cache: 256KB, 8-way set associative, 32 byte line size\n" );
		break;
	case 0x83:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 8-way set associative 32 byte line size\n" );
		break;
	case 0x84:
		AddCacheDescription ( processor,
							  "2nd-level cache: 1MB, 8-way set associative, 32 byte line size\n" );
		break;
	case 0x85:
		AddCacheDescription ( processor,
							  "2nd-level cache: 2MB, 8-way set associative, 32 byte line size\n" );
		break;
	case 0x86:
		AddCacheDescription ( processor,
							  "2nd-level cache: 512KB, 4-way set associative, 64 byte line size\n" );
		break;
	case 0x87:
		AddCacheDescription ( processor,
							  "2nd-level cache: 1MB, 8-way set associative, 64 byte line size\n" );
		break;
	case 0xB0:
		AddCacheDescription ( processor,
							  "Instruction TLB: 4KB pages, 4-way set associative, 128 entries\n" );
		break;
	case 0xB3:
		AddCacheDescription ( processor,
							  "Data TLB: 4KB pages, 4-way set associative, 128 entries\n" );
		break;
	case 0xF0:
		AddCacheDescription ( processor, "64 byte prefetching\n" );
		break;
	case 0xF1:
		AddCacheDescription ( processor, "128 byte prefetching\n" );
		break;
	default:
		//printf("unknown TLB/cache descriptor\n");
		break;
	}
}

void
CoreCPUID::DetectFMS ( int processor )
{
	proc[processor]->Family = ( Std[1].eax >> 8 ) & 0xf;
	proc[processor]->Model = ( Std[1].eax >> 4 ) & 0xf;
	proc[processor]->Stepping = Std[1].eax & 0xf;
}

void
CoreCPUID::DetectBrandID ( int processor )
{
	proc[processor]->BrandID = Std[1].ebx;
}

void
CoreCPUID::DetectCount ( int processor )
{
	// AMD and Intel documentations state that if HTT is supported
	// then this the EBX:16 will reflect the logical processor count
	// otherwise the flag is reserved.
	RedBlackTree < Feature *, char *>::nodeType * HTT_node =
		proc[processor]->features.findNode ( "HTT" );
	if ( HTT_node->data->Enabled )
		proc[processor]->Count = ( Std[1].ebx >> 16 );
	else
		// HTT not supported. Report logical processor count as 1.
		proc[processor]->Count = 1;
}

void
CoreCPUID::DetectAPIC ( int processor )
{
	proc[processor]->APICID = ( Std[1].ebx >> 24 );
}

void
CoreCPUID::DetectFeature ( unsigned const int *_register, int _flag,
						   int _processor, const char *_name )
{
	Feature *feature = new Feature (  );

	feature->Enabled = ( *_register & _flag ) > 0;
	proc[_processor]->features.insert ( ( char * ) _name, feature );
	feature = NULL;
}

void
CoreCPUID::DetectFeatures ( int processor )
{
	DetectFeature ( &Std[1].edx, FPU_FLAG, processor, "FPU" );
	DetectFeature ( &Std[1].edx, VME_FLAG, processor, "VME" );
	DetectFeature ( &Std[1].edx, DE_FLAG, processor, "DE" );
	DetectFeature ( &Std[1].edx, PSE_FLAG, processor, "PSE" );
	DetectFeature ( &Std[1].edx, TSC_FLAG, processor, "TSC" );
	DetectFeature ( &Std[1].edx, MSR_FLAG, processor, "MSR" );
	DetectFeature ( &Std[1].edx, PAE_FLAG, processor, "PAE" );
	DetectFeature ( &Std[1].edx, MCE_FLAG, processor, "MCE" );
	DetectFeature ( &Std[1].edx, CX8_FLAG, processor, "CX8" );
	DetectFeature ( &Std[1].edx, APIC_FLAG, processor, "APIC" );
	DetectFeature ( &Std[1].edx, SEP_FLAG, processor, "SEP" );
	DetectFeature ( &Std[1].edx, MTRR_FLAG, processor, "MTRR" );
	DetectFeature ( &Std[1].edx, PGE_FLAG, processor, "PGE" );
	DetectFeature ( &Std[1].edx, MCA_FLAG, processor, "MCA" );
	DetectFeature ( &Std[1].edx, CMOV_FLAG, processor, "CMOV" );
	DetectFeature ( &Std[1].edx, PAT_FLAG, processor, "PAT" );
	DetectFeature ( &Std[1].edx, PSE36_FLAG, processor, "PSE36" );
	DetectFeature ( &Std[1].edx, PSNUM_FLAG, processor, "PSNUM" );
	DetectFeature ( &Std[1].edx, CLFLUSH_FLAG, processor, "CLFLUSH" );
	DetectFeature ( &Std[1].edx, DTS_FLAG, processor, "DTS" );
	DetectFeature ( &Std[1].edx, ACPI_FLAG, processor, "ACPI" );
	DetectFeature ( &Std[1].edx, MMX_FLAG, processor, "MMX" );
	DetectFeature ( &Std[1].edx, FXSR_FLAG, processor, "FXSR" );
	DetectFeature ( &Std[1].edx, SSE_FLAG, processor, "SSE" );
	DetectFeature ( &Std[1].edx, SSE2_FLAG, processor, "SSE2" );
	DetectFeature ( &Std[1].edx, SS_FLAG, processor, "SS" );
	DetectFeature ( &Std[1].edx, HTT_FLAG, processor, "HTT" );
	DetectFeature ( &Std[1].edx, TM1_FLAG, processor, "TM1" );

	if ( proc[processor]->Manufacturer )
	{
		if ( strcmp ( proc[processor]->Manufacturer, "GenuineIntel" ) == 0 )
		{
			// IA64 and PBE are on Intel where the 3DNow! flags are on AMD
			DetectFeature ( &Std[1].edx, IA64_FLAG, processor, "IA64" );
			DetectFeature ( &Std[1].edx, PBE_FLAG, processor, "PBE" );
		}
	}

	DetectFeature ( &Std[1].ecx, SSE3_FLAG, processor, "SSE3" );
	DetectFeature ( &Std[1].ecx, CX16_FLAG, processor, "CX16" );
	if ( proc[processor]->Manufacturer )
	{
		if ( strcmp ( proc[processor]->Manufacturer, "GenuineIntel" ) == 0 )
		{
			// Intel-only flags
			DetectFeature ( &Std[1].ecx, LAHF_FLAG, processor, "LAHF" );
			DetectFeature ( &Std[1].ecx, DS_CPL_FLAG, processor, "DS_CPL" );
			DetectFeature ( &Std[1].ecx, MONITOR_FLAG, processor, "MONITOR" );
			DetectFeature ( &Std[1].ecx, EIST_FLAG, processor, "EIST" );
			DetectFeature ( &Std[1].ecx, TM2_FLAG, processor, "TM2" );
			DetectFeature ( &Std[1].ecx, CID_FLAG, processor, "CID" );
			DetectFeature ( &Std[1].ecx, SYSCALL_FLAG, processor, "SYSCALL" );
			DetectFeature ( &Std[1].ecx, XTPR_FLAG, processor, "XTPR" );
			DetectFeature ( &Std[1].ecx, XD_FLAG, processor, "XD" );
			DetectFeature ( &Std[1].ecx, EM64T_FLAG, processor, "EM64T" );
		}
		else if ( strcmp ( proc[processor]->Manufacturer, "AuthenticAMD" ) ==
				  0 )
		{
			// AMD-only flags, EDX 8000_0001
			DetectFeature ( &Ext[1].edx, NX_FLAG, processor, "NX" );
			DetectFeature ( &Ext[1].edx, MMXEXT_FLAG, processor, "MMXEXT" );
			DetectFeature ( &Ext[1].edx, FFXSR_FLAG, processor, "FFXSR" );
			DetectFeature ( &Ext[1].edx, RDTSCP_FLAG, processor, "RDTSCP" );
			DetectFeature ( &Ext[1].edx, LM_FLAG, processor, "LM" );
			DetectFeature ( &Ext[1].edx, _3DNOWEXT_FLAG, processor,
							"3DNOWEXT" );
			DetectFeature ( &Ext[1].edx, _3DNOW_FLAG, processor, "3DNOW" );
		}
	}
}

#endif
