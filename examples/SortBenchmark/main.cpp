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
	sprintf ( format, "%s", "%lf seconds (%I64d clocks)." );
#else
	sprintf ( format, "%s", "%lf seconds (%lld clocks)." );
#endif

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
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );
		
		file.Close();

		console->WriteLine ( "DArray contains %d items.", data.used() );

		console->Write ( "Sorting highly-randomized data:\t" );
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

		console->Write ( "Sorting pre-sorted data:\t" );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

		console->Write ( "Sorting reverse-sorted data:\t" );
		sw.Start();
		rdata.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

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

void
BenchmarkLList ( Sorter<char *> &sorter )
{
	LList<char *> data, rdata;
	Stopwatch sw;
	char buffer[512], format[64];

#ifdef TARGET_OS_WINDOWS
	sprintf ( format, "%s", "%lf seconds (%I64d clocks)." );
#else
	sprintf ( format, "%s", "%lf seconds (%lld clocks)." );
#endif

	TextReader file;

	file.SetLineEndings ( CC_LN_LF );
	file.Open ( "dataset" );

	if ( file.IsOpen() )
	{

		console->Write ( "Successfully opened file, loading data... " );

		sw.Start();

		// Load the file into the data DArray
		while ( file.ReadLine ( buffer, sizeof ( buffer ) ) )
			data.insert ( strdup ( buffer ) );

		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );
		
		file.Close();

		console->WriteLine ( "LList contains %d items.", data.size() );

		console->Write ( "Sorting highly-randomized data:\t" );
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

		console->Write ( "Sorting pre-sorted data:\t" );
		sw.Start();
		data.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

		console->Write ( "Sorting reverse-sorted data:\t" );
		sw.Start();
		rdata.sort ( sorter );
		sw.Stop();
		console->WriteLine ( format, sw.Elapsed(), sw.Clocks() );

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

	BubbleSort<char *> bs;
	QuickSort<char *> qs;
	HeapSort<char *> hs;
	InsertionSort<char *> is;
	CombSort<char *> cs;
	ShellSort<char *> ss;

	console->WriteLine ( "Benchmarking HeapSort..." );
	BenchmarkDArray ( hs );
	BenchmarkLList ( hs );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking CombSort..." );
	BenchmarkDArray ( cs );
	BenchmarkLList ( cs );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking ShellSort..." );
	BenchmarkDArray ( ss );
	BenchmarkLList ( ss );
#ifdef ENABLE_SLOWSORTS
	console->WriteLine ();
	console->WriteLine ( "Benchmarking BubbleSort..." );
	BenchmarkDArray ( bs );
	BenchmarkLList ( bs );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking InsertionSort..." );
	BenchmarkDArray ( is );
	BenchmarkLList ( is );
	console->WriteLine ();
	console->WriteLine ( "Benchmarking QuickSort..." );
	BenchmarkDArray ( qs );
	BenchmarkLList ( qs );
#else
	console->WriteLine ( "Skipping BubbleSort benchmark (ENABLE_SLOWSORTS not defined)..." );
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
