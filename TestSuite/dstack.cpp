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
#include "dstack.h"

#include <crisscross/dstack.h>

using namespace CrissCross::Data;

int TestDStack()
{
	DStack<int> *dstack = new DStack<int>();

	for (int i = 0; i < 16; i++) {
		dstack->push(i);
	}
	
	if (dstack->count() != 16)
		return 1;

	if (dstack->peek() != 15)
		return 2;

	for (int i = 15; i > 0; i--) {
		if (dstack->pop() != i)
			return i + 2;
	}
	
	if (dstack->count() != 1)
		return 18;
		
	dstack->empty();
	if (dstack->count() != 0)
		return 19;

	delete dstack;

	return 0;
}
