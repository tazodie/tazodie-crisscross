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
	int int_array[] = {4, 3, 6, 2, 1, 5, 7, 9, 8 };
	HeapSort<int> *hs = new HeapSort<int>();
	hs->Sort ( int_array, sizeof(int_array) );
	for ( int i = 1; i <= 9; i++ )
	{
		if ( int_array[i - 1] != i )
			return i;
	}
	return 0;
}
