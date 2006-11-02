/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006 IO.IN Research
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of the I.O. Independent Network nor the names of its contributors
 *       may be used to endorse or promote products derived from this software without
 *       specific prior written permission.
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

using namespace CrissCross::Data;

template < class T >
DArray < T >::DArray ()
{
    m_stepSize = -1;
    m_arraySize = 0;
    m_shadow = NULL;
    m_array = NULL;
    m_emptyNodes = new DStack<unsigned int>;
    m_emptyNodes->push ( -1 );
}

template < class T >
DArray < T >::DArray ( int _newStepSize )
{
    m_stepSize = _newStepSize;
    m_arraySize = 0;
    m_shadow = NULL;
    m_array = NULL;
    m_emptyNodes = new DStack<unsigned int> ( _newStepSize + 1 );
    m_emptyNodes->push ( -1 );
}

template < class T >
DArray < T >::~DArray ()
{
    Empty ();
    delete m_emptyNodes;
}

template < class T >
void DArray < T >::RebuildStack ()
{
	//  Reset free list

    m_emptyNodes->empty();
    m_emptyNodes->push ( -1 );

	// Step through, rebuilding

	for ( int i = m_arraySize; i >= 0; i-- )
		if ( m_shadow[i] == 0 )
			m_emptyNodes->push ( i );

}

template < class T >
void DArray < T >::Recount()
{
	m_numUsed = 0;
	for ( int i = 0; i < m_arraySize; i++ )
		if ( m_shadow[i] == 1 )
            m_numUsed++;
}

template < class T >
void DArray < T >::SetSize ( int newsize )
{
    if ( newsize > m_arraySize )
    {
        int oldarraysize = m_arraySize;

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && m_shadow )
        {
            memcpy ( &temparray[0], &m_array[0], sizeof ( temparray[0] ) * oldarraysize );
            memcpy ( &tempshadow[0], &m_shadow[0], sizeof ( tempshadow[0] ) * oldarraysize );
        }

        memset ( &temparray[oldarraysize], 0, sizeof ( temparray[0] ) * ( m_arraySize - oldarraysize ) );
        memset ( &tempshadow[oldarraysize], 0, sizeof ( tempshadow[0] ) * ( m_arraySize - oldarraysize ) );

		for ( int a = m_arraySize - 1; a >= oldarraysize; a-- ) 
		{
			m_emptyNodes->push ( a );
		}

        delete [] m_array;
        delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize < m_arraySize )
    {

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && m_shadow )
        {
            memcpy ( &temparray[0], &m_array[0], sizeof ( temparray[0] ) * m_arraySize );
            memcpy ( &tempshadow[0], &m_shadow[0], sizeof ( tempshadow[0] ) * m_arraySize );
        }

        // We may have lost more than one node. It's worth rebuilding over.
        RebuildStack();
        Recount();

        delete [] m_array;
        delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize == m_arraySize )
    {
        // Do nothing
    }
}

template < class T >
void DArray < T >::Grow ()
{
    if ( m_stepSize == -1 )
    {
        // Double array size
        if ( m_arraySize == 0 )
        {
            SetSize ( 1 );
        }
        else
        {
            SetSize ( m_arraySize * 2 );
        }
    }
    else
    {
        // Increase array size by fixed amount
        SetSize ( m_arraySize + m_stepSize );
    }
}

template < class T >
void DArray < T >::SetStepSize ( int _stepSize )
{
    m_stepSize = _stepSize;
}


template < class T >
void DArray < T >::SetStepDouble ()
{
    m_stepSize = -1;
}

template < class T >
int DArray < T >::PutData ( const T & newdata )
{
    int freeslot = GetNextFree();

    m_array[freeslot] = newdata;
    if ( m_shadow[freeslot] == 0 ) m_numUsed++;
    m_shadow[freeslot] = 1;
    
    return freeslot;
}

template < class T >
void DArray < T >::PutData ( const T & newdata, int index )
{

    CoreAssert ( index < m_arraySize && index >= 0 );

    m_array[index] = newdata;
    if ( m_shadow[index] == 0 ) m_numUsed++;
    m_shadow[index] = 1;
}

template < class T >
void DArray < T >::Empty ()
{

    delete [] m_array;
    delete [] m_shadow;

    m_array = NULL;
    m_shadow = NULL;

    m_emptyNodes->empty ();
    m_emptyNodes->push ( -1 );

    m_arraySize = 0;
    m_numUsed = 0;

}

template < class T >
int DArray < T >::GetNextFree()
{
    // WARNING: This function assumes the node returned
    //          will be used by the calling function.

    if ( !m_shadow )
        Grow();

    int freeslot = -2;

    while ( (freeslot = m_emptyNodes->pop() ) != -1 )
    {
        if ( m_shadow[freeslot] == 0 )
            break;
    }

    if ( freeslot == -1 )
	{
        m_emptyNodes->push ( -1 );
        freeslot = m_arraySize;	
		Grow();
	}
    
	if ( m_shadow[freeslot] == 0 )
		m_numUsed++;

    m_shadow[freeslot] = 1;

    return freeslot;
}

template < class T >
T DArray < T >::GetData ( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    return m_array[index];

}

template < class T >
T & DArray < T >::operator []( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    return m_array[index];
}



template < class T >
void DArray < T >::RemoveData ( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    m_emptyNodes->push ( index );

    if ( m_shadow[index] == 1 ) m_numUsed--;
    m_shadow[index] = 0;

}

template < class T >
int DArray < T >::NumUsed ()
{
    return m_numUsed;
}

template < class T >
int DArray < T >::Size ()
{
    return m_arraySize;
}

template < class T >
bool DArray < T >::ValidIndex ( int index )
{

    if ( index >= m_arraySize || index < 0 )
        return false;

    if ( !m_shadow[index] )
        return false;

    return true;

}

template < class T >
int DArray < T >::FindData ( const T & newdata )
{

    for ( int a = 0; a < m_arraySize; ++a )
        if ( m_shadow[a] )
            if ( m_array[a] == newdata )
                return a;

    return -1;

}

#endif
