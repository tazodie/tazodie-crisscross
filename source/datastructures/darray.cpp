/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __included_darray_cpp
#define __included_darray_cpp

#include "core_debug.h"

#include "darray.h"
#include "dstack.h"

template <class T>
DArray <T> :: DArray ()
{

#ifdef USE_STACK
    empty_nodes = new DStack();
	empty_nodes->push ( -1 );
#endif
#ifdef SPECIAL_DEFAULT_CONSTRUCTOR
    stepsize = 32;
#else
	stepsize = 1;
#endif
#ifdef KEEP_COUNT
	count = 0;
#endif
    arraysize = 0;
    array = NULL;
    shadow = NULL;

}

template <class T>
DArray <T> :: DArray ( int newstepsize )
{

#ifdef USE_STACK
    empty_nodes = new DStack(newstepsize + 1);
	empty_nodes->push ( -1 );
#endif
#ifdef KEEP_COUNT
	count = 0;
#endif
    stepsize = newstepsize;
    arraysize = 0;
    array = NULL;
    shadow = NULL;

}

template <class T>
DArray <T> :: ~DArray ()
{

    Empty ();
#ifdef USE_STACK
	delete empty_nodes;
#endif

}

template <class T>
void DArray <T> :: SetSize ( int newsize )
{

	if ( newsize > arraysize ) {

		int oldarraysize = arraysize;

		arraysize = newsize;
		T *temparray = new T [ arraysize ];
		char *tempshadow = new char [ arraysize ];

		if (array && temparray)
		{
			memcpy ( &temparray[0], &array[0], sizeof(temparray[0]) * oldarraysize );
			memcpy ( &tempshadow[0], &shadow[0], sizeof(tempshadow[0]) * oldarraysize );
		}
		memset ( &temparray[oldarraysize], 0, sizeof (temparray[0]) * (arraysize - oldarraysize) );
		memset ( &tempshadow[oldarraysize], 0, sizeof (tempshadow[0]) * (arraysize - oldarraysize) );
#ifdef USE_STACK
		for (int i = oldarraysize + 1; i < arraysize; i++ )
		{
			empty_nodes->push ( i );
		}
#endif

		if ( array ) delete [] array;
		if ( shadow ) delete [] shadow;
		
		array = temparray;
		shadow = tempshadow;

	}
	else if ( newsize < arraysize ) {

		arraysize = newsize;
		T *temparray = new T [arraysize];
		char *tempshadow = new char [arraysize];

		if (array && temparray)
		{
			memcpy ( &temparray[0], &array[0], sizeof(temparray[0]) * arraysize );
			memcpy ( &tempshadow[0], &shadow[0], sizeof(tempshadow[0]) * arraysize );
		}

		// We need to find nodes that are out of the range and eliminate them.
		// At the same time, find any in-use nodes and remove them from the empty_nodes stack.
#ifdef USE_STACK
		DStack *temp_stack = new DStack();
		temp_stack->push(-1);
		int _item = 0;
		while ( (_item = empty_nodes->pop()) > 0 )
			if ( _item < arraysize )
				if ( shadow[_item] == 0 )
					temp_stack->push(_item); // Node is deemed valid.

		empty_nodes->empty(); // Aaaaaaand flush.
		empty_nodes->push(-1);
		while ( (_item = temp_stack->pop()) != -1 )
			empty_nodes->push ( _item );

		delete temp_stack;
#endif
#ifdef KEEP_COUNT
		count = 0; // we're recounting, since we've lost some nodes.
		for ( int i = 0; i < arraysize; i++ )
			if ( shadow[i] == 1 )
				count++;
#endif

		if ( array ) delete [] array;
		if ( shadow ) delete [] shadow;
		
		array = temparray;
		shadow = tempshadow;

	}
	else if ( newsize == arraysize ) {

		// Do nothing

	}

}

template <class T>
void DArray <T> :: SetStepSize ( int newstepsize )
{

	stepsize = newstepsize;

}

template <class T>
int DArray <T> :: PutData ( const T &newdata )
{
#ifdef USE_STACK
	int freespace = 0;

	while ( (freespace = empty_nodes->pop()) != -1 ) {
		if ( shadow )
			if ( shadow[freespace] == 0 )
				break;					// Found one!
	}

#else
    int freespace = -1;					// Find a free space
    
    for ( int a = 0; a < arraysize; ++a ) {
		if ( shadow ) {
			if ( shadow [a] == 0 ) {
				freespace = a;
				break;
			}
		}
    }
#endif

    if ( freespace == -1 ) {			// Must resize the array
#ifdef USE_STACK
		empty_nodes->push ( -1 );		// since we just lost our -1, we need to re-add.
#endif
		freespace = arraysize;
		SetSize ( arraysize + stepsize );
		
    }

    array [freespace] = newdata;
#ifdef KEEP_COUNT
	if ( shadow [freespace] != 1 )		// If the item's already in use, no reason to add one to 'count'.
		count++;
#endif
    shadow [freespace] = 1;
	
	return freespace;

}

template <class T>
void DArray <T> :: PutData ( const T &newdata, int index )
{

    assert ( index < arraysize && index >= 0 );       

    array [index] = newdata;
#ifdef KEEP_COUNT
	if ( shadow [index] != 1 )		// If the item's already in use, no reason to add one to 'count'.
		count++;
#endif

    shadow [index] = 1;
}

template <class T>
void DArray <T> :: Empty ()
{

    if ( array != NULL )
		delete [] array;
    
    if ( shadow != NULL )
		delete [] shadow;
    
    array = NULL;
    shadow = NULL;
#ifdef KEEP_COUNT
	count = 0;
#endif
#ifdef USE_STACK
	empty_nodes->empty();
	empty_nodes->push ( -1 );
#endif

    arraysize = 0;

}

template <class T>
T DArray <T> :: GetData ( int index )
{

	CoreAssert ( shadow[index] != 0 );
    CoreAssert ( index < arraysize && index >= 0 );

    return array [index];

}

template <class T>
T& DArray <T> :: operator [] (int index)
{

	CoreAssert ( shadow[index] != 0 );
    CoreAssert ( index < arraysize && index >= 0 );

    return array [index];
}


template <class T>
void DArray <T> :: ChangeData ( const T &newdata, int index )
{

	CoreAssert ( shadow[index] != 0 );
	CoreAssert ( index < arraysize && index >= 0 );

    PutData ( newdata, index );
    shadow [index] = 1;

}

template <class T>
void DArray <T> :: RemoveData ( int index )
{

	CoreAssert ( shadow[index] != 0 );
	CoreAssert ( index < arraysize && index >= 0 );

#ifdef KEEP_COUNT
	count--;
#endif

#ifdef USE_STACK
	empty_nodes->push ( index );
#endif

    shadow [index] = 0;

}

template <class T>
int DArray <T> :: NumUsed ()
{

    int count = 0;

    for ( int a = 0; a < arraysize; ++a )
		if ( shadow [a] == 1 )
			++count;
    return count;

}

template <class T>
int DArray <T> :: Size (bool guarantee_actual)
{
#ifdef KEEP_COUNT
	if ( guarantee_actual ) return arraysize;
	return (stepsize > 1) ? count : arraysize; // Only need to correct the error generated by larger-than-1 step sizes.
#else
	return arraysize;
#endif
}

template <class T>
bool DArray <T> :: ValidIndex ( int index )
{

    if (index >= arraysize || index < 0 )
		return false;

    if (!shadow [index])
		return false;

    return true;

}

template <class T>
int DArray <T> :: FindData ( const T &newdata )
{

    for ( int a = 0; a < arraysize; ++a )
		if ( shadow [a] )
		    if ( array [a] == newdata )
				return a;

    return -1;

}

#endif
