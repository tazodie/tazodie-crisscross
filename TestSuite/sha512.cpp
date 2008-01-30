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
#include "sha512.h"

using namespace CrissCross::Crypto;

int TestSHA512()
{
	SHA512Hash sha512;

    const char *teststring = NULL;
    size_t length = 0;

    /* These tests are from FIPS PUB 180-1 */

    teststring = "abc"; length = strlen(teststring);
    sha512.Process(teststring, length);
    if ( strcmp ( sha512.ToString(), "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f" ) )
        return 1;

    teststring = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"; length = strlen(teststring);
    sha512.Process(teststring, length);
    if ( strcmp ( sha512.ToString(), "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909" ) )
        return 2;

    char *tempstring = new char[1000001];
    memset(tempstring, 'a', 1000000);
    tempstring[1000000] = '\0';
    length = strlen(tempstring);
    sha512.Process(tempstring, length);
    if ( strcmp ( sha512.ToString(), "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973ebde0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b" ) )
        return 3;
    delete [] tempstring;
    
    return 0;
}

