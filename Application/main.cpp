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
#include "core_console.h"
#include "core_cpuid.h"
#include "core_socket.h"
#include "core_system.h"

using namespace CrissCross::Network;

LList<CoreSocket *> *sockets;

int
RunApplication ( int argc, char **argv )
{
    CoreConsole *console = new CoreConsole ();
    sockets = new LList<CoreSocket *>;

    console->WriteLine ( "Creating CoreSystem..." );
    CoreSystem *system = new CoreSystem ();
    console->WriteLine ( "Creating CoreSocket..." );
    CoreSocket *socket = new CoreSocket ();
    CoreSocket *tsock = NULL;
    char buffer[10240];

    console->WriteLine ( "CoreSocket is listening on port 3193..." );
    CoreAssert ( socket->Listen ( 3193 ) == 0 );

    while ( true )
    {
        // console->WriteLine ( "Clearing variables..." );
        memset ( buffer, 0, sizeof ( buffer ) );
        tsock = NULL;

        if ( ( tsock = socket->Accept() ) != NULL)
        {
            sockets->PutData ( tsock );
            strcat ( buffer, "Good day, sir." );
            tsock->Send ( buffer, sizeof ( buffer ) );
        }

        for ( int i = 0; sockets->ValidIndex ( i ); i++ )
        {
            tsock = sockets->GetData ( i );
            std::string data = tsock->Read(1024);
            sprintf ( buffer, "Recv ( %d ): '%s'", i, data.c_str() );
            console->WriteLine ( buffer );
        }

        system->ThreadSleep ( 1000 );
    }
    
    delete system;
    delete socket;
    delete console;
    return 0;
}
