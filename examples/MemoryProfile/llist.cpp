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

using namespace CrissCross::Data;

int ProfileLList()
{
    LList<item_t> *list = new LList<item_t>();
    g_stdout->SetColour ( g_stdout->FG_WHITE | g_stdout->FG_INTENSITY );
    g_stdout->WriteLine ( "LList Statistics" );
    g_stdout->SetColour ();

    size_t usage = 0, i;
    for ( i = 0; i <= MAX_NODES; i += ( i ) ? i : 1 )
    { 
        while ( list->size() < i )
			list->insert ( 0 );
        usage = list->mem_usage();
        g_stdout->WriteLine ( "%3d items: %4d bytes (%4.2lf KB)", list->size(), usage, (double)usage / 1024.0 );
    }

    g_stdout->WriteLine();

    delete list;

    return 0;
}
