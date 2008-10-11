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

int TestDArray()
{
	DArray<int> *darray = new DArray<int>();

	darray->insert(1);
	darray->insert(3);
	darray->insert(5);
	darray->insert(7);
	
	if (darray->used() != 4)
		return 1;

	if (darray->get(0) != 1)
		return 2;

	if (darray->get(3) != 7)
		return 3;

	if (darray->get(1) != 3)
		return 4;

	if (!darray->valid(0))
		return 5;
		
	if (!darray->valid(1))
		return 6;
		
	if (!darray->valid(2))
		return 7;
		
	if (!darray->valid(3))
		return 8;
		
	darray->remove(0);
	if (darray->used() != 3)
		return 9;

	darray->remove(3);
	if (darray->used() != 2)
		return 10;
		
	darray->empty();
	if (darray->used() != 0)
		return 11;

	delete darray;

	return 0;
}
