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

#include <crisscross/universal_include.h>

#ifdef ENABLE_CPUID

#    include <crisscross/cpuid.h>
#    include <crisscross/core_io.h>

using namespace CrissCross::System;

#ifdef TARGET_OS_LINUX
#	define DWORD unsigned long
#endif

#    define FPU_FLAG 0x0001
#    define LAHF_FLAG 0x0001
#    define SSE3_FLAG 0x0001
#    define VME_FLAG 0x0002
#    define DE_FLAG 0x0004
#    define MONITOR_FLAG 0x0008
#    define PSE_FLAG 0x0008
#    define DS_CPL_FLAG 0x0010
#    define TSC_FLAG 0x0010
#    define MSR_FLAG 0x0020
#    define VMX_FLAG 0x0020
#    define PAE_FLAG 0x0040
#    define EIST_FLAG 0x0080
#    define MCE_FLAG 0x0080
#    define CX8_FLAG 0x0100
#    define TM2_FLAG 0x0100
#    define APIC_FLAG 0x0200
#    define SSSE3_FLAG 0x0200
#    define CID_FLAG 0x0400
#    define SEP_FLAG 0x0800
#    define SYSCALL_FLAG 0x0800
#    define MTRR_FLAG 0x1000
#    define CX16_FLAG 0x2000
#    define PGE_FLAG 0x2000
#    define MCA_FLAG 0x4000
#    define XTPR_FLAG 0x4000
#    define CMOV_FLAG 0x8000
#    define PAT_FLAG 0x10000
#    define PSE36_FLAG 0x20000
#    define DCA_FLAG 0x40000
#    define PSNUM_FLAG 0x40000
#    define CLFLUSH_FLAG 0x80000
#    define XD_FLAG 0x100000
#    define DTS_FLAG 0x200000
#    define ACPI_FLAG 0x400000
#    define MMX_FLAG 0x800000
#    define FXSR_FLAG 0x1000000
#    define SSE_FLAG 0x2000000
#    define SSE2_FLAG 0x4000000
#    define SS_FLAG 0x8000000
#    define HTT_FLAG 0x10000000
#    define EM64T_FLAG 0x20000000
#    define TM1_FLAG 0x20000000
#    define IA64_FLAG 0x40000000
#    define PBE_FLAG 0x80000000


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
    unsigned long eax;
    unsigned long ebx;
    unsigned long ecx;
    unsigned long edx;
};

struct Registers *Std;
unsigned int StdMax;
struct Registers *Ext;
unsigned int ExtMax;

#if defined ( TARGET_COMPILER_GCC )

/* If the current processor supports the CPUID instruction, execute
   one, with REQUEST in %eax, and set *EAX, *EBX, *ECX, and *EDX to
   the values the 'cpuid' stored in those registers.  Return true if
   the current processor supports CPUID, false otherwise.  */
static bool
call_cpuid (unsigned int request, unsigned long *eax, unsigned long *ebx, unsigned long *ecx, unsigned long *edx)
{
#ifndef TARGET_CPU_X64
  unsigned int pre_change, post_change;
  const unsigned int id_flag = 0x200000;
#endif

  /* This is pretty much the standard way to detect whether the CPUID
     instruction is supported: try to change the ID bit in the EFLAGS
     register.  If we can change it, then the CPUID instruction is
     implemented.  */
#ifndef TARGET_CPU_X64
  asm ("pushfl\n\t"        /* Save %eflags to restore later.  */
       "pushfl\n\t"        /* Push second copy, for manipulation.  */
       "popl %1\n\t"        /* Pop it into post_change.  */
       "movl %1,%0\n\t"        /* Save copy in pre_change.   */
       "xorl %2,%1\n\t"        /* Tweak bit in post_change.  */
       "pushl %1\n\t"        /* Push tweaked copy... */
       "popfl\n\t"        /* ... and pop it into %eflags.  */
       "pushfl\n\t"        /* Did it change?  Push new %eflags... */
       "popl %1\n\t"        /* ... and pop it into post_change.  */
       "popfl"            /* Restore original value.  */
       : "=&r" (pre_change), "=&r" (post_change)
       : "ir" (id_flag));
#endif

  /* If the bit changed, then we support the CPUID instruction.  */
#ifndef TARGET_CPU_X64
  if ((pre_change ^ post_change) & id_flag)
    {
#endif
      asm volatile ("mov %%ebx, %%esi\n\t" /* Save %ebx.  */
            "cpuid\n\t"
            "xchgl %%ebx, %%esi" /* Restore %ebx.  */
            : "=a" (*eax), "=S" (*ebx), "=c" (*ecx), "=d" (*edx)
            : "0" (request)
            : "memory");

      return true;
#ifndef TARGET_CPU_X64
    }
  else
    return false;
#endif
}

#else

static void
call_cpuid ( unsigned int op, unsigned long *_eax, unsigned long *_ebx,
             unsigned long *_ecx, unsigned long *_edx )
{
    __asm
    {
        xor ecx, ecx;
        mov eax, op;
        cpuid;
        mov edi,[_eax];
        mov esi,[_ebx];
        mov[edi], eax;
        mov[esi], ebx;
        mov edi,[_ecx];
        mov esi,[_edx];
        mov[edi], ecx;
        mov[esi], edx;
    }
}

#endif

CPUID::CPUID ()
{
    unsigned int i = 0;

    for ( i = 0; i < MAX_PROCESSORS; i++ )
    {
        proc[i] = new Processor ();
        CoreAssert ( proc[i] );
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

    call_cpuid ( 0x80000000, &Ext[0].eax, &Ext[0].ebx, &Ext[0].ecx, &Ext[0].edx );

    if ( Ext[0].eax < 0x80000004 )
    {
    return;
    }
    else
    {
        ExtMax = Ext[0].eax - 0x80000000;
    }

    for ( i = 0; i <= ExtMax; i++ )
    {
        call_cpuid ( 0x80000000 + i, &Ext[i].eax, &Ext[i].ebx, &Ext[i].ecx, &Ext[i].edx );
    }
}

CPUID::~CPUID ()
{
    // Time to deallocate all the memory we allocated.
    int i = 0, j = 0;

    delete [] Std;
    delete [] Ext;
    for ( i = 0; i < MAX_PROCESSORS; i++ )
    {
        while ( proc[i]->caches.valid ( j ) )
        {
            delete [] proc[i]->caches.get ( j );
            j++;
        }
        j = 0;
        
        RedBlackNode<std::string, Feature *> *node;

        node = proc[i]->features.rootNode;
        node->beenThere = RedBlackTree <std::string, Feature *>::NODE_ITSELF_VISITED;
        while ( proc[i]->features.valid ( node ) )
        {
            delete ( Feature * ) node->data;
            node->data = NULL;
            proc[i]->features.getNext ( &node );
        }
        delete [] (char *)proc[i]->Manufacturer;
        delete [] (char *)proc[i]->ProcessorName;
        delete proc[i];
    }
}

#if 0
// Theoretically obsoleted.
int
CPUID::GetVirtualCPUCount ()
{
    int count = 0, i;

    for ( i = 0; i < MAX_PROCESSORS; i++ )
    {
        if ( proc[i]->Manufacturer )
            count++;
    }
    return count;
}

int
CPUID::GetLogicalCPUCount ()
{
    return proc[0]->LogicalCount;
}

int
CPUID::GetPhysicalCPUCount ()
{
    return proc[0]->PhysicalCount;
}
#endif

#    ifdef TARGET_OS_WINDOWS
DWORD WINAPI
CPUID::GoThread ( LPVOID * params )
#    else
long int
CPUID::GoThread ( int processor )
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
    DetectAPIC ( processor );
    DetectFeatures ( processor );
    DetectCacheInfo ( processor );
    DetectFMS ( processor );
    DetectBrandID ( processor );
    return 0;
}

void
CPUID::Go ()
{
    CoreAssert ( this );
#    ifdef TARGET_OS_WINDOWS
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
                           &params, CREATE_SUSPENDED, &dThread );
        SetThreadAffinityMask ( hThread,
                                ( DWORD ) pow ( ( double ) 2,
                                                ( double ) params.
                                                processor ) );
		Sleep ( 0 ); // Wait for affinity switch.
        SetThreadPriority ( hThread, THREAD_PRIORITY_ABOVE_NORMAL );
		ResumeThread ( hThread );
        WaitForSingleObject ( hThread, INFINITE );
    }
#    elif defined ( TARGET_OS_LINUX ) || defined ( TARGET_OS_MACOSX )
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

    // Disabled until properly integrated.
    //DetectHTTCMP ();
}

void
CPUID::DetectHTTCMP()
{
	unsigned int l, c, p;
	char retval = Count ( &l, &c, &p );
	for ( unsigned int i = 0; i < l; i++ )
	{
		if ( proc[i]->features.find("HTT") == NULL )
		{
			Feature *htt = new Feature();
			htt->Enabled = false;
			proc[i]->features.insert ( "HTT", htt );
		}
		if ( proc[i]->features.find("CMP") == NULL )
		{
			Feature *cmp = new Feature();
			cmp->Enabled = false;
			proc[i]->features.insert ( "CMP", cmp );
		}
		switch ( retval )
		{
		case MULTI_CORE_AND_HT_NOT_CAPABLE:
			proc[i]->features.find ( "HTT" )->Enabled = false;
			proc[i]->features.find ( "CMP" )->Enabled = true;
			break;

		case SINGLE_CORE_AND_HT_NOT_CAPABLE:
			proc[i]->features.find ( "HTT" )->Enabled = false;
			proc[i]->features.find ( "CMP" )->Enabled = false;
			break;

		case SINGLE_CORE_AND_HT_DISABLED:
			proc[i]->features.find ( "HTT" )->Enabled = false;
			proc[i]->features.find ( "CMP" )->Enabled = false;
			break;

		case SINGLE_CORE_AND_HT_ENABLED:
			proc[i]->features.find ( "HTT" )->Enabled = true;
			proc[i]->features.find ( "CMP" )->Enabled = false;
			break;

		case MULTI_CORE_AND_HT_DISABLED:
			proc[i]->features.find ( "HTT" )->Enabled = false;
			proc[i]->features.find ( "CMP" )->Enabled = true;
			break;

		case MULTI_CORE_AND_HT_ENABLED:
			proc[i]->features.find ( "HTT" )->Enabled = true;
			proc[i]->features.find ( "CMP" )->Enabled = true;
			break;
		}
	}
}

void
CPUID::DetectManufacturer ( int processor )
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
CPUID::DetectProcessorName ( int processor )
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
CPUID::DetectCacheInfo ( int processor )
{
    // Compliant with Intel document #241618.

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
CPUID::AddCacheDescription ( int processor, const char *description )
{
    char *temp = new char[strlen ( description ) + 1];

    CoreAssert ( temp );
    strcpy ( temp, description );
    proc[processor]->caches.insert ( temp );
    temp = NULL;
}

void
CPUID::AddCacheData ( int processor, int x )
{
    // Compliant with Intel document #241618.

    x &= 0xff;
    switch ( x )
    {
    case 0:
        break;
    case 0x1:
        AddCacheDescription ( processor, "Instruction TLB: 4KB pages, 4-way set associative, 32 entries\n" );
        break;
    case 0x2:
        AddCacheDescription ( processor, "Instruction TLB: 4MB pages, fully associative, 2 entries\n" );
        break;
    case 0x3:
        AddCacheDescription ( processor, "Data TLB: 4KB pages, 4-way set associative, 64 entries\n" );
        break;
    case 0x4:
        AddCacheDescription ( processor, "Data TLB: 4MB pages, 4-way set associative, 8 entries\n" );
        break;
    case 0x6:
        AddCacheDescription ( processor, "1st-level instruction cache: 8KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x8:
        AddCacheDescription ( processor, "1st-level instruction cache: 16KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0xa:
        AddCacheDescription ( processor, "1st-level data cache: 8KB, 2-way set associative, 32 byte line size\n" );
        break;
    case 0xc:
        AddCacheDescription ( processor, "1st-level data cache: 16KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x22:
        AddCacheDescription ( processor, "3rd-level data cache: 512KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x23:
        AddCacheDescription ( processor, "3rd-level data cache: 1MB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x25:
        AddCacheDescription ( processor, "3rd-level data cache: 2MB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x29:
        AddCacheDescription ( processor, "3rd-level data cache: 4MB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x2C:
        AddCacheDescription ( processor, "1st-level data cache: 32KB, 8-way set associative, 64 byte line size\n" );
        break;
    case 0x30:
        AddCacheDescription ( processor, "1st-level instruction cache: 32KB, 8-way set associative, 64 byte line size\n" );
        break;
    case 0x39:
        AddCacheDescription ( processor, "2nd-level cache: 128KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x3A:
        AddCacheDescription ( processor, "2nd-level cache: 192KB, 6-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x3B:
        AddCacheDescription ( processor, "2nd-level cache: 128KB, 2-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x3C:
        AddCacheDescription ( processor, "2nd-level cache: 256KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x3D:
        AddCacheDescription ( processor, "2nd-level cache: 384KB, 6-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x3E:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x40:
        AddCacheDescription ( processor, "No 2nd-level cache, or if 2nd-level cache exists, no 3rd-level cache\n" );
        break;
    case 0x41:
        AddCacheDescription ( processor, "2nd-level cache: 128KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x42:
        AddCacheDescription ( processor, "2nd-level cache: 256KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x43:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x44:
        AddCacheDescription ( processor, "2nd-level cache: 1MB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x45:
        AddCacheDescription ( processor, "2nd-level cache: 2MB, 4-way set associative, 32 byte line size\n" );
        break;
    case 0x46:
        AddCacheDescription ( processor, "3rd-level cache: 4MB, 4-way set associative, 64 byte line size\n" );
        break;
    case 0x47:
        AddCacheDescription ( processor, "3rd-level cache: 8MB, 4-way set associative, 64 byte line size\n" );
        break;
    case 0x49:
        AddCacheDescription ( processor, "3rd-level cache: 4MB, 16-way set associative, 64 byte line size\n" );
        break;
    case 0x4A:
        AddCacheDescription ( processor, "3rd-level cache: 6MB, 12-way set associative, 64 byte line size\n" );
        break;
    case 0x4B:
        AddCacheDescription ( processor, "3rd-level cache: 8MB, 16-way set associative, 64 byte line size\n" );
        break;
    case 0x4C:
        AddCacheDescription ( processor, "3rd-level cache: 12MB, 12-way set associative, 64 byte line size\n" );
        break;
    case 0x4D:
        AddCacheDescription ( processor, "3rd-level cache: 16MB, 16-way set associative, 64 byte line size\n" );
        break;
    case 0x50:
        AddCacheDescription ( processor, "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 64 entries\n" );
        break;
    case 0x51:
        AddCacheDescription ( processor, "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 128 entries\n" );
        break;
    case 0x52:
        AddCacheDescription ( processor, "Instruction TLB: 4KB, 2MB or 4MB pages, fully associative, 256 entries\n" );
        break;
    case 0x5b:
        AddCacheDescription ( processor, "Data TLB: 4KB or 4MB pages, fully associative, 64 entries\n" );
        break;
    case 0x5c:
        AddCacheDescription ( processor, "Data TLB: 4KB or 4MB pages, fully associative, 128 entries\n" );
        break;
    case 0x5d:
        AddCacheDescription ( processor, "Data TLB: 4KB or 4MB pages, fully associative, 256 entries\n" );
        break;
    case 0x60:
        AddCacheDescription ( processor, "1st-level data cache: 16KB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x66:
        AddCacheDescription ( processor, "1st-level data cache: 8KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x67:
        AddCacheDescription ( processor, "1st-level data cache: 16KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x68:
        AddCacheDescription ( processor, "1st-level data cache: 32KB, 4-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x70:
        AddCacheDescription ( processor, "Trace cache: 12K-uops, 8-way set associative\n" );
        break;
    case 0x71:
        AddCacheDescription ( processor, "Trace cache: 16K-uops, 8-way set associative\n" );
        break;
    case 0x72:
        AddCacheDescription ( processor, "Trace cache: 32K-uops, 8-way set associative\n" );
        break;
    case 0x73:
        AddCacheDescription ( processor, "Trace cache: 64K-uops, 8-way set associative\n" );
        break;
    case 0x78:
        AddCacheDescription ( processor, "2nd-level cache: 1MB, 4-way set associative, 64 byte line size\n" );
        break;
    case 0x79:
        AddCacheDescription ( processor, "2nd-level cache: 128KB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x7a:
        AddCacheDescription ( processor, "2nd-level cache: 256KB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x7b:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x7c:
        AddCacheDescription ( processor, "2nd-level cache: 1MB, 8-way set associative, sectored cache, 64 byte line size\n" );
        break;
    case 0x7d:
        AddCacheDescription ( processor, "2nd-level cache: 2MB, 8-way set associative, 64 byte line size\n" );
        break;
    case 0x7f:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 2-way set associative, 64 byte line size\n" );
        break;
    case 0x82:
        AddCacheDescription ( processor, "2nd-level cache: 256KB, 8-way set associative, 32 byte line size\n" );
        break;
    case 0x83:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 8-way set associative 32 byte line size\n" );
        break;
    case 0x84:
        AddCacheDescription ( processor, "2nd-level cache: 1MB, 8-way set associative, 32 byte line size\n" );
        break;
    case 0x85:
        AddCacheDescription ( processor, "2nd-level cache: 2MB, 8-way set associative, 32 byte line size\n" );
        break;
    case 0x86:
        AddCacheDescription ( processor, "2nd-level cache: 512KB, 4-way set associative, 64 byte line size\n" );
        break;
    case 0x87:
        AddCacheDescription ( processor, "2nd-level cache: 1MB, 8-way set associative, 64 byte line size\n" );
        break;
    case 0xB0:
        AddCacheDescription ( processor, "Instruction TLB: 4KB pages, 4-way set associative, 128 entries\n" );
        break;
    case 0xB3:
        AddCacheDescription ( processor, "Data TLB: 4KB pages, 4-way set associative, 128 entries\n" );
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
CPUID::DetectFMS ( int processor )
{
    // Compliant with Intel document #241618.
    proc[processor]->Family = (char)( ( ( Std[1].eax >> 8 ) + ( Std[1].eax >> 20 ) ) & 0xff );
    proc[processor]->Model = (char)( ( ( ( ( Std[1].eax >> 16 ) & 0xf ) << 4 ) +  ( ( Std[1].eax >> 4 ) & 0xf ) ) & 0xff );
    proc[processor]->Stepping = (char)(Std[1].eax & 0xf);
}

void
CPUID::DetectBrandID ( int processor )
{
    // Compliant with Intel document #241618.
    proc[processor]->BrandID = (char)( Std[1].ebx & 0xff );
}

unsigned int HWD_MTSupported(void)
{
   
	unsigned int Regedx      = Std[1].edx;
	return (Regedx & HTT_FLAG);  
  
}

unsigned int
CPUID::MaxLogicalProcPerPhysicalProc()
{

	unsigned int Regebx = 0;

	if (!HWD_MTSupported()) return (unsigned int) 1;

	Regebx = Std[1].ebx;
	return (unsigned int) ((Regebx & 0x00FF0000) >> 16);

}

unsigned int
CPUID::MaxCorePerPhysicalProc()
{
	unsigned int Regeax = Std[4].eax;
	return (unsigned int)((Regeax & 0xFC000000) >> 26)+1;

}

unsigned int find_maskwidth(unsigned int CountItem)
{
	unsigned int MaskWidth,
				 count = CountItem;
#ifdef TARGET_OS_LINUX
	asm
	(
#ifdef __x86_64__		// define constant to compile  
		"push %%rcx\n\t"		// under 64-bit Linux
		"push %%rax\n\t"
#else
		"pushl %%ecx\n\t"
		"pushl %%eax\n\t"
#endif
//		"movl $count, %%eax\n\t" //done by Assembler below
		"xorl %%ecx, %%ecx"
//		"movl %%ecx, MaskWidth\n\t" //done by Assembler below
		: "=c" (MaskWidth)
		: "a" (count)
//		: "%ecx", "%eax" We don't list these as clobbered because we don't want the assembler
			//to put them back when we are done
	);
	asm
	(
		"decl %%eax\n\t"
		"bsrw %%ax,%%cx\n\t"
		"jz next\n\t"
		"incw %%cx\n\t"
//		"movl %%ecx, MaskWidth\n" //done by Assembler below
		: "=c" (MaskWidth)
		:
	);
	asm
	(
		"next:\n\t"
#ifdef __x86_64__
		"pop %rax\n\t"
		"pop %rcx"		
#else
		"popl %eax\n\t"
		"popl %ecx"		
#endif
	);

#else
	__asm
	{
		mov eax, count
		mov ecx, 0
		mov MaskWidth, ecx
		dec eax
		bsr cx, ax
		jz next
		inc cx
		mov MaskWidth, ecx
next:
		
	}
#endif
	return MaskWidth;
}

//
// Extract the subset of bit field from the 8-bit value FullID.  It returns the 8-bit sub ID value
//
static unsigned char GetNzbSubID(unsigned char FullID,
						  unsigned char MaxSubIDValue,
						  unsigned char ShiftCount)
{
	unsigned int MaskWidth;
	unsigned char MaskBits;

	MaskWidth = find_maskwidth((unsigned int) MaxSubIDValue);
	MaskBits  = (0xff << ShiftCount) ^ 
				((unsigned char) (0xff << (ShiftCount + MaskWidth)));

	return (FullID & MaskBits);
}

unsigned char GetAPIC_ID(void)
{

	unsigned int Regebx = 0;
#ifdef TARGET_OS_LINUX

      asm volatile ("mov $1, %%eax\n\t"
            "mov %%ebx, %%esi\n\t" /* Save %ebx.  */
            "cpuid\n\t"
            "xchgl %%ebx, %%esi" /* Restore %ebx.  */
            : "=S" (Regebx)
            :
            : "%eax","%ecx","%edx","memory");

#else
	__asm
	{
		mov eax, 1
		cpuid
		mov Regebx, ebx
	}
#endif                                

	return (unsigned char) ((Regebx & 0xFF000000) >> 24);

}

unsigned char
CPUID::Count (	unsigned int *TotAvailLogical,
				unsigned int *TotAvailCore,
				unsigned int *PhysicalNum )
{
	unsigned char StatusFlag = 0;
	unsigned int numLPEnabled = 0;
	DWORD dwAffinityMask;
	int j = 0, MaxLPPerCore;
	unsigned char apicID, PackageIDMask;
	unsigned char tblPkgID[256], tblCoreID[256], tblSMTID[256];
	*TotAvailCore = 1;
	*PhysicalNum  = 1;

#ifdef TARGET_OS_LINUX
	//we need to make sure that this process is allowed to run on 
	//all of the logical processors that the OS itself can run on.
	//A process could acquire/inherit affinity settings that restricts the 
	// current process to run on a subset of all logical processor visible to OS.

	// Linux doesn't easily allow us to look at the Affinity Bitmask directly,
	// but it does provide an API to test affinity maskbits of the current process 
	// against each logical processor visible under OS.
	int sysNumProcs = sysconf(_SC_NPROCESSORS_CONF); //This will tell us how many 
	//CPUs are currently enabled.

	//this will tell us which processors this process can run on. 
	cpu_set_t allowedCPUs;	 
	sched_getaffinity(0, sizeof(allowedCPUs), &allowedCPUs);

	for (int i = 0; i < sysNumProcs; i++ )
	{
		if ( CPU_ISSET(i, &allowedCPUs) == 0 )
		{
			StatusFlag = USER_CONFIG_ISSUE;		
			return StatusFlag;
		}
	}
#elif defined ( TARGET_OS_WINDOWS )
	DWORD dwProcessAffinity, dwSystemAffinity;
	GetProcessAffinityMask(GetCurrentProcess(), 
		&dwProcessAffinity,
		&dwSystemAffinity);
	if (dwProcessAffinity != dwSystemAffinity)  // not all CPUs are enabled
	{
		StatusFlag = USER_CONFIG_ISSUE;		
		return StatusFlag;
	}
#else
#	error Not defined for this platform.
#endif

	// Assume that cores within a package have the SAME number of 
	// logical processors.  Also, values returned by
	// MaxLogicalProcPerPhysicalProc and MaxCorePerPhysicalProc do not have
	// to be power of 2.

	MaxLPPerCore = MaxLogicalProcPerPhysicalProc() / MaxCorePerPhysicalProc();
	dwAffinityMask = 1;

#ifdef TARGET_OS_LINUX
	cpu_set_t currentCPU;
	while ( j < sysNumProcs )
	{
		CPU_ZERO(&currentCPU);
		CPU_SET(j, &currentCPU);
		if ( sched_setaffinity (0, sizeof(currentCPU), &currentCPU) == 0 )
		{
			sleep(0);  // Ensure system to switch to the right CPU
#elif defined ( TARGET_OS_WINDOWS )
	while (dwAffinityMask && dwAffinityMask <= dwSystemAffinity)
	{
		if (SetThreadAffinityMask(GetCurrentThread(), dwAffinityMask))
		{
			Sleep(0);  // Ensure system to switch to the right CPU
#else
#	error Not defined for this platform.
#endif
			apicID = GetAPIC_ID();


			// Store SMT ID and core ID of each logical processor
			// Shift vlaue for SMT ID is 0
			// Shift value for core ID is the mask width for maximum logical
			// processors per core

			tblSMTID[j]  = GetNzbSubID(apicID, MaxLPPerCore, 0);
			tblCoreID[j] = GetNzbSubID(apicID, 
				MaxCorePerPhysicalProc(),
				(unsigned char) find_maskwidth(MaxLPPerCore));

			// Extract package ID, assume single cluster.
			// Shift value is the mask width for max Logical per package

			PackageIDMask = (unsigned char) (0xff << 
				find_maskwidth(MaxLogicalProcPerPhysicalProc()));

			tblPkgID[j] = apicID & PackageIDMask;

			numLPEnabled ++;   // Number of available logical processors in the system.

		} // if

		j++;
		dwAffinityMask = 1 << j;
	} // while

	// restore the affinity setting to its original state
#ifdef TARGET_OS_LINUX
	sched_setaffinity (0, sizeof(allowedCPUs), &allowedCPUs);
	sleep(0);
#elif defined ( TARGET_OS_WINDOWS )
	SetThreadAffinityMask(GetCurrentThread(), dwProcessAffinity);
	Sleep(0);
#else
#	error Not defined for this platform.
#endif
	*TotAvailLogical = numLPEnabled;

	//
	// Count available cores (TotAvailCore) in the system
	//
	unsigned char CoreIDBucket[256];
	DWORD ProcessorMask, pCoreMask[256];
	unsigned int i, ProcessorNum;

	CoreIDBucket[0] = tblPkgID[0] | tblCoreID[0];
	ProcessorMask = 1;
	pCoreMask[0] = ProcessorMask;

	for (ProcessorNum = 1; ProcessorNum < numLPEnabled; ProcessorNum++)
	{
		ProcessorMask <<= 1;
		for (i = 0; i < *TotAvailCore; i++)
		{
			// Comparing bit-fields of logical processors residing in different packages
			// Assuming the bit-masks are the same on all processors in the system.
			if ((tblPkgID[ProcessorNum] | tblCoreID[ProcessorNum]) == CoreIDBucket[i])
			{
				pCoreMask[i] |= ProcessorMask;
				break;
			}

		}  // for i

		if (i == *TotAvailCore)   // did not match any bucket.  Start a new one.
		{
			CoreIDBucket[i] = tblPkgID[ProcessorNum] | tblCoreID[ProcessorNum];
			pCoreMask[i] = ProcessorMask;

			(*TotAvailCore)++;	// Number of available cores in the system

		}

	}  // for ProcessorNum


	//
	// Count physical processor (PhysicalNum) in the system
	//
	unsigned char PackageIDBucket[256];
	DWORD pPackageMask[256];

	PackageIDBucket[0] = tblPkgID[0];
	ProcessorMask = 1;
	pPackageMask[0] = ProcessorMask;

	for (ProcessorNum = 1; ProcessorNum < numLPEnabled; ProcessorNum++)
	{
		ProcessorMask <<= 1;
		for (i = 0; i < *PhysicalNum; i++)
		{
			// Comparing bit-fields of logical processors residing in different packages
			// Assuming the bit-masks are the same on all processors in the system.
			if (tblPkgID[ProcessorNum]== PackageIDBucket[i])
			{
				pPackageMask[i] |= ProcessorMask;
				break;
			}

		}  // for i

		if (i == *PhysicalNum)   // did not match any bucket.  Start a new one.
		{
			PackageIDBucket[i] = tblPkgID[ProcessorNum];
			pPackageMask[i] = ProcessorMask;

			(*PhysicalNum)++;	// Total number of physical processors in the system

		}

	}  // for ProcessorNum

	//
	// Check to see if the system is multi-core 
	// Check if the system is hyper-threading
	//
	if (*TotAvailCore > *PhysicalNum) 
	{
		// Multi-core
		if (MaxLPPerCore == 1)
			StatusFlag = MULTI_CORE_AND_HT_NOT_CAPABLE;
		else if (numLPEnabled > *TotAvailCore)
			StatusFlag = MULTI_CORE_AND_HT_ENABLED;
		else StatusFlag = MULTI_CORE_AND_HT_DISABLED;
	}
	else
	{
		// Single-core
		if (MaxLPPerCore == 1)
			StatusFlag = SINGLE_CORE_AND_HT_NOT_CAPABLE;
		else if (numLPEnabled > *TotAvailCore)
			StatusFlag = SINGLE_CORE_AND_HT_ENABLED;
		else StatusFlag = SINGLE_CORE_AND_HT_DISABLED;
	}
	return StatusFlag;
}

void
CPUID::DetectAPIC ( int processor )
{
    // Found at http://www.intel.com/cd/ids/developer/asmo-na/eng/211924.htm
    proc[processor]->APICID = (char)( ( Std[1].ebx & 0xFF000000 ) >> 24 );
}

void
CPUID::DetectFeature ( const unsigned long *_register, long _flag,
                           int _processor, const char *_name )
{
    // Compliant with Intel document #241618.

    Feature *feature = new Feature ();

    feature->Enabled = ( *_register & _flag ) > 0;
    proc[_processor]->features.insert ( ( char * ) _name, feature );
    feature = NULL;
}

void
CPUID::DetectFeatures ( int processor )
{
    // Compliant with Intel document #241618.

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
    DetectFeature ( &Std[1].ecx, VMX_FLAG, processor, "VMX" );
    DetectFeature ( &Std[1].ecx, CX16_FLAG, processor, "CX16" );
    if ( proc[processor]->Manufacturer )
    {
        if ( strcmp ( proc[processor]->Manufacturer, "GenuineIntel" ) == 0 )
        {
            // Intel-only flags
            DetectFeature ( &Ext[1].ecx, LAHF_FLAG, processor, "LAHF" );
            DetectFeature ( &Std[1].ecx, DS_CPL_FLAG, processor, "DS_CPL" );
            DetectFeature ( &Std[1].ecx, MONITOR_FLAG, processor, "MONITOR" );
            DetectFeature ( &Std[1].ecx, EIST_FLAG, processor, "EIST" );
            DetectFeature ( &Std[1].ecx, TM2_FLAG, processor, "TM2" );
            DetectFeature ( &Std[1].ecx, SSSE3_FLAG, processor, "SSSE3" );
            DetectFeature ( &Std[1].ecx, CID_FLAG, processor, "CID" );
            DetectFeature ( &Ext[1].edx, SYSCALL_FLAG, processor, "SYSCALL" );
            DetectFeature ( &Std[1].ecx, XTPR_FLAG, processor, "XTPR" );
            DetectFeature ( &Ext[1].edx, XD_FLAG, processor, "XD" );
            DetectFeature ( &Std[1].ecx, DCA_FLAG, processor, "DCA" );
            DetectFeature ( &Ext[1].edx, EM64T_FLAG, processor, "EM64T" );
        }
        else if ( strcmp ( proc[processor]->Manufacturer, "AuthenticAMD" ) == 0 )
        {
            // AMD-only flags, EDX 8000_0001
            DetectFeature ( &Ext[1].edx, NX_FLAG, processor, "NX" );
            DetectFeature ( &Ext[1].edx, MMXEXT_FLAG, processor, "MMXEXT" );
            DetectFeature ( &Ext[1].edx, FFXSR_FLAG, processor, "FFXSR" );
            DetectFeature ( &Ext[1].edx, RDTSCP_FLAG, processor, "RDTSCP" );
            DetectFeature ( &Ext[1].edx, LM_FLAG, processor, "LM" );
            DetectFeature ( &Ext[1].edx, _3DNOWEXT_FLAG, processor, "3DNOWEXT" );
            DetectFeature ( &Ext[1].edx, _3DNOW_FLAG, processor, "3DNOW" );
        }
    }
}

#endif
