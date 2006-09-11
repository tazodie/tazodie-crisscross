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

#include "datastructures/llist.h"
#include "datastructures/rbtree.h"
#include "core_console.h"
#include "core_cpuid.h"
#include "core_system.h"
#include "tcpsocket.h"

using namespace CrissCross::IO;
using namespace CrissCross::Network;
using namespace CrissCross::System;

LList<TCPSocket *> *sockets;
RedBlackTree<int,unsigned long *> *connections_per_host;

int
RunApplication ( int argc, char **argv )
{
    CoreConsole *console = new CoreConsole ();
    sockets = new LList<TCPSocket *>;
    connections_per_host = new RedBlackTree<int,unsigned long *>();

    console->WriteLine ( "Creating CoreSystem..." );
    CoreSystem *system = new CoreSystem ();
    console->WriteLine ( "Creating TCPSocket..." );
    TCPSocket *socket = new TCPSocket ();
    TCPSocket *tsock = NULL;
    int sockets_per_second = 0, retval = 0, breakout = 0;

    console->Write ( "TCPSocket is listening on port 3193... " );
    retval = socket->Listen ( 3193 );
    console->WriteLine ( "retval == %d", retval );
    CoreAssert ( retval == 0 );

    while ( !breakout )
    {
        tsock = NULL;

        sockets_per_second = 0;
        while ( ( tsock = socket->Accept() ) != NULL )
        {
            sockets_per_second++;
            
            u_long host = tsock->GetRemoteHost();
            RedBlackTree<int,u_long *>::nodeType *node;
            node = connections_per_host->findNode ( &host );

            if ( node != NULL )
            {
                node->data++;
                if ( node->data > 5 )
                {
                    socket->Ban ( host );
                    console->WriteLine ( "Connection flood from '%s'!", 
                        tsock->GetRemoteIP() );
                    delete tsock;
                    for ( int i = 0; sockets->ValidIndex ( i ); i++ )
                    {
                        tsock = sockets->GetData(i);
                        if ( tsock->GetRemoteHost() == host )
                        {
                            sockets->RemoveData ( i );
                            delete tsock;
                            i--;
                        }
                    }
                    continue;
                }
            } else {
                connections_per_host->PutData ( &host, 1 );
            }

            sockets->PutData ( tsock );
        }

        for ( int i = 0; sockets->ValidIndex ( i ); i++ )
        {
            tsock = sockets->GetData ( i );
            std::string data;
            int result = tsock->Read ( data, 1024 );
            if ( result == -2 ) // Socket closed.
            {
                sockets->RemoveData ( i );
                delete tsock;
                i--; // This index has changed.
            } else {
		console->WriteLine ( "%s", data.c_str() );
		if ( strcasecmp ( data.c_str(), "die" ) == 0 )
		     breakout = true;
            }
        }

        system->ThreadSleep ( 1000 );
    }

    while ( sockets->ValidIndex ( 0 ) )
    {
        tsock = sockets->GetData ( 0 );
	sockets->RemoveData ( 0 );
        delete tsock;
    }

    delete sockets;
    delete connections_per_host;
    
    delete system;
    delete socket;
    delete console;
    return 0;
}
