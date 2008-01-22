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

//#define ENABLE_SLOWSORTS

using namespace CrissCross::Data;
using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

Console *console = NULL;

void
BenchmarkDArray ( Sorter<char *> &sorter )
{
	DArray<char *> data, rdata;
	Stopwatch sw;
	char buffer[512], format[64];

#ifdef TARGET_OS_WINDOWS
	sprintf ( format, "%s", "%4.3lfs (%I64d clocks)." );
#elif defined ( TARGET_OS_NDSFIRMWARE )
	sprintf ( format, "%s", "%4.3lfs" );
#else
	sprintf ( format, "%s", "%4.3lfs (%lld clocks)." );
#endif

	TextReader file;

	file.SetLineEndings ( CC_LN_LF );
	file.Open ( "dataset" );

	if ( file.IsOpen() )
	{

		data.setStepDouble();
		rdata.setStepDouble();

		console->Write ( "Loading... " );

		sw.Start();

		// Load the file into the data DArray
		while ( file.ReadLine ( buffer, sizeof ( buffer ) ) )
			data.insert ( strdup ( buffer ) );

		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );
		
		file.Close();

		console->WriteLine ( "Loaded %d items.", data.used() );

		console->Write ( "Random: " );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

		// Create a reverse-sorted DArray
		for ( long i = (long)data.size(); i >= 0; i-- )
		{
			if ( data.valid ( i ) )
			{
				rdata.insert ( data.get ( i ) );
			}
		}

		console->Write ( "Pre-sorted: " );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

		console->Write ( "Reverse-sorted: " );
		sw.Start();
		rdata.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

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

		console->WriteLine ( "Dataset not found." );

	}
}

int
RunApplication ( int argc, char **argv )
{
    console = new Console ();

    // Begin your application here.

	BubbleSort<char *> bs;
	QuickSort<char *> qs;
	HeapSort<char *> hs;
	InsertionSort<char *> is;
	CombSort<char *> cs;
	ShellSort<char *> ss;

#ifdef TARGET_OS_NDSFIRMWARE
	chdir ( "/data/SortBenchmark/" );
#endif
	console->WriteLine ( "HeapSort..." );
	BenchmarkDArray ( hs );
	console->WriteLine ();
	console->WriteLine ( "CombSort..." );
	BenchmarkDArray ( cs );
	console->WriteLine ();
	console->WriteLine ( "ShellSort..." );
	BenchmarkDArray ( ss );
	console->WriteLine ();
	console->WriteLine ( "QuickSort..." );
	BenchmarkDArray ( qs );
#ifdef ENABLE_SLOWSORTS
	console->WriteLine ();
	console->WriteLine ( "BubbleSort..." );
	BenchmarkDArray ( bs );
	console->WriteLine ();
	console->WriteLine ( "InsertionSort..." );
	BenchmarkDArray ( is );
	console->WriteLine ();
#else
	console->WriteLine ( "Skipping BubbleSort..." );
	console->WriteLine ( "Skipping InsertionSort..." );
#endif
	console->WriteLine ();


    // End your application here.

#ifdef TARGET_OS_WINDOWS
    system ( "pause" );
#endif

    delete console;
    return 0;
}
