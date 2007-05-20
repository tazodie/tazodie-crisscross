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
#include "dstack.h"

#include <crisscross/dstack.h>

using namespace CrissCross::Data;

int TestDStack()
{
    DStack<int> *dstack = new DStack<int>();
    
    for ( int i = 0; i < 16; i++ )
    {
        dstack->push ( i );
    }
    
    if ( dstack->peek() != 15 ) return 1;
    
    for ( int i = 15; i >= 0; i-- )
    {
        if ( dstack->pop() != i )
            return i + 1;
    }
    
    delete dstack;
    
    return 0;
}
