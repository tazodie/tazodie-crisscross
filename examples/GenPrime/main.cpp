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

bool
isPrime ( int _number )
{
  if ( _number == 2 ) return true;
  for ( int div = 2; div < _number; div++ )
  {
    if ( _number % div == 0 )
      return false;
  }
  return true;
}

int
genPrime ( int _maxToFind )
{
  int count = 0;
  for ( int num = 2; count < _maxToFind; num++ )
  {
    if ( isPrime ( num ) )
    {
      count++;
      continue;
    }
  }
  return count;
}

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

	Stopwatch sw;
	for ( int i = 10000; i < 500000; i += 10000 )
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
