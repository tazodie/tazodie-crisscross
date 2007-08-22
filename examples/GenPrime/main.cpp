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

//#define USE_INTEGERS

#ifdef USE_INTEGERS
typedef unsigned long prime_t;
#define _modulus(x,y) x % y
#else
typedef float prime_t;
#define _modulus(x,y) fmod(x,y)
#endif

typedef bool (*isPrimeFunc)( prime_t _number );

#ifdef PREGEN
prime_t primeCache[PREGEN]; prime_t *primeCachePtr;
#endif

//
// NOTE: The '__asm nop;' lines keep the compiler from marking the function
//		 as a waste of time and optimizing it out.
//

bool
isPrime ( prime_t _candidate )
{
	prime_t i, limit, next, *p;

	if ( _candidate == 1 ) return false;

	/* All numbers less than 4 are prime, except '1'. */
	if ( _candidate < 4.0 ) return true;

	/* All other numbers divisble by 2 are not prime. */
	if ( _modulus ( _candidate, 2 ) == 0 ) return false;

	/*
         if n is composite then it can be factored into two values,
         at least one of which is less than or equal to sqrt(n)
	*/
	limit = (prime_t)sqrt((double)_candidate);
	
#ifdef PREGEN
	/* Iterate through the prime cache first to check divisors. */
	for ( p = primeCache; *p != 0 && *p <= limit; p++ )
		if ( _modulus ( _candidate, *p ) == 0 ) return false;

	/* Why did we exit the loop? Too high a divisor? */
	if ( *p >= limit ) return true;

	/* No cache hit, we're moving on to odd numbers. */
	if ( primeCache[PREGEN-2] )
		next = primeCache[PREGEN-2] + 2;
	else
#endif
		next = 3;
	
	/* Now test all other odd numbers up to sqrt(n) */
	for ( i = next; i <= limit; i += 2 ) if ( _modulus ( _candidate, i ) == 0 ) return false;

	return true;
#if defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_CPU_X86 )
	__asm nop;
#endif
}

unsigned long
genPrime ( prime_t _maxToFind, isPrimeFunc _func )
{
	unsigned long count = 0;
	for ( unsigned long num = 1; count < _maxToFind; num++ )
	{
		if ( _func ( (prime_t)num ) )
		{
			count++;
		}
	}
	return count;
#if defined ( TARGET_OS_WINDOWS ) && defined ( TARGET_CPU_X86 )
	__asm nop;
#endif
}

#ifdef PREGEN
void AddPrimeToCache ( prime_t _prime )
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

	prime_t n;
	memset ( primeCache, 0, sizeof ( primeCache ) );
	primeCachePtr = primeCache;
	for ( n = 3; primeCachePtr - primeCache <= PREGEN - 2; n += 2 )
		if ( isPrime ( n ) )
			AddPrimeToCache ( n );
}
#endif

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

#ifdef PREGEN
	PrecalculatePrimes ();
#endif

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
