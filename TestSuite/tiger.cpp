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
#include "tiger.h"

using namespace CrissCross::Crypto;

int TestTiger ()
{
    TigerHash tiger;

    const char *teststring = NULL;
    size_t length = 0;

    /* These tests are from http://www.cs.technion.ac.il/~biham/Reports/Tiger/tiger2-test-vectors-nessie-format.dat */

    teststring = ""; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "24f0130c63ac933216166e76b1bb925ff373de2d49584e7a" ) )
        return 1;

    teststring = "a"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "abf87e2eeffbbe77fca787f53bf9c82e0978245f7f243e61" ) )
        return 2;

    teststring = "abc"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "f258c1e88414ab2a527ab541ffc5b8bf935f7b951c132951" ) )
        return 3;

    teststring = "message digest"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "951a2078cbf881d91c441e754830cf0df6295aa51aca7f51" ) )
        return 4;

    teststring = "abcdefghijklmnopqrstuvwxyz"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "307de5ee72a414172a0355ccbf120404e9ee7bf32f60110b" ) )
        return 5;

    teststring = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "ee8375a180a6ce8d5186363c8aa32b50cca849dcccfb0f89" ) )
        return 6;

    teststring = "12345678901234567890123456789012345678901234567890123456789012345678901234567890"; length = strlen (teststring);
    tiger.Process (teststring, length);
    if ( strcmp ( tiger.ToString (), "209ffd295579141ce8112fc5848f957afd1bd9dfab0cfa87" ) )
        return 7;

    TigerHash otherhash;
    otherhash.Process ( "cheese", 6 );
    if ( otherhash == tiger || tiger == otherhash )
        return 8;

    otherhash.Process ( teststring, length );
    if ( otherhash != tiger || tiger != otherhash )
        return 9;

    return 0;
}
