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

#include "header.h"
#include <crisscross/universal_include.h>

#include <crisscross/core_console.h>
#include <crisscross/core_cpuid.h>

using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

int
RunApplication ( int argc, char **argv )
{
    CoreConsole *console = new CoreConsole ();

    // Begin your application here.

#ifdef ENABLE_CPUID
    CoreCPUID *cpuid = new CoreCPUID ();

    console->SetColour ( console->FG_RED | console->FG_INTENSITY );
    console->WriteLine ( "======================" );
    console->WriteLine ( "= CPU IDENTIFICATION =" );
    console->WriteLine ( "======================" );
    console->SetColour ( 0 );
    console->WriteLine ();

    cpuid->Go ();
    
    // NOTES
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
            if ( cpuid->proc[i]->caches.Size () > 0 )
            {
                console->WriteLine ( "CPU[%d] Caches:", i );
                for ( int j = 0; j < cpuid->proc[i]->caches.Size (); j++ )
                {
                    if ( cpuid->proc[i]->caches.ValidIndex ( j ) )
                        console->Write ( "  %s",
                                         cpuid->proc[i]->caches.
                                         GetData ( j ) );
                }
                console->WriteLine ();
            }

            // Print out CPU features (MMX, SSE, and so on).
            console->Write ( "CPU[%d] Features: ", i );
            RedBlackTree < Feature *, char *>::nodeType * node = cpuid->proc[i]->features.rootNode;
            node->beenThere = RedBlackTree < Feature *, char *>::NODE_ITSELF_VISITED;
            while ( cpuid->proc[i]->features.ValidNode ( node ) )
            {
                if ( node->data->Enabled )
                    console->Write ( "%s ", node->id );
                cpuid->proc[i]->features.getNext ( &node );
            }
            console->WriteLine ();
            console->WriteLine ();
        }
    }

    delete cpuid;
#else
	console->WriteLine ( "Hello, world!" );
#endif

    // End your application here.

#if defined ( TARGET_OS_WINDOWS )
	system ( "pause" );
#endif

    delete console;
    return 0;
}
