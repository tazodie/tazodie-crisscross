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


#ifndef __included_dstack_cpp
#define __included_dstack_cpp

#include "dstack.h"

using namespace CrissCross::Data;

template < class dataType >
DStack<dataType>::DStack ( size_t N )
{
    m_stepSize = 32;
    m_top = m_bottom = NULL;
    m_size = m_origSize = 0;
}

template < class dataType >
DStack<dataType>::~DStack ()
{
    delete [] m_bottom;
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
    return ( m_top - m_bottom );
}

template < class dataType >
dataType DStack<dataType>::pop ()
{
    if ( !m_top ) return (dataType)0;
    m_top--;
    return *m_top;
}

template < class dataType >
void DStack<dataType>::empty ()
{
    delete [] m_bottom;
    m_top = m_bottom = NULL;
    m_size = m_origSize = 0;
}

#endif
