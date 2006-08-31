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

#ifndef __included_llist_h
#define __included_llist_h

template < class T > class LListItem
{
  protected:
  public:
    T m_data;
    LListItem *m_next;
    LListItem *m_previous;

    LListItem ();
    ~LListItem ();
};


template < class T > class LList
{
  protected:
    LListItem < T > *m_first;    // Pointer to first node
    LListItem < T > *m_last;    // Pointer to last node

    mutable LListItem < T > *m_previous;    // Used to get quick access
    mutable int m_previousIndex;    // for sequential reads (common)

    int m_numItems;

  protected:
    inline LListItem < T > *GetItem ( int index ) const;

  public:
    LList ();
    LList ( const LList < T > & );

    ~LList ();

    LList & operator = ( const LList < T > & );

    inline void PutData ( const T & newdata );    // Adds in data at the end  
    void PutDataAtEnd ( const T & newdata );
    void PutDataAtStart ( const T & newdata );
    void PutDataAtIndex ( const T & newdata, int index );

    inline T GetData ( int index ) const;    // slow unless sequential
    inline T *GetPointer ( int index ) const;    // slow unless sequential
    void RemoveData ( int index );    // slow unless sequential
    inline void RemoveDataAtEnd ();
    int FindData ( const T & data );    // -1 means 'not found'

    inline int Size () const;    // Returns the total size of the array
    inline bool ValidIndex ( int index ) const;

    void Empty ();            // Resets the array to empty    
    void EmptyAndDelete ();    // As above, deletes all data as well

    inline T operator [] ( int index );
};

#    include "llist.cpp"

#endif
