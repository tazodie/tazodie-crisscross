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
#include <crisscross/debug.h>
#include <crisscross/darray.h>
#include <crisscross/rbtree.h>
#include <crisscross/llist.h>

using namespace std;
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

    std::map<std::string,int> combined;
    std::map<std::string,int> frequency;
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
             strchr ( thisline, ':' ) )
        {                        // This line does not have a source file location - useless to us

            // Get the size

            char *lastcomma = strrchr ( thisline, ',' );
            if ( lastcomma == 0 ) continue;
            char *ssize = lastcomma + 2;
            int size;
            char unused[32];

            sscanf ( ssize, "%d %s", &size, unused );

            // Get the source file name

            std::string sourcelocation = string(thisline);
            char *colon = strrchr ( thisline, ':' );

            *( colon - 1 ) = '\x0';

            // Put the result into our BTree

            if ( combined.find(sourcelocation) != combined.end() )
                combined[sourcelocation] += size;
            else
                combined[sourcelocation] = size;

            if ( frequency.find(sourcelocation) != frequency.end() )
                frequency[sourcelocation]++;
            else
                frequency[sourcelocation] = 1;

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

    //DArray <int> *sizes = combined.ConvertToDArray ();
    //DArray <std::string> *sources = combined.ConvertIndexToDArray ();
    std::list<std::string> sorted;

    int totalsize = 0;

    std::map<std::string,int>::iterator cit;
    for ( cit = combined.begin(); cit != combined.end (); ++cit )
    {
        std::string newsource = cit->first;
        int newsize = cit->second;

        totalsize += newsize;
        bool inserted = false;

        std::list<std::string>::iterator sit;
        for ( sit = sorted.begin(); sit != sorted.end(); ++sit )
        {

            std::string existingsource = *sit;
            int existingsize = combined.find ( existingsource )->second;

            if ( newsize <= existingsize )
            {
                sorted.insert ( sit, newsource );
                inserted = true;
                break;
            }
        }

        if ( !inserted )
            sorted.push_back ( newsource );
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

        std::list<std::string>::reverse_iterator k;
        for ( k = sorted.rbegin(); k != sorted.rend(); ++k )
        {

            std::string source = *k;
            int size = combined.find ( source )->second;
            int freq = frequency.find ( source )->second;

            if ( size > 2048 )
            {
                fprintf ( output, "%-95s (%d Kbytes in %d leaks)\n", source.c_str(),
                        int ( size / 1024 ), freq );
            }
            else
            {
                fprintf ( output, "%-95s (%d  bytes in %d leaks)\n", source.c_str(), size,
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
int main ( int argc, char **argv )
#endif
{
    int retval = 0;

#ifdef ENABLE_MEMLEAK_STATS
    _CrtMemCheckpoint ( &s1 );
#endif
    g_stderr = new Console ( stderr, NULL );
    g_stdout = new Console ( stdout, NULL );

#ifndef NO_CPP_EXCEPTION_HANDLER
    try
    {
#endif
        retval = RunApplication ( argc, argv );
#ifndef NO_CPP_EXCEPTION_HANDLER
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
