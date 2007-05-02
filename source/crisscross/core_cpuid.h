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

#ifndef __included_core_cpuid_h
#define __included_core_cpuid_h

#ifndef __GNUC__
#include <crisscross/universal_include.h>
#endif

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
	RedBlackTree<std::string, Feature *> features;
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
