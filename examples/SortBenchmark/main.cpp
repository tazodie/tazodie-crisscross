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

#include "header.h"

//#define ENABLE_SLOWSORTS

using namespace CrissCross::Data;
using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

Console *console = NULL;

void
Benchmark ( Sorter<char *> &sorter )
{
	DArray<char *> data, rdata;
	Stopwatch sw;
	char buffer[512];

	TextReader file;

	file.SetLineEndings ( CC_LN_LF );
	file.Open ( "dataset" );

	if ( file.IsOpen() )
	{

		data.setStepDouble();
		rdata.setStepDouble();

		console->Write ( "Successfully opened file, loading data... " );

		sw.Start();

		// Load the file into the data DArray
		while ( file.ReadLine ( buffer, sizeof ( buffer ) ) )
			data.insert ( strdup ( buffer ) );

		sw.Stop();
		console->WriteLine ( "%lf seconds.", sw.Elapsed() );
		
		file.Close();

		console->WriteLine ( "DArray contains %d items.", data.used() );

		console->Write ( "Sorting highly-randomized data:\t" );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( "%lf seconds.", sw.Elapsed() );

		// Create a reverse-sorted DArray
		for ( long i = (long)data.size(); i >= 0; i-- )
		{
			if ( data.valid ( i ) )
			{
				rdata.insert ( data.get ( i ) );
			}
		}

		console->Write ( "Sorting pre-sorted data:\t" );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( "%lf seconds.", sw.Elapsed() );

		console->Write ( "Sorting reverse-sorted data:\t" );
		sw.Start();
		rdata.sort ( sorter );
		sw.Stop();
		console->WriteLine ( "%lf seconds.", sw.Elapsed() );

		console->WriteLine ();

		for ( size_t i = 0; i < data.size(); i++ )
		{
			if ( data.valid ( i ) )
			{
				free ( data.get ( i ) );
				data.remove ( i );
			}
		}
		data.empty ();
		rdata.empty ();

	} else {

		console->WriteLine ( "File 'dataset' couldn't be opened... Is it in this directory?" );

	}
}

int
RunApplication ( int argc, char **argv )
{
    console = new Console ();

    // Begin your application here.

	QuickSort<char *> qs;
	HeapSort<char *> hs;
	InsertionSort<char *> is;
	CombSort<char *> cs;
	ShellSort<char *> ss;

	console->WriteLine ( "Benchmarking HeapSort..." );
	Benchmark ( hs );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking CombSort..." );
	Benchmark ( cs );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking ShellSort..." );
	Benchmark ( ss );
#ifdef ENABLE_SLOWSORTS
	console->WriteLine ();
	console->WriteLine ( "Benchmarking InsertionSort..." );
	Benchmark ( is );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking QuickSort..." );
	Benchmark ( qs );
#else
	console->WriteLine ( "Skipping InsertionSort benchmark (ENABLE_SLOWSORTS not defined)..." );
	console->WriteLine ( "Skipping QuickSort benchmark (ENABLE_SLOWSORTS not defined)..." );
#endif
	console->WriteLine ();


    // End your application here.

#ifdef TARGET_OS_WINDOWS
    system ( "pause" );
#endif

    delete console;
    return 0;
}
