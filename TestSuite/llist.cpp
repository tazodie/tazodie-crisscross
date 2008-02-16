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
#include "llist.h"
#include "testutils.h"

#include <crisscross/llist.h>

using namespace CrissCross::Data;

int TestLList ()
{
    LList<char *> *llist = new LList<char *>();
    if ( !llist ) return 1;

    llist->insert ( newStr ("one") );
    llist->insert ( newStr ("two") );
    llist->insert ( newStr ("three") );
    llist->insert ( newStr ("four") );

    if ( strcmp ( llist->get (0), "one" ) != 0 )
        return 2;

    if ( strcmp ( llist->get (2), "three" ) != 0 )
        return 3;

    if ( strcmp ( llist->get (3), "four" ) != 0 )
        return 4;

    if ( strcmp ( llist->get (1), "two" ) != 0 )
        return 5;

    delete [] llist->get (1);
    llist->remove ( 1 );

    if ( strcmp ( llist->get (0), "one" ) != 0 )
        return 6;

    if ( strcmp ( llist->get (1), "three" ) != 0 )
        return 7;

    if ( strcmp ( llist->get (2), "four" ) != 0 )
        return 8;

    while ( llist->valid (0) )
    {
        delete [] llist->get (0);
        llist->remove (0);
    }
    delete llist;

    return 0;
}
