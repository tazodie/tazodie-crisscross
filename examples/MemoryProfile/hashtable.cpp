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

using namespace CrissCross::Data;

int ProfileHashTable ()
{
	HashTable<item_t> *table = new HashTable<item_t>();
	g_stdout->SetColour ( g_stdout->FG_WHITE | g_stdout->FG_INTENSITY );
	g_stdout->WriteLine ( "HashTable Statistics" );
	g_stdout->SetColour ();

	size_t usage = 0, i;
	for ( i = 0; i < 10; i++ )
	{
		usage = table->mem_usage ();
		g_stdout->WriteLine ( "%6d items: %7d bytes (%4.2lf KB)", table->size (), usage, (double)usage / 1024.0 );
		table->grow ();
	}

	g_stdout->WriteLine ();

	delete table;

	return 0;
}
