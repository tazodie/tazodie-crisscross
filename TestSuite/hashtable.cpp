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
#include "rbtree.h"
#include "testutils.h"

#include <crisscross/hashtable.h>

using namespace CrissCross::Data;

int TestHashTable()
{
	HashTable<int> ht;

	char buffer[32];
	const size_t max = 10000;
	for ( size_t i = 0; i < max; i++ )
	{
		sprintf ( buffer, "%lu", i );
		ht.insert ( buffer, max - i );
	}
	ht.print_statistics();

	for ( size_t i = 0; i < max; i += 2 )
	{
		sprintf ( buffer, "%lu", i );
		if ( ht.remove ( buffer ) != 0 )
			return i + 1;
	}
	ht.print_statistics();

	for ( size_t i = 0; i < max; i += 2 )
	{
		sprintf ( buffer, "%lu", i );
		if ( ht.find ( buffer ) != NULL )
			return i + 1;
	}
	ht.print_statistics();

	for ( size_t i = 1; i < max; i += 2 )
	{
		sprintf ( buffer, "%lu", i );
		if ( ht.find ( buffer ) != max - i )
			return i + 1;
	}
	ht.print_statistics();

	return 0;
}

