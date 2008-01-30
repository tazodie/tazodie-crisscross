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
#include "sha1.h"

using namespace CrissCross::Crypto;

int TestSHA1()
{
	SHA1Hash sha1;

    const char *teststring = NULL;
    size_t length = 0;

    /* These tests are from FIPS PUB 180-1 */

    teststring = "abc"; length = strlen(teststring);
    sha1.Process(teststring, length);
    if ( strcmp ( sha1.ToString(), "a9993e364706816aba3e25717850c26c9cd0d89d" ) )
        return 1;

    teststring = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"; length = strlen(teststring);
    sha1.Process(teststring, length);
    if ( strcmp ( sha1.ToString(), "84983e441c3bd26ebaae4aa1f95129e5e54670f1" ) )
        return 2;

    char *tempstring = new char[1000001];
    memset(tempstring, 'a', 1000000);
    tempstring[1000000] = '\0';
    length = strlen(tempstring);
    sha1.Process(tempstring, length);
    if ( strcmp ( sha1.ToString(), "34aa973cd4c4daa4f61eeb2bdbad27316534016f" ) )
        return 3;
    delete [] tempstring;
    
    return 0;
}

