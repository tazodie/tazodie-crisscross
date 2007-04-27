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
#include <crisscross/core_io.h>
#include <crisscross/core_debug.h>
#include <crisscross/darray.h>
#include <crisscross/rbtree.h>
#include <crisscross/llist.h>

#include <exception>

using namespace std;
using namespace CrissCross::Debug;
using namespace CrissCross::IO;

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

    RedBlackTree <int> combined;
    RedBlackTree <int> frequency;
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

            BinaryNode<int> *node =
                combined.findNode ( sourcelocation );
            if ( node )
                ( ( int ) node->data ) += size;
            else
                combined.insert ( sourcelocation, size );

            BinaryNode<int> *freq =
                frequency.findNode ( sourcelocation );
            if ( freq )
                ( ( int ) freq->data )++;
            else
                frequency.insert ( sourcelocation, 1 );

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

    for ( int i = 0; i < sources->size (); ++i )
    {
        char *newsource = sources->getData ( i );
        int newsize = sizes->getData ( i );

        totalsize += newsize;
        bool inserted = false;

        for ( int j = 0; j < sorted.size (); ++j )
        {

            char *existingsource = sorted.getData ( j );
            int existingsize = combined.find ( existingsource );

            if ( newsize <= existingsize )
            {

                sorted.insert_at ( newsource, j );
                inserted = true;
                break;

            }

        }

        if ( !inserted )
            sorted.insert_back ( newsource );
    }


    //
    // Open the output file
    //

    if ( sorted.size() )
    {
        FILE *output = fopen ( _outputFilename, "wt" );

        //
        // Print out our sorted list
        // 

		fprintf ( output, "Total recognised memory leaks   : %d Kbytes\n",
			int ( totalsize / 1024 ) );
		fprintf ( output, "Total unrecognised memory leaks : %d Kbytes\n\n",
			int ( unrecognised / 1024 ) );

        for ( int k = sorted.size () - 1; k >= 0; --k )
        {

            char *source = sorted.getData ( k );
            int size = combined.find ( source );
            int freq = frequency.find ( source );

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
        // Clean up

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
    DeleteFileA ( tmpFilename );
#    else
    unlink ( tmpFilename );
#    endif

}
#endif

int
#ifndef TARGET_OS_MACOSX
main ( int argc, char **argv )
#else
CrissCrossInitialise ( int argc, char **argv )
#endif
{
    int retval = 0;

#ifdef ENABLE_MEMLEAK_STATS
    _CrtMemCheckpoint ( &s1 );
#endif
    g_stderr = new CoreConsole ( stderr, NULL );
    g_stdout = new CoreConsole ( stdout, NULL );

#ifdef ENABLE_CREDITS
    g_stdout->SetColour ( g_stdout->FG_GREEN | g_stdout->FG_INTENSITY );
    g_stdout->WriteLine ( "Powered by " CC_LIB_NAME " " CC_LIB_VERSION " (Codename " CC_LIB_CODENAME ")\n    " CC_LIB_URL );
    g_stdout->SetColour ( 0 );
    g_stdout->WriteLine ( CC_LIB_COPYRIGHT );
    g_stdout->WriteLine ();
#endif
    try
    {
        retval = RunApplication ( argc, argv );
	}
	catch ( std::exception& e )
	{
		cout << e.what() << endl;
		return -3;
	}
	catch ( const char *_exception )
	{
		g_stderr->
			WriteLine
			( "An unknown exception has been raised:\n\tDescription: %s",
			  _exception );
		return -2;
	}
	
    delete g_stderr;
    delete g_stdout;

#ifdef DETECT_MEMORY_LEAKS
    AppPrintMemoryLeaks ( "memleak.txt" );
#endif
    return retval;
}

#ifdef TARGET_OS_WINDOWS
int WINAPI
WinMain ( HINSTANCE hInstance,
          HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	main ( __argc, __argv );
}
#endif
