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

#include "universal_include.h"
#include "core_exception.h"
#include "core_io.h"
#include "core_debug.h"

#if defined ( ENABLE_DEBUGLOG )
#    include "core_debuglog.h"
#endif

#include "datastructures/rbtree.h"
#include "datastructures/llist.h"

#include <exception>

using namespace std;
using namespace CrissCross::IO;

#if defined ( ENABLE_DEBUGLOG )
using namespace CrissCross::Debug;
CoreDebugLog *g_debuglog;
#endif

CoreConsole *g_stderr;
CoreConsole *g_stdout;

#ifdef DETECT_MEMORY_LEAKS

#    pragma warning ( disable: 4312 )

#    ifdef ENABLE_MEMLEAK_STATS
_CrtMemState s1, s2, s3;
#    endif

void
ParseMemoryLeakFile ( const char *_inputFilename,
                      const char *_outputFilename )
{

    //
    // Start up
    //

    RedBlackTree < int, char *>combined;
    RedBlackTree < int, char *>frequency;
    int unrecognised = 0;

    //
    // Open the file and start parsing
    //

    std::ifstream memoryfile ( _inputFilename );

    while ( !memoryfile.eof () )
    {
        char thisline[256];

        memoryfile.getline ( thisline, 256 );

        if ( !strncmp ( thisline, " Data:", 6 ) == 0 &&    // This line is a data line - useless to us
             strchr ( thisline, ':' ) )
        {                        // This line does not have a source file location - useless to us

            // Get the size

            char *lastcomma = strrchr ( thisline, ',' );
            char *ssize = lastcomma + 2;
            int size;
            char unused[32];

            sscanf ( ssize, "%d %s", &size, unused );

            // Get the source file name

            char *sourcelocation = thisline;
            char *colon = strrchr ( thisline, ':' );

            *( colon - 1 ) = '\x0';

            // Put the result into our BTree

            RedBlackTree < int, char *>::nodeType * btree =
                combined.findNode ( sourcelocation );
            if ( btree )
                ( ( int ) btree->data ) += size;
            else
                combined.PutData ( sourcelocation, size );

            RedBlackTree < int, char *>::nodeType * freq =
                frequency.findNode ( sourcelocation );
            if ( freq )
                ( ( int ) freq->data )++;
            else
                frequency.PutData ( sourcelocation, 1 );

        }
        else
        {
            char *lastcomma = strrchr ( thisline, ',' );

            if ( lastcomma )
            {

                char *ssize = lastcomma + 2;
                int size;
                char unused[32];

                sscanf ( ssize, "%d %s", &size, unused );

                unrecognised += size;
            }
        }
    }

    memoryfile.close ();


    //
    // Sort the results into a list
    //

    DArray < int >*sizes = combined.ConvertToDArray ();
    DArray < char *>*sources = combined.ConvertIndexToDArray ();
    LList < char *>sorted;
    int totalsize = 0;

    for ( int i = 0; i < sources->Size (); ++i )
    {
        char *newsource = sources->GetData ( i );
        int newsize = sizes->GetData ( i );

        totalsize += newsize;
        bool inserted = false;

        for ( int j = 0; j < sorted.Size (); ++j )
        {

            char *existingsource = sorted.GetData ( j );
            int existingsize = combined.GetData ( existingsource );

            if ( newsize <= existingsize )
            {

                sorted.PutDataAtIndex ( newsource, j );
                inserted = true;
                break;

            }

        }

        if ( !inserted )
            sorted.PutDataAtEnd ( newsource );
    }


    //
    // Open the output file
    //

    if ( sorted.Size() )
    {
        FILE *output = fopen ( _outputFilename, "wt" );

        //
        // Print out our sorted list
        // 

        fprintf ( output, "Total recognised memory leaks   : %d Kbytes\n",
                int ( totalsize / 1024 ) );
        fprintf ( output, "Total unrecognised memory leaks : %d Kbytes\n\n",
                int ( unrecognised / 1024 ) );

        for ( int k = sorted.Size () - 1; k >= 0; --k )
        {

            char *source = sorted.GetData ( k );
            int size = combined.GetData ( source );
            int freq = frequency.GetData ( source );

            if ( size > 2048 )
            {
                fprintf ( output, "%-95s (%d Kbytes in %d leaks)\n", source,
                        int ( size / 1024 ), freq );
            }
            else
            {
                fprintf ( output, "%-95s (%d  bytes in %d leaks)\n", source, size,
                        freq );
            }
        }


        //
        // Clear up

        fclose ( output );
    }

    delete sources;
    delete sizes;
}


void
AppPrintMemoryLeaks ( char *_filename )
{
    //
    // Print all raw memory leak data to a temporary file

#    ifdef ENABLE_MEMLEAK_STATS
    _CrtMemCheckpoint ( &s2 );
#    endif

    char tmpFilename[512];

    sprintf ( tmpFilename, "%s.tmp", _filename );

    OFSTRUCT ofstruct;
    HFILE file = OpenFile ( tmpFilename,
                            &ofstruct,
                            OF_CREATE );

    _CrtSetReportMode ( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile ( _CRT_WARN, ( _HFILE ) file );

    _CrtDumpMemoryLeaks ();
#    ifdef ENABLE_MEMLEAK_STATS
    _CrtMemDifference ( &s3, &s1, &s2 );
    _CrtMemDumpStatistics ( &s3 );
#    endif

    _lclose ( file );


    //
    // Parse the temp file into a sensible format

    ParseMemoryLeakFile ( tmpFilename, _filename );



    //
    // Delete the temporary file

#    ifdef TARGET_OS_WINDOWS
    DeleteFile ( tmpFilename );
#    else
    unlink ( tmpFilename );
#    endif

}
#endif


#if 0
int APIENTRY
WinMain ( HINSTANCE hInstance,
          HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
#else
int
main ( int argc, char **argv )
{
#endif
    /* TODO: Get proper command line parameters for Windows apps */
    int retval = 0;

#ifdef ENABLE_MEMLEAK_STATS
    _CrtMemCheckpoint ( &s1 );
#endif
    g_stderr = new CoreConsole ( stderr );
    g_stdout = new CoreConsole ( stdout );
#ifdef ENABLE_DEBUGLOG
    g_debuglog = new CoreDebugLog ( APP_NAME, APP_VERSION, APP_URL, "bugs@uplinklabs.net", false );
    g_debuglog->Write ( g_debuglog->BUG_LEVEL_INFO, "Initializing" );
#endif

#ifdef ENABLE_CREDITS
    g_stdout->SetColour ( g_stdout->FG_GREEN | g_stdout->FG_INTENSITY );
    g_stdout->WriteLine ( "Powered by " APP_NAME ", " APP_URL );
    g_stdout->SetColour ( 0 );
    g_stdout->WriteLine ( APP_COPYRIGHT_CONSOLE );
    g_stdout->WriteLine ();
#endif
    try
    {
#if 0
        retval = RunApplication ( 0, NULL );
#else
        retval = RunApplication ( argc, argv );
#endif
    }
    catch ( std::exception& e )
    {
        cout << e.what() << endl;
        return -3;
    }
    catch ( CoreException * e )
    {
        g_stderr->
            WriteLine
            ( "\nA CoreException has been raised.\n\tFile: %s\n\tLine: %d\n\tDescription: %s\n",
              e->ShowFile (), e->ShowLine (), e->ShowReason () );
        return -1;
    }
    catch ( const char *_exception )
    {
        g_stderr->
            WriteLine
            ( "An unknown exception has been raised:\n\tDescription: %s",
              _exception );
        return -2;
    }
    
#ifdef ENABLE_DEBUGLOG

    g_debuglog->Write ( g_debuglog->BUG_LEVEL_INFO, "Exiting", "" );

    // Below commented only because I hate cleaning out .log files. Uncomment if you wish. -- Steven
    // g_debuglog->Save();

    delete g_debuglog;

#endif

    delete g_stderr;
    delete g_stdout;

#ifdef DETECT_MEMORY_LEAKS
    AppPrintMemoryLeaks ( "memleak.txt" );
#endif
    return retval;
}
