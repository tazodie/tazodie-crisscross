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

#define PREGEN 4096

typedef bool (*isPrimeFunc)( unsigned long  _number );

unsigned long primeCache[PREGEN]; unsigned long *primeCachePtr;

//
// NOTE: The '__asm nop;' lines keep the compiler from marking the function
//		 as a waste of time and optimizing it out.
//

bool
isPrime ( unsigned long _candidate )
{
	unsigned long i, limit, next, *p;

	if ( _candidate == 1 ) return false;

	/* All numbers less than 4 are prime, except '1'. */
	if ( _candidate < 4 ) return true;

	/* All other numbers divisble by 2 are not prime. */
	if ( _candidate % 2 == 0 ) return false;

	/*
         if n is composite then it can be factored into two values,
         at least one of which is less than or equal to sqrt(n)
	*/
	limit = (unsigned long)sqrt((double)_candidate);
	
	/* Iterate through the prime cache first to check divisors. */
	for ( p = primeCache; *p != 0 && *p <= limit; p++ )
		if ( ( _candidate % *p ) == 0 ) return false;

	/* Why did we exit the loop? Too high a divisor? */
	if ( *p >= limit ) return true;

	/* No cache hit, we're moving on to odd numbers. */
	if ( primeCache[PREGEN-2] )
		next = primeCache[PREGEN-2] + 2;
	else
		next = 3;
	
	/* Now test all other odd numbers up to sqrt(n) */
	for ( i = next; i < limit; i += 2 ) if ( _candidate % i == 0 ) return false;

	return true;
#if defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_CPU_X86 )
	__asm nop;
#endif
}

unsigned long
genPrime ( unsigned long _maxToFind, isPrimeFunc _func )
{
	unsigned long count = 0;
	for ( unsigned long num = 1; count < _maxToFind; num++ )
	{
		if ( _func ( num ) )
		{
			count++;
		}
	}
	return count;
#if defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_CPU_X86 )
	__asm nop;
#endif
}


void AddPrimeToCache ( unsigned long _prime )
{
	static char inUse = 0;
	if ( primeCachePtr - primeCache > PREGEN - 2 )
		return;
	while ( inUse != 0 );
	inUse = 1;
	*primeCachePtr = _prime;
	primeCachePtr++;
	inUse = 0;
}

void PrecalculatePrimes()
{
	/* Find a predetermined number of primes to use as divisors. */

	unsigned long n;
	memset ( primeCache, 0, sizeof ( primeCache ) );
	primeCachePtr = primeCache;
	for ( n = 3; primeCachePtr - primeCache <= PREGEN - 2; n += 2 )
		if ( isPrime ( n ) )
			AddPrimeToCache ( n );
}

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

	PrecalculatePrimes ();

#ifdef TARGET_OS_WINDOWS
	HANDLE hThread = GetCurrentThread();
	HANDLE hProcess = GetCurrentProcess();
	SetThreadPriority ( hThread, THREAD_PRIORITY_TIME_CRITICAL );
	SetPriorityClass ( hProcess, HIGH_PRIORITY_CLASS );
#endif

	Stopwatch sw;

	for ( unsigned long i = 100000; i <= 1000000; i += 100000 )
	{
		sw.Start();
		genPrime ( i, isPrime );
		sw.Stop();
		console->WriteLine ( "Time for %9d primes: %6.3lf seconds", i, sw.Elapsed() );
	}

    // End your application here.

    delete console;

    return 0;
}
