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
#include "quicksort.h"

#include <crisscross/universal_include.h>
#include <crisscross/darray.h>
#include <crisscross/quicksort.h>

using namespace CrissCross::Data;

int TestQuickSort_IntArray()
{
	int int_array[] = {0, 4, 3, 6, 2, 1, 5, 7, 9, 8 };
	QuickSort<int> *hs = new QuickSort<int>();
	hs->Sort ( int_array, 10 );
	for ( int i = 0; i < 10; i++ )
	{
		if ( int_array[i] != i )
			return i + 1;
	}
	delete hs;
	return 0;
}

int TestQuickSort_DArray()
{
    DArray<int> *darray = new DArray<int>();
    
    darray->insert ( 4 );
    darray->insert ( 2 );
    darray->insert ( 0 );
    darray->insert ( 3 );
    darray->insert ( 1 );
    
    QuickSort<int> *hs = new QuickSort<int>();
    darray->sort ( hs );
    delete hs;
    
    for ( int i = 0; i < 5; i++ )
    {
        if ( darray->getData(i) != i )
            return i + 1;
    }

    delete darray;    
    return 0;
}
