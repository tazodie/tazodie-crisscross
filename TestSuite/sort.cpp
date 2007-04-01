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

#include "sort.h"

#include <crisscross/universal_include.h>
#include <crisscross/sortclass.h>

using namespace CrissCross::Data;

int TestHeapSort()
{
	int int_array[] = {0, 4, 3, 6, 2, 1, 5, 7, 9, 8 };
	HeapSort<int> *hs = new HeapSort<int>();
	hs->Sort ( int_array, 10 );
	for ( int i = 0; i < 10; i++ )
	{
		if ( int_array[i] != i )
			return i;
	}
	return 0;
}
