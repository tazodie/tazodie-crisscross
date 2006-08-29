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

#include "core_console.h"
#include "core_cpuid.h"

int
RunApplication ( int argc, char **argv )
{
	CoreConsole *console = new CoreConsole (  );
	CoreCPUID *cpuid = new CoreCPUID (  );

	console->SetColour ( console->FG_RED | console->FG_INTENSITY );
	console->Write ( "Red " );
	console->SetColour ( console->FG_GREEN | console->FG_INTENSITY );
	console->Write ( "Green " );
	console->SetColour ( console->FG_BLUE | console->FG_INTENSITY );
	console->Write ( "Blue " );

	console->SetColour ( console->FG_MAGENTA | console->FG_INTENSITY );
	console->Write ( "Magenta " );
	console->SetColour ( console->FG_BROWN | console->FG_INTENSITY );
	console->Write ( "Brown " );
	console->SetColour ( console->FG_CYAN | console->FG_INTENSITY );
	console->Write ( "Cyan " );
	console->SetColour ( console->FG_GRAY | console->FG_INTENSITY );
	console->Write ( "Gray " );
	console->SetColour ( console->FG_WHITE | console->FG_INTENSITY );
	console->Write ( "White " );
	console->SetColour ( 0 );
	console->WriteLine ();

#if 0

	console->SetColour ( console->FG_RED | console->FG_INTENSITY );
	console->WriteLine ( "======================" );
	console->WriteLine ( "= CPU IDENTIFICATION =" );
	console->WriteLine ( "======================" );
	console->SetColour ( 0 );
	console->WriteLine (  );
	
	cpuid->Go ();
	console->WriteLine ( "There are %d processors in the system.",
						 cpuid->GetCPUCount () );

	for ( int i = 0; i < MAX_PROCESSORS; i++ )
	{
		if ( cpuid->proc[i]->Manufacturer != NULL )
		{
			console->WriteLine ( "CPU[%d] Manufacturer: %s", i,
								 cpuid->proc[i]->Manufacturer );
			console->WriteLine ( "CPU[%d] Name: %s", i,
								 cpuid->proc[i]->ProcessorName );
			console->
				WriteLine ( "CPU[%d] Family: %d, Model: %d, Stepping: %d", i,
							cpuid->proc[i]->Family, cpuid->proc[i]->Model,
							cpuid->proc[i]->Stepping );
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
			console->Write ( "CPU[%d] Features: ", i );
			RedBlackTree < Feature *, char *>::nodeType * node =
				cpuid->proc[i]->features.rootNode;
			node->beenThere =
				RedBlackTree < Feature *, char *>::NODE_ITSELF_VISITED;
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
#endif
	delete cpuid;
	delete console;

	return 0;
}
