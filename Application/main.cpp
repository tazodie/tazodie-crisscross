/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
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

#include "header.h"
#include "universal_include.h"

#include "core_filesystem.h"
#include "core_console.h"

#ifdef NETWORK_DIAGNOSTIC
#	include "udpsocket.h"
#endif

#ifdef CPUID_PROGRAM
#	include "core_cpuid.h"
#endif

#ifdef SORT_PROGRAM
#	include "SortClass.h"
#endif

using namespace CrissCross::IO;

#ifdef NETWORK_DIAGNOSTIC
using namespace CrissCross::Network;
#endif

using namespace std;

int
RunApplication ( int argc, char **argv )
{
	int retval = 0;
	CoreConsole *console = new CoreConsole ();

#ifdef NETWORK_DIAGNOSTIC
	
	UDPSocket *socket_out = new UDPSocket();
	UDPSocket *socket_in = new UDPSocket();
	string input = "";
	console->WriteLine ( "Enter an IP to send diagnostic requests to." );
	while ( input.length() == 0 )
		cin >> input;

	retval = socket_out->Bind ( input.c_str(), 9931 );
	retval = socket_in->Listen ( 9931 );

	time_t LastIncomingPacket, Now;
	int InSeqID = -1, OutSeqID = 1, loss = 0, tempSeq, SeqDiff;
	unsigned int len;
	char buffer[128];
	char *buf = NULL;

	// Establish a "connection"
	printf ( "Waiting for initial reply... " );
	while ( true )
	{
		Sleep ( 300 );
		memset ( buffer, 0, sizeof ( buffer ) );
		memcpy ( buffer, &InSeqID, sizeof ( int ) );

		retval = socket_out->Send ( buffer, sizeof ( buffer ) );
		retval = socket_in->Read ( &buf, &len );

		if ( retval == CrissCross::CC_ERR_NONE )
			break;
	}
	delete [] buf;

	// Calm before the storm...
	// Sleep ( 1500 );
	
	time ( &LastIncomingPacket ); // Initial packet does count

	printf ( "Received!\nRunning diagnostic...\n" );
	while ( true )
	{
		memset ( buffer, 0, sizeof ( buffer ) );
		memcpy ( buffer, &OutSeqID, sizeof ( int ) );
		retval = socket_out->Send ( buffer, sizeof ( buffer ) );
		retval = socket_in->Read ( &buf, &len );

		if ( buf )
			memcpy ( &tempSeq, buf, sizeof ( int ) );
		else
			tempSeq = -5;

		if ( tempSeq != -5 && tempSeq != -1 && buf )
		{
			time ( &LastIncomingPacket );
			SeqDiff = tempSeq - InSeqID;
			if ( SeqDiff == 1 )
			{
				// A difference of 1 means we just got the appropriate SeqID.
				InSeqID = tempSeq;
			} else if ( SeqDiff > 1 ) {
				// A difference of > 1 means we skipped one or more.
				if ( InSeqID != -1 )
					loss += SeqDiff - 1;
				InSeqID = tempSeq;
			} else if ( SeqDiff < 1 ) {
				// A difference of < 1 means we got one late.
				loss -= 1;
			}
			delete [] buf;
			buf = NULL;
		}
		time ( &Now );
		printf ( "In: %d Out: %d Loss: %d Last Packet: %lds  \r", InSeqID, OutSeqID, loss, Now - LastIncomingPacket );
		OutSeqID++;
		Sleep(50);
	}

	system ( "pause" );
#endif

#ifdef SORT_PROGRAM
    int ints[1024];
    memset ( ints, 0, sizeof ( ints ) );
    srand ( GetTickCount() );

    for ( int i = 0; i < 1024; i++ )
    {
        ints[i] = rand();
        printf ( "%d ", ints[i] );
    }
    printf ( "\n\n" );
    
    HeapSort<int> *sort = new HeapSort<int>();
    IntegerCompare *comparison = new IntegerCompare();

    sort->Sort ( ints, 1024, comparison );

    for ( int i = 0; i < 1024; i++ )
    {
        printf ( "%d ", ints[i] );
		if ( i > 0 )
			_ASSERT ( ints[i-1] <= ints[i] );
    }
    printf ( "\n\n" );

	system ( "pause" );

    delete sort;
    delete comparison;
#endif

#ifdef CPUID_PROGRAM
    CoreCPUID *cpuid = new CoreCPUID ();
    console->SetColour ( console->FG_RED | console->FG_INTENSITY );
    console->WriteLine ( "======================" );
    console->WriteLine ( "= CPU IDENTIFICATION =" );
    console->WriteLine ( "======================" );
    console->SetColour ( 0 );
    console->WriteLine ();
    
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
    delete cpuid;
#endif
    delete console;

    return 0;
}
