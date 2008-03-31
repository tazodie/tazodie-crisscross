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

using namespace CrissCross::IO;
using namespace CrissCross::System;

/* 16K of data. Should fit in most L1 caches. */
//#define PREGEN 4096

#define USE_INTEGERS

#ifdef USE_INTEGERS
typedef unsigned long prime_t;
#  define _modulus(x,y) x % y
#else
typedef float prime_t;
#  define _modulus(x,y) (int)fmod (x,y)
#endif

typedef bool ( *isPrimeFunc )( unsigned long _number );

#ifdef PREGEN
prime_t primeCache[PREGEN]; prime_t *primeCachePtr;
#endif

//
// NOTE: The '__asm nop;' lines keep the compiler from marking the function
//		 as a waste of time and optimizing it out.
//

#ifdef TARGET_OS_WINDOWS
#  ifdef PREGEN
bool
isPrime_asm ( unsigned long _candidate )
{
    int retval = 0;
    unsigned int floatpacket1[4] = {0, 0, 0, 0x041f00000};
    unsigned int floatpacket2[4] = {0, 0, 0, 0x041f00000};
    unsigned int floatpacket3 = 0x040000000;
    unsigned int floatpacket4 = 0x040400000;
    __asm {
		mov eax, _candidate
		
		sub esp, 20
		
		// 1 isn't prime
		cmp eax, 1
		je notprime
		
		// Anything else less than four is prime.
		cmp eax, 4
		jb prime
		
		// Anything else divisible by 2 isn't prime.
		test al, 1
		je notprime
		
		movss xmm3, DWORD PTR primeCache
		mov DWORD PTR [esp], eax
		fild DWORD PTR [esp]
		mov DWORD PTR [esp], eax
		fild DWORD PTR [esp]
		mov edx, eax
		shr edx, 31
		fxch st (1)
		fadd QWORD PTR floatpacket2[0+edx*8]
		fstp DWORD PTR [esp+8]
		shr eax, 31
		fadd QWORD PTR floatpacket2[0+eax*8]
		fsqrt
		mov edx, OFFSET primeCache
		movss xmm2, DWORD PTR [esp+8]
		fstp DWORD PTR[esp+8]
		movss xmm0, DWORD PTR [esp+8]
		xorps xmm1, xmm1
		ucomiss xmm3, xmm1
		jp b5_5
		je b5_22
		b5_5 :           movss xmm3, DWORD PTR [edx]
		b5_6 :           comiss xmm0, xmm3
		jb b5_10
		
		movss DWORD PTR [esp], xmm2
		fld DWORD PTR [esp]
		movss DWORD PTR [esp], xmm3
		fld DWORD PTR [esp]
		fxch st (1)
		L19 :            fprem
		fnstsw ax
		sahf
		jp L19
		fstp st (1)
		
		fstp DWORD PTR [esp+8]
		movss xmm3, DWORD PTR [esp+8]
		cvttss2si eax, xmm3
		test eax, eax
		je notprime
		
		movss xmm3, DWORD PTR [edx+4]
		add edx, 4
		ucomiss xmm3, xmm1
		jne b5_6
		jp b5_6
		
		b5_10 : // Why did we exit the loop? Too high a divisor?
		comiss xmm3, xmm0
		jae prime
		
		movss xmm5, DWORD PTR primeCache+PREGEN-2
		ucomiss xmm5, xmm1
		movss xmm4, DWORD PTR floatpacket3
		movaps xmm3, xmm4
		addss xmm3, xmm5
		movss xmm6, DWORD PTR floatpacket4
		jne L20
		jp L20
		movaps xmm3, xmm6
		L20 :            comiss xmm0, xmm3
		jb prime
		
		movss DWORD PTR [esp], xmm2
		fld DWORD PTR [esp]
		fstp DWORD PTR [esp+16]
		b5_13 :          fld DWORD PTR [esp+16]
		movss DWORD PTR [esp], xmm3
		fld DWORD PTR [esp]
		fxch st (1)
		L21 :            fprem
		fnstsw ax
		sahf
		jp L21
		fstp st (1)
		
		fstp DWORD PTR [esp+8]
		movss xmm1, DWORD PTR [esp+8]
		cvttss2si eax, xmm1
		test eax, eax
		je notprime
		
		addss xmm3, xmm4
		comiss xmm0, xmm3
		jae b5_13
		
		b5_22 :          movss xmm3, DWORD PTR [ebx]
		jmp b5_10
		prime :          mov retval, 1
		notprime :       add esp, 20
    }
    return ( retval != 0 );
}
#  endif
#endif

bool
isPrime ( unsigned long _candidate )
{
    prime_t i, limit, next, *p, n;

	/* 1 and 0 aren't prime */
    if ( _candidate < 2 ) return false;

    /* All numbers less than 4 are prime, except '1'. */
    if ( _candidate < 4 ) return true;

    if ( _candidate == 5 ) return true;

    /* All other numbers divisible by 2 are not prime. */
    if ( _candidate % 2 == 0 ) return false;

    /* All other numbers divisible by 5 are not prime. */
    if ( _candidate % 5 == 0 ) return false;

    if ( ( _candidate + 1 ) % 6 != 0 && ( _candidate - 1 ) % 6 != 0 ) return false;

    n = (prime_t)_candidate;

    /*
       if n is composite then it can be factored into two values,
       at least one of which is less than or equal to sqrt(n)
     */
    limit = (prime_t)sqrt ((double)_candidate);

#ifdef PREGEN
    /* Iterate through the prime cache first to check divisors. */
    for ( p = primeCache; *p != 0 && *p <= limit; p++ )
        if ( _modulus ( n, *p ) == 0 ) return false;

    /* Why did we exit the loop? Too high a divisor? */
    if ( *p >= limit ) return true;

    /* No cache hit, we're moving on to odd numbers. */
    if ( primeCache[PREGEN-2] )
        next = primeCache[PREGEN-2] + 2;
    else
#endif
    next = 3;

    /* Now test all other odd numbers up to sqrt(n) */
    for ( i = next; i <= limit; i += 2 ) if ( _modulus ( n, i ) == 0 ) return false;

    return true;
#if defined ( TARGET_CPU_X86 )
#  if defined ( TARGET_COMPILER_VC )
    __asm nop;
#  elif defined ( TARGET_COMPILER_GCC )
    asm ( "nop" );
#  endif
#endif
}

unsigned long
genPrime ( unsigned long _maxToFind, isPrimeFunc _func )
{
    unsigned long count = 0;
    for ( unsigned long num = 1; count < _maxToFind; num++ )
    {
        //CoreAssert ( isPrime ( num ) == _func ( num ) );
        if ( _func ( num ) )
        {
            count++;
        }
    }
    return count;
#if defined ( TARGET_CPU_X86 )
#  if defined ( TARGET_COMPILER_VC )
    __asm nop;
#  elif defined ( TARGET_COMPILER_GCC )
    asm ( "nop" );
#  endif
#endif
}

#ifdef PREGEN
void AddPrimeToCache ( prime_t _prime )
{
    /* inUse is a simple lock for multithreading. */
    static char inUse = 0;
    if ( primeCachePtr - primeCache > PREGEN - 2 )
        return;

    while ( inUse != 0 ) ;
    inUse = 1;
    *primeCachePtr = _prime;
    primeCachePtr++;
    inUse = 0;
}

void PrecalculatePrimes ()
{
    /* Find a predetermined number of primes to use as divisors. */

    unsigned long n;
    memset ( primeCache, 0, sizeof ( primeCache ) );
    primeCachePtr = primeCache;
    for ( n = 3; primeCachePtr - primeCache <= PREGEN - 2; n += 2 )
        if ( isPrime ( n ) )
            AddPrimeToCache ( (prime_t)n );

}
#endif

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

#ifdef USE_INTEGERS
    console->WriteLine ( "Using INTEGER math only.\n" );
#else
    console->WriteLine ( "Using FLOAT math only.\n" );
#endif

#ifdef PREGEN
    console->Write ( "Pregenerating %d primes... ", PREGEN );
    PrecalculatePrimes ();
    console->WriteLine ( "OK\n" );
#endif

#ifdef TARGET_OS_WINDOWS
    HANDLE hThread = GetCurrentThread ();
    HANDLE hProcess = GetCurrentProcess ();
    SetThreadPriority ( hThread, THREAD_PRIORITY_TIME_CRITICAL );
    SetPriorityClass ( hProcess, HIGH_PRIORITY_CLASS );

    console->WriteLine ( "Compiler optimized:" );

#endif

    Stopwatch sw;

#ifdef TARGET_OS_NDSFIRMWARE
    for ( unsigned long i = 10000; i <= 50000; i += 1000 )
#else
    for ( unsigned long i = 100000; i <= 500000; i += 100000 )
#endif
    {
        sw.Start ();
        genPrime ( i, isPrime );
        sw.Stop ();
#ifdef TARGET_OS_NDSFIRMWARE
        console->WriteLine ( "%5d primes: %d.%03ds (%lu PPS)", i, sw.ElapsedMS () / 1000,
                             sw.ElapsedMS () % 1000, (unsigned long)( i / sw.Elapsed ()) );
#else
        console->WriteLine ( "Time for %9d primes: %6.3lf seconds (%lu PPS)", i, sw.Elapsed (),
                             (unsigned long)((double)i / sw.Elapsed ()) );
#endif
    }

#ifdef TARGET_OS_WINDOWS
#  ifdef PREGEN
    console->WriteLine ();
    console->WriteLine ( "Intel C++ Compiler v10 optimized:" );
    for ( unsigned long i = 100000; i <= 500000; i += 100000 )
    {
        sw.Start ();
        genPrime ( i, isPrime_asm );
        sw.Stop ();
        console->WriteLine ( "Time for %9d primes: %6.3lf seconds", i, sw.Elapsed () );
    }
#  endif
#endif

#ifdef TARGET_OS_WINDOWS
    system ("PAUSE");
#endif

    // End your application here.

    delete console;

    return 0;
}
