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

#ifndef __included_llist_cpp
#define __included_llist_cpp

#    include "llist.h"

using namespace CrissCross::Data;

template < class T > LListItem < T >::LListItem ()
{
    m_next = NULL;
    m_previous = NULL;
}


template < class T > LListItem < T >::~LListItem ()
{
}


template < class T > LList < T >::LList ()
{
    m_first = NULL;
    m_last = NULL;
    m_numItems = 0;
    m_previous = NULL;
    m_previousIndex = -1;
}


template < class T > LList < T >::~LList ()
{
    Empty ();
}


template < class T > LList < T >::LList ( const LList < T > &source ):
m_first ( NULL ),
m_last ( NULL ),
m_previous ( NULL ),
m_previousIndex ( -1 ),
m_numItems ( 0 )
{
    for ( int i = 0; i < source.Size (); i++ )
    {
        PutDataAtEnd ( source.GetData ( i ) );
    }
}


template < class T >
    LList < T > &LList < T >::operator = ( const LList < T > &source )
{
    Empty ();
    for ( int i = 0; i < source.Size (); i++ )
    {
        PutDataAtEnd ( source.GetData ( i ) );
    }

    return *this;
}


template < class T > void LList < T >::PutData ( const T & newdata )
{
    PutDataAtEnd ( newdata );
}


template < class T > void LList < T >::PutDataAtEnd ( const T & newdata )
{
    LListItem < T > *li = new LListItem < T > ();
    li->m_data = newdata;
    li->m_next = NULL;
    ++m_numItems;

    if ( m_last == NULL )
    {
        li->m_previous = NULL;
        m_first = li;
        m_last = li;

        m_previous = li;
        m_previousIndex = 0;
    }
    else
    {
        m_last->m_next = li;
        li->m_previous = m_last;
        m_last = li;
    }
}


template < class T > void LList < T >::PutDataAtStart ( const T & newdata )
{
    LListItem < T > *li = new LListItem < T > ();
    li->m_data = newdata;
    li->m_previous = NULL;
    ++m_numItems;

    if ( m_last == NULL )
    {
        li->m_next = NULL;
        m_first = li;
        m_last = li;

        m_previous = li;
        m_previousIndex = 0;
    }
    else
    {
        m_first->m_previous = li;
        li->m_next = m_first;
        m_first = li;

        m_previousIndex++;
    }
}


template < class T >
    void LList < T >::PutDataAtIndex ( const T & newdata, int index )
{
    if ( index == 0 )
    {
        PutDataAtStart ( newdata );
    }
    else if ( index == m_numItems )
    {
        PutDataAtEnd ( newdata );
    }
    else
    {
        LListItem < T > *current = m_first;

        for ( int i = 0; i < index - 1; ++i )
        {
            if ( !current )
                return;
            current = current->m_next;
        }

        if ( !current )
            return;

        LListItem < T > *li = new LListItem < T > ();
        li->m_data = newdata;
        li->m_previous = current;
        li->m_next = current->m_next;
        if ( current->m_next )
            current->m_next->m_previous = li;
        current->m_next = li;
        ++m_numItems;

        m_previousIndex = 0;
        m_previous = m_first;
    }
}


template < class T > int LList < T >::Size () const
{
    return m_numItems;
}


template < class T > T LList < T >::GetData ( int index ) const
{
    LListItem < T > const *item = GetItem ( index );

    if ( item )
    {
        return item->m_data;
    }

    return ( T ) 0;
}


template < class T > T * LList < T >::GetPointer ( int index ) const
{
    LListItem < T > *item = GetItem ( index );
    if ( item )
    {
        return &item->m_data;
    }

    return NULL;
}


template < class T > LListItem < T > *LList < T >::GetItem ( int index ) const
{
    if ( !ValidIndex ( index ) )
        return NULL;


    //
    // Choose a place for which to start walking the list

    // Best place to start is either; m_first, m_previous or m_last
    //
    // m_first                m_previous                                   m_last
    //     |----------:-----------|---------------------:--------------------|
    //            mid-point 1                      mid-point 2
    //     
    // If index is less than mid-point 1, then m_first is nearest.
    // If index is greater than mid-point 2, then m_last is nearest.
    // Otherwise m_previous is nearest.
    // The two if statements below test for these conditions.

    if ( index <= ( m_previousIndex >> 1 ) )
    {
        m_previous = m_first;
        m_previousIndex = 0;
    }
    else if ( ( index - m_previousIndex ) > ( m_numItems - index ) )
    {
        m_previous = m_last;
        m_previousIndex = m_numItems - 1;
    }

    if ( !m_previous )
    {
        m_previous = m_first;
        m_previousIndex = 0;
    }

    while ( index > m_previousIndex )
    {
        m_previous = m_previous->m_next;
        m_previousIndex++;
    }
    while ( index < m_previousIndex )
    {
        m_previous = m_previous->m_previous;
        m_previousIndex--;
    }


    return m_previous;
}


template < class T > T LList < T >::operator []( int index )
{
    return GetData ( index );
}


template < class T > bool LList < T >::ValidIndex ( int index ) const
{
    return ( index >= 0 && index < m_numItems );
}


template < class T > void LList < T >::Empty ()
{

    LListItem < T > *current = m_first;
    while ( current )
    {
        LListItem < T > *m_next = current->m_next;
        delete current;

        current = m_next;
    }

    m_first = NULL;
    m_last = NULL;
    m_numItems = 0;
    m_previous = NULL;
    m_previousIndex = -1;
}

template < class T > void LList < T >::RemoveData ( int index )
{
    LListItem < T > *current = GetItem ( index );

    if ( current == NULL )
        return;

    if ( current->m_previous == NULL )
        m_first = current->m_next;
    else
        current->m_previous->m_next = current->m_next;

    if ( current->m_next == NULL )
        m_last = current->m_previous;
    else
        current->m_next->m_previous = current->m_previous;

    if ( index == m_previousIndex )
    {
        if ( m_numItems == 1 )
        {
            m_previousIndex = -1;
            m_previous = NULL;
        }
        else if ( index > 0 )
        {
            m_previousIndex--;
            m_previous = current->m_previous;
        }
        else
        {
            m_previous = current->m_next;
        }
    }
    else if ( index < m_previousIndex )
    {
        m_previousIndex--;
    }

    delete current;

    --m_numItems;
}


template < class T > void LList < T >::RemoveDataAtEnd ()
{
    RemoveData ( m_numItems - 1 );
}


template < class T > int LList < T >::FindData ( const T & data )
{
    int const size = Size ();

    for ( int i = 0; i < size; ++i )
    {
        if ( GetData ( i ) == data )
        {
            return i;
        }
    }

    return -1;
}

#endif
