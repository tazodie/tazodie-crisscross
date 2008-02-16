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
#include "hashtable.h"

#include <crisscross/hashtable.h>

using namespace CrissCross::Data;

int TestHashTable ()
{
    HashTable<int> ht;

    char buffer[32];
    const unsigned long max = 1000;
    unsigned long i;
    for ( i = 0; i < max; i++ )
    {
        sprintf ( buffer, "%lu", i );
        ht.insert ( buffer, max - i );
    }
    //ht.print_statistics();

    for ( i = 0; i < max; i += 2 )
    {
        sprintf ( buffer, "%lu", i );
        if ( !ht.erase ( buffer ) )
            return i + 1;
    }
    //ht.print_statistics();

    for ( i = 0; i < max; i += 2 )
    {
        sprintf ( buffer, "%lu", i );
        if ( ht.find ( buffer ) != 0 )
            return i + 1;
    }
    //ht.print_statistics();

    for ( i = 1; i < max; i += 2 )
    {
        sprintf ( buffer, "%lu", i );
        if ( ht.find ( buffer ) != (int)( max - i ) )
            return i + 1;
    }
    //ht.print_statistics();

    return 0;
}
