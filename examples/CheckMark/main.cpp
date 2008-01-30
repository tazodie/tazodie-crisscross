/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include "header.h"

#include "adler32.h"
#include "crc32.h"
#include "md5.h"
#include "sha256.h"
#include "random.h"

using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

    CrissCross::Data::DArray<char *> randomStrings;
    CrissCross::System::Stopwatch sw;

    console->WriteLine ( "CheckMark v" CC_LIB_VERSION );
    console->WriteLine ( "A checksum algorithm benchmark." );
    console->WriteLine ();

    /* Generate some data for checksum speed tests. */
    console->Write ( "Generating random data... " );
    sw.Start();
    GenerateRandom ( randomStrings );
    sw.Stop();
    console->WriteLine ( "%5.3lfs", sw.Elapsed() );
    console->WriteLine ();

    console->SetColour ( console->FG_BLUE | console->FG_INTENSITY );
    console->WriteLine ( "Adler32" );
    console->SetColour ();
    sw.Start();
    for ( int r = 0; r < MAX_RUNS; r++ )
        for ( int i = 0; i < DATASET_SIZE; i++ )
        {
            adler32(0,randomStrings.get(i),ENTRY_LENGTH);
        }
    sw.Stop();
    console->WriteLine ( "%lu AdlerMarks", (unsigned long)((double)(DATASET_SIZE * MAX_RUNS) / sw.Elapsed()) );
    console->WriteLine();


    console->SetColour ( console->FG_BLUE | console->FG_INTENSITY );
    console->WriteLine ( "CRC32" );
    console->SetColour ();
    sw.Start();
    for ( int r = 0; r < MAX_RUNS; r++ )
        for ( int i = 0; i < DATASET_SIZE; i++ )
        {
            crc32(randomStrings.get(i),ENTRY_LENGTH);
        }
    sw.Stop();
    console->WriteLine ( "%lu CRCMarks", (unsigned long)((double)(DATASET_SIZE * MAX_RUNS) / sw.Elapsed()) );
    console->WriteLine();


    console->SetColour ( console->FG_BLUE | console->FG_INTENSITY );
    console->WriteLine ( "MD5" );
    console->SetColour ();
    sw.Start();
    for ( int r = 0; r < MAX_RUNS; r++ )
        for ( int i = 0; i < DATASET_SIZE; i++ )
        {
	        MD5_CTX state;
	        MD5Init(&state);
	        MD5Update(&state,(unsigned char *)randomStrings.get(i),ENTRY_LENGTH);
	        MD5Final(&state);
        }
    sw.Stop();
    console->WriteLine ( "%lu MD5Marks", (unsigned long)((double)(DATASET_SIZE * MAX_RUNS) / sw.Elapsed()) );
    console->WriteLine();


    console->SetColour ( console->FG_BLUE | console->FG_INTENSITY );
    console->WriteLine ( "SHA256" );
    console->SetColour ();
    sw.Start();
    for ( int r = 0; r < MAX_RUNS; r++ )
        for ( int i = 0; i < DATASET_SIZE; i++ )
        {
	        sha256_state state;
	        sha256_init(&state);
	        sha256_process(&state,(unsigned char *)randomStrings.get(i),ENTRY_LENGTH);
	        //sha256_done(&state);
        }
    sw.Stop();
    console->WriteLine ( "%lu SHA256Marks", (unsigned long)((double)(DATASET_SIZE * MAX_RUNS) / sw.Elapsed()) );
    console->WriteLine();



    randomStrings.EmptyAndDeleteArray();
    console->WriteLine();

    // End your application here.

#ifdef TARGET_OS_WINDOWS
    system ( "pause" );
#endif

    delete console;
    return 0;
}
