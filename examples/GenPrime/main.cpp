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

using namespace CrissCross::IO;
using namespace CrissCross::System;
using namespace std;

//
// NOTE: The '__asm nop;' lines keep the compiler from marking the function
//		 as a waste of time and optimizing it out.
//

bool
isPrime ( unsigned long _number )
{
	if ( _number == 1 ) return false;
	if ( _number == 2 ) return true;

	for ( unsigned long div = 3; div < _number; div++ )
	{
		if ( _number % div == 0 )
			return false;
	}

	return true;
#ifdef TARGET_OS_WINDOWS
	__asm nop;
#endif
}

unsigned long
genPrime ( unsigned long _maxToFind )
{
	unsigned long count = 0;
	for ( unsigned long num = 1; count < _maxToFind; num++ )
	{
		if ( isPrime ( num ) )
		{
			count++;
			continue;
		}
	}
	return count;
#ifdef TARGET_OS_WINDOWS
	__asm nop;
#endif
}

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

	Stopwatch sw;
	for ( unsigned long i = 100000; i <= 1000000; i += 100000 )
	{
		sw.Start();
		genPrime ( i );
		sw.Stop();
		console->WriteLine ( "Time for %d primes: %lf seconds", i, sw.Elapsed() );
	}

    // End your application here.

    delete console;

    return 0;
}
