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
#include "darray.h"

#include <crisscross/darray.h>

using namespace CrissCross::Data;

int TestDArray ()
{
    DArray<int> *darray = new DArray<int>();

    darray->insert ( 1 );
    darray->insert ( 3 );
    darray->insert ( 5 );
    darray->insert ( 7 );

    if ( darray->get (0) != 1 )
        return 1;

    if ( darray->get (3) != 7 )
        return 2;

    if ( darray->get (1) != 3 )
        return 3;

    delete darray;

    return 0;
}
