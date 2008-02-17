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
#include "md4.h"

using namespace CrissCross::Crypto;

int TestMD4 ()
{
    MD4Hash md4;

    const char *teststring = NULL;
    size_t length = 0;

    /* These tests are from http://tools.ietf.org/html/rfc1319 */

    teststring = ""; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "31d6cfe0d16ae931b73c59d7e0c089c0" ) )
        return 1;

    teststring = "a"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "bde52cb31de33e46245e05fbdbd6fb24" ) )
        return 2;

    teststring = "abc"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "a448017aaf21d8525fc10ae87aa6729d" ) )
        return 3;

    teststring = "message digest"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "d9130a8164549fe818874806e1c7014b" ) )
        return 4;

    teststring = "abcdefghijklmnopqrstuvwxyz"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "d79e1c308aa5bbcdeea8ed63df412da9" ) )
        return 5;

    teststring = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "043f8582f241db351ce627e153e7f0e4" ) )
        return 6;

    teststring = "12345678901234567890123456789012345678901234567890123456789012345678901234567890"; length = strlen (teststring);
    md4.Process (teststring, length);
    if ( strcmp ( md4.ToString (), "e33b4ddc9c38f2199c3e7b164fcc0536" ) )
        return 7;

    MD4Hash otherhash;
    otherhash.Process ( "cheese", 6 );
    if ( otherhash == md4 || md4 == otherhash )
        return 8;
        
    otherhash.Process ( teststring, length );
    if ( otherhash != md4 || md4 != otherhash )
        return 9;
        
    return 0;
}
