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
#include "testutils.h"
#include "mergesort.h"

#include <crisscross/universal_include.h>
#include <crisscross/darray.h>
#include <crisscross/mergesort.h>

using namespace CrissCross::Data;

int TestMergeSort_IntArray()
{
    int int_array[] = {0, 4, 3, 6, 2, 1, 5, 7, 9, 8 };
    MergeSort<int> *ms = new MergeSort<int>();
    ms->Sort ( int_array, 10 );
    for ( int i = 0; i < 10; i++ )
    {
        if ( int_array[i] != i )
            return i + 1;
    }
    delete ms;
    return 0;
}

int TestMergeSort_DArray()
{
    DArray<int> *darray = new DArray<int>();
    
    darray->insert ( 4 );
    darray->insert ( 2 );
    darray->insert ( 0 );
    darray->insert ( 3 );
    darray->insert ( 1 );
    
    MergeSort<int> *ms = new MergeSort<int>();
    darray->sort ( ms );
    delete ms;
    
    for ( int i = 0; i < 5; i++ )
    {
        if ( darray->get(i) != i )
            return i + 1;
    }

    delete darray;    
    return 0;
}

int TestMergeSort_LList()
{
    LList<int> *llist = new LList<int>();
    
    llist->insert ( 4 );
    llist->insert ( 2 );
    llist->insert ( 0 );
    llist->insert ( 3 );
    llist->insert ( 1 );
    
    MergeSort<int> *ms = new MergeSort<int>();
    llist->sort ( ms );
    delete ms;
    
    for ( int i = 0; i < 5; i++ )
    {
        if ( llist->get(i) != i )
            return i + 1;
    }

    delete llist;    
    return 0;
}
