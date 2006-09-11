/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
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

#    include "core_debug.h"

#    include "darray.h"
#    include "dstack.h"

using namespace CrissCross::Data;

template < class T > DArray < T >::DArray ()
{

    empty_nodes = new DStack<int> ();
    empty_nodes->push ( -1 );
    m_stepSize = -1;
    m_arraySize = 0;
    m_array = NULL;
    m_shadow = NULL;

}

template < class T > DArray < T >::DArray ( int _newStepSize )
{

    empty_nodes = new DStack<int> ( _newStepSize + 1 );
    empty_nodes->push ( -1 );

    m_stepSize = _newStepSize;
    m_arraySize = 0;
    m_array = NULL;
    m_shadow = NULL;

}

template < class T > DArray < T >::~DArray ()
{

    Empty ();
    delete empty_nodes;

}

template < class T > void DArray < T >::SetSize ( int newsize )
{

    if ( newsize > m_arraySize )
    {

        int oldarraysize = m_arraySize;

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && temparray )
        {
            memcpy ( &temparray[0], &m_array[0],
                     sizeof ( temparray[0] ) * oldarraysize );
            memcpy ( &tempshadow[0], &m_shadow[0],
                     sizeof ( tempshadow[0] ) * oldarraysize );
        }
        memset ( &temparray[oldarraysize], 0,
                 sizeof ( temparray[0] ) * ( m_arraySize - oldarraysize ) );
        memset ( &tempshadow[oldarraysize], 0,
                 sizeof ( tempshadow[0] ) * ( m_arraySize - oldarraysize ) );

        for ( int i = oldarraysize + 1; i < m_arraySize; i++ )
        {
            empty_nodes->push ( i );
        }

        if ( m_array )
            delete [] m_array;
        if ( m_shadow )
            delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize < m_arraySize )
    {

        m_arraySize = newsize;
        T *temparray = new T[m_arraySize];
        char *tempshadow = new char[m_arraySize];

        if ( m_array && temparray )
        {
            memcpy ( &temparray[0], &m_array[0],
                     sizeof ( temparray[0] ) * m_arraySize );
            memcpy ( &tempshadow[0], &m_shadow[0],
                     sizeof ( tempshadow[0] ) * m_arraySize );
        }

        // We need to find nodes that are out of the range and eliminate them.
        // At the same time, find any in-use nodes and remove them from the empty_nodes stack.
        DStack<int> *temp_stack = new DStack<int> ();

        temp_stack->push ( -1 );
        int _item = 0;

        while ( ( _item = empty_nodes->pop () ) > 0 )
            if ( _item < m_arraySize )
                if ( m_shadow[_item] == 0 )
                    temp_stack->push ( _item );    // Node is deemed valid.

        empty_nodes->empty ();    // Aaaaaaand flush.
        empty_nodes->push ( -1 );
        while ( ( _item = temp_stack->pop () ) != -1 )
            empty_nodes->push ( _item );

        delete temp_stack;

        if ( m_array )
            delete [] m_array;
        if ( m_shadow )
            delete [] m_shadow;

        m_array = temparray;
        m_shadow = tempshadow;

    }
    else if ( newsize == m_arraySize )
    {

        // Do nothing

    }

}

template < class T > void DArray < T >::Grow ()
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

template < class T > void DArray < T >::SetStepSize ( int _stepSize )
{

    m_stepSize = _stepSize;

}

template < class T > int DArray < T >::PutData ( const T & newdata )
{
    int freespace = 0;

    while ( ( freespace = empty_nodes->pop () ) != -1 )
    {
        if ( m_shadow )
            if ( m_shadow[freespace] == 0 )
                break;            // Found one!
    }

    if ( freespace == -1 )
    {                            // Must resize the array
        empty_nodes->push ( -1 );    // since we just lost our -1, we need to re-add.
        freespace = m_arraySize;
        Grow ();
    }

    m_array[freespace] = newdata;

    m_shadow[freespace] = 1;

    return freespace;

}

template < class T >
    void DArray < T >::PutData ( const T & newdata, int index )
{

    CoreAssert ( index < m_arraySize && index >= 0 );

    m_array[index] = newdata;

    m_shadow[index] = 1;
}

template < class T > void DArray < T >::Empty ()
{

    if ( m_array != NULL )
        delete [] m_array;

    if ( m_shadow != NULL )
        delete [] m_shadow;

    m_array = NULL;
    m_shadow = NULL;

    empty_nodes->empty ();
    empty_nodes->push ( -1 );

    m_arraySize = 0;

}

template < class T > T DArray < T >::GetData ( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    return m_array[index];

}

template < class T > T & DArray < T >::operator []( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    return m_array[index];
}


template < class T >
    void DArray < T >::ChangeData ( const T & newdata, int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    PutData ( newdata, index );
    m_shadow[index] = 1;

}

template < class T > void DArray < T >::RemoveData ( int index )
{

    CoreAssert ( m_shadow[index] != 0 );
    CoreAssert ( index < m_arraySize && index >= 0 );

    empty_nodes->push ( index );

    m_shadow[index] = 0;

}

template < class T > int DArray < T >::NumUsed ()
{

    int count = 0;

    for ( int a = 0; a < m_arraySize; ++a )
        if ( m_shadow[a] == 1 )
            ++count;
    return count;

}

template < class T > int DArray < T >::Size ()
{
    return m_arraySize;
}

template < class T > bool DArray < T >::ValidIndex ( int index )
{

    if ( index >= m_arraySize || index < 0 )
        return false;

    if ( !m_shadow[index] )
        return false;

    return true;

}

template < class T > int DArray < T >::FindData ( const T & newdata )
{

    for ( int a = 0; a < m_arraySize; ++a )
        if ( m_shadow[a] )
            if ( m_array[a] == newdata )
                return a;

    return -1;

}

#endif
