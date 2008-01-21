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

using namespace CrissCross::Data;

int ProfileDArray()
{
    DArray<item_t> *darray = new DArray<item_t>(1);
    g_stdout->SetColour ( g_stdout->FG_WHITE | g_stdout->FG_INTENSITY );
    g_stdout->WriteLine ( "DArray Statistics" );
    g_stdout->SetColour ();

    size_t usage = 0, i;
    for ( i = 0; i <= MAX_NODES; i += ( i ) ? i : 1 )
    { 
        while ( darray->size() < i )
			darray->insert ( 0 );
        usage = darray->mem_usage();
        g_stdout->WriteLine ( "%3d items: %4d bytes (%4.2lf KB)", darray->size(), usage, (double)usage / 1024.0 );
    }

    g_stdout->WriteLine();

    delete darray;

    return 0;
}
