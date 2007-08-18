/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/core_io.h>
#include <crisscross/debug.h>
#include <crisscross/darray.h>
#include <crisscross/rbtree.h>
#include <crisscross/llist.h>

using namespace std;
using namespace CrissCross::Data;
using namespace CrissCross::Debug;
using namespace CrissCross::IO;

Console *g_stderr;
Console *g_stdout;

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

    RedBlackTree<char *,int> combined;
    RedBlackTree<char *,int> frequency;
    int unrecognised = 0;

    //
    // Open the file and start parsing
    //

    std::ifstream memoryfile ( _inputFilename );

    while ( !memoryfile.eof () && !memoryfile.fail() )
    {
        char thisline[1024];

        memoryfile.getline ( thisline, 1024 );

        if ( !strncmp ( thisline, " Data:", 6 ) == 0 &&    // This line is a data line - useless to us
             strchr ( thisline, ':' ) )                    // This line does not have a source file location - useless to us
        {
            // Get the size

            char *lastcomma = strrchr ( thisline, ',' );
            if ( lastcomma == 0 ) continue;
            char *ssize = lastcomma + 2;
            int size;
            char unused[32];

            sscanf ( ssize, "%d %s", &size, unused );

            // Get the source file name

            char *sourcelocation = thisline;
            char *colon = strrchr ( thisline, ':' );

            *( colon - 1 ) = '\x0';

            // Put the result into our BTree

			RedBlackNode<char *,int> *comb = combined.findNode ( sourcelocation );
			RedBlackNode<char *,int> *freq = frequency.findNode ( sourcelocation );

            if ( comb )
                comb->data += size;
            else
                combined.insert ( sourcelocation, size );

            if ( freq )
                freq->data++;
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

    std::list<char *> sorted;

    int totalsize = 0;

	RedBlackNode<char *,int> *node = combined.NULL_NODE;
	combined.getNext ( &node );

    while ( node )
    {
        char *newsource = node->id;
		int newsize = node->data;

        totalsize += newsize;
        bool inserted = false;

        std::list<char *>::iterator sit;
        for ( sit = sorted.begin(); sit != sorted.end(); ++sit )
        {

            char *existingsource = *sit;
            int existingsize = combined.findNode ( existingsource )->data;

            if ( newsize <= existingsize )
            {
                sorted.insert ( sit, newsource );
                inserted = true;
                break;
            }
        }

        if ( !inserted )
            sorted.push_back ( newsource );

		combined.getNext ( &node );
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

        std::list<char *>::reverse_iterator k;
        for ( k = sorted.rbegin(); k != sorted.rend(); ++k )
        {

            char *source = *k;
            int size = combined.findNode ( source )->data;
            int freq = frequency.findNode ( source )->data;

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

#ifdef SDL_APPLICATION
int CrissCrossInitialize ( int argc, char **argv )
#else
	#ifndef TARGET_OS_WINDOWS
		int main ( int argc, char **argv )
	#else
		#ifndef _WINDOWS
			int main ( int argc, char **argv )
		#else
			int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, 
							   LPSTR _cmdLine, int _iCmdShow)
		#endif
	#endif
#endif
{
	int retval = 0;

#ifdef ENABLE_MEMLEAK_STATS
	_CrtMemCheckpoint ( &s1 );
#endif
	g_stderr = new Console ( stderr, NULL );
	g_stdout = new Console ( stdout, NULL );

#ifdef ENABLE_CRASHREPORTS
	__try
#endif
	{
#ifndef _WINDOWS
		retval = RunApplication ( argc, argv );
#else
		retval = RunApplication ( __argc, __argv );
#endif
	}
#ifdef ENABLE_CRASHREPORTS
	__except ( RecordExceptionInfo ( GetExceptionInformation(), "WinMain", CC_LIB_NAME, CC_LIB_VERSION ) ) {}
#endif
    
	delete g_stderr; g_stderr = NULL;
	delete g_stdout; g_stdout = NULL;

#ifdef DETECT_MEMORY_LEAKS
	AppPrintMemoryLeaks ( "memleak.txt" );
#endif
	return retval;
}

#ifdef SDL_APPLICATION
extern "C" {
	int SDL_main ( int argc, char **argv )
	{
		return CrissCrossInitialize(argc,argv);
	}
}
#endif
