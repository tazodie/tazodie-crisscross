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

#include "header.h"


using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

#ifdef ENABLE_CPUID

    CPUID *cpuid = new CPUID ();

    console->SetColour ( console->FG_RED | console->FG_INTENSITY );
    console->WriteLine ( "======================" );
    console->WriteLine ( "= CPU IDENTIFICATION =" );
    console->WriteLine ( "======================" );
    console->SetColour ( 0 );
    console->WriteLine ();

    cpuid->Go ();
    
#if 0

	// Everything in this #if block is considered unpredictable. We've seen varying results
	// and will reimplement this later if we feel that we've found a better way to detect
	// the processor count (including cores and hyperthreads).
	// For now, just ignore this part.

	// NOTES (old, may be inaccurate)
    // The Virtual count is the number of processors that the operating system sees,
    // but does not take into account whether any of the processors counted are
    // hyperthreads, cores, or truly physical CPUs.
    //
    // If the Physical and Logical counts are equal, the number of Physical/Logical is the 
    // core count, because it's a dual core system.

    console->WriteLine ( "There are %d processors in the system (%d physical, %d logical).",
                         cpuid->GetVirtualCPUCount (),
                         cpuid->GetPhysicalCPUCount (),
                         cpuid->GetLogicalCPUCount () );

	console->WriteLine ( "There are %d cores and %d hardware threads.",
		cpuid->CoresPerPackage(), cpuid->ThreadsSharingCache() );

	console->WriteLine ();

#endif

    for ( int i = 0; i < MAX_PROCESSORS; i++ )
    {
        // Go through each Virtual processor.
        if ( cpuid->proc[i]->Manufacturer != NULL )
        {
            // Print out the manufacturer string
            console->WriteLine ( "CPU[%d] Manufacturer: %s", i,
                                 cpuid->proc[i]->Manufacturer );
            
            // Print out the CPU name string, if available.
            if ( strlen ( cpuid->proc[i]->ProcessorName ) > 0 )
                console->WriteLine ( "CPU[%d] Name: %s", i,
                                     cpuid->proc[i]->ProcessorName );

            // Print out Family/Model/Stepping info.
            console->WriteLine ( "CPU[%d] Family: %d, Model: %d, Stepping: %d", i,
                                 cpuid->proc[i]->Family, cpuid->proc[i]->Model,
                                 cpuid->proc[i]->Stepping );

            // Print out the CPU cache info.
            if ( cpuid->proc[i]->caches.size () > 0 )
            {
                console->WriteLine ( "CPU[%d] Caches:", i );
                for ( size_t j = 0; j < cpuid->proc[i]->caches.size (); j++ )
                {
                    if ( cpuid->proc[i]->caches.valid ( j ) )
                        console->Write ( "  %s",
                                         cpuid->proc[i]->caches.get ( j ) );
                }
                console->WriteLine ();
            }

            // Print out CPU features (MMX, SSE, and so on).
            console->Write ( "CPU[%d] Features: ", i );
            RedBlackNode <std::string, Feature *> *node = cpuid->proc[i]->features.rootNode;
            node->beenThere = RedBlackTree <std::string, Feature *>::NODE_ITSELF_VISITED;
            while ( cpuid->proc[i]->features.valid ( node ) )
            {
                if ( node->data->Enabled )
                {
                    console->Write ( node->id );
                    console->Write ( " " );
                }
                cpuid->proc[i]->features.getNext ( &node );
            }
            console->WriteLine ();
            console->WriteLine ();
        }
    }

    delete cpuid;

#else

    console->WriteLine ( "CPUID isn't supported on your platform or compiler." );

#endif

    // End your application here.

#ifdef TARGET_OS_WINDOWS
    system ( "pause" );
#endif

    delete console;
    return 0;
}
