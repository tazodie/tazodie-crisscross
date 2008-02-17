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
#include "sha256.h"

using namespace CrissCross::Crypto;

int TestSHA256 ()
{
    SHA256Hash sha256;

    const char *teststring = NULL;
    size_t length = 0;

    /* These tests are from FIPS PUB 180-1 */

    teststring = "abc"; length = strlen (teststring);
    sha256.Process (teststring, length);
    if ( strcmp ( sha256.ToString (), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad" ) )
        return 1;

    teststring = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"; length = strlen (teststring);
    sha256.Process (teststring, length);
    if ( strcmp ( sha256.ToString (), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1" ) )
        return 2;

#ifdef HIGH_INTENSITY
    char *tempstring = new char[1000001];
    memset (tempstring, 'a', 1000000);
    tempstring[1000000] = '\0';
    length = strlen (tempstring);
    sha256.Process (tempstring, length);
    if ( strcmp ( sha256.ToString (), "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0" ) )
        return 3;

    delete [] tempstring;
#endif
        
    SHA256Hash otherhash;
    otherhash.Process ( "cheese", 6 );
    if ( otherhash == sha256 || sha256 == otherhash )
        return 4;
        
    otherhash.Process ( teststring, length );
    if ( otherhash != sha256 || sha256 != otherhash )
        return 5;

    return 0;
}
