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

#ifndef __included_cc_dstack_h
#   error "This file shouldn't be compiled directly."
#endif

#include <crisscross/dstack.h>

using namespace CrissCross::Data;

template < class dataType >
DStack<dataType>::DStack ( size_t N )
{
	if ( N < 32 || (int)N == -1 )
		m_stepSize = 32;
	else
		m_stepSize = N;
    m_top = m_bottom = NULL;
    m_size = m_origSize = 0;
}

template < class dataType >
DStack<dataType>::~DStack ()
{
    delete [] m_bottom;
	m_top = m_bottom = NULL;
}

template < class dataType >
void DStack<dataType>::grow ()
{
    dataType *newstack_ = new dataType[m_size + m_stepSize];
    if ( m_bottom )
        memcpy ( newstack_, m_bottom, sizeof ( dataType ) * m_size );
    delete [] m_bottom;
    m_bottom = newstack_;
    m_top = m_bottom + m_size;
    m_size += m_stepSize;
}

template < class dataType >
void DStack<dataType>::push ( dataType val )
{
    if ( count() == m_size )    // the stack is full. need more space!
    {
        grow();
    }
    *m_top = val;
    m_top++;
}

template < class dataType >
size_t DStack<dataType>::count () const
{
    return (m_top - m_bottom);
}

template < class dataType >
dataType DStack<dataType>::pop ()
{
    if ( !m_top ) return (dataType)0;
    m_top--;
    return *m_top;
}

template < class dataType >
const dataType &DStack<dataType>::peek ()
{
    if ( !m_top ) return (dataType)0;
    return *(m_top - 1);
}

template < class dataType >
void DStack<dataType>::empty ()
{
    delete [] m_bottom;
    m_top = m_bottom = NULL;
    m_size = m_origSize = 0;
}
