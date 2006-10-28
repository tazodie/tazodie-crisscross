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

namespace CrissCross
{
    namespace Data
    {
        //! @cond
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
        //! @endcond


        //! A doubly-linked list implementation.
        template < class T > class LList
        {
        protected:
            //! The first node.
            LListItem < T > *m_first;

            //! The last node.
            LListItem < T > *m_last;

            //! The last accessed node.
            /*!
                Speeds up searches and sequential access.
             */
            mutable LListItem < T > *m_previous;    // Used to get quick access
            
            //! The last accessed index.
            /*!
                Speeds up searches and sequential access.
             */
            mutable int m_previousIndex;    // for sequential reads (common)

            //! The number of nodes in the list.
            int m_numItems;

        protected:
            inline LListItem < T > *GetItem ( int index ) const;

        public:

            //! The default constructor.
            LList ();

            //! The copy constructor.
            LList ( const LList < T > & );

            //! The destructor.
            ~LList ();

            //! The implicit copy operator.
            LList & operator = ( const LList < T > & );

            //! Adds data at the end of the list.
            /*!
                \param _newdata The data to add to the list.
             */
            inline void PutData ( const T & _newdata );

            //! Adds data at the end of the list.
            /*!
                \param _newdata The data to add to the list.
             */
            void PutDataAtEnd ( const T & _newdata );

            //! Adds data at the start of the list.
            /*!
                \param _newdata The data to add to the list.
             */
            void PutDataAtStart ( const T & _newdata );

            //! Adds data at the specified index.
            /*!
                \param _newdata The data to add to the list.
                \param _index The index where the node should be added.
             */
            void PutDataAtIndex ( const T & _newdata, int _index );

            //! Gets the data at the specified index.
            /*!
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the data to fetch.
                \return The data contained in the node at the index.
             */
            inline T GetData ( int _index ) const;

            //! Gets the address of where the data at the specified index is stored.
            /*!
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the node to find.
                \return The pointer to where the data record is stored.
             */
            inline T *GetPointer ( int _index ) const;

            //! Removes the node at the given index.
            /*!
                This does not delete the data at the node, just the node itself.
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the node to delete.
             */
            void RemoveData ( int _index );

            //! Removes the node at the end of the list.
            /*!
                This does not delete the data at the node, just the node itself.
                WARNING: Slow unless you're sequentially iterating through.
             */
            inline void RemoveDataAtEnd ();

            //! Finds a node's index by searching for the given data.
            /*!
                \param _data The data to find.
                \return -1 if not found, otherwise returns the index.
             */
            int FindData ( const T & _data );

            //! Indicates the size of the linked list.
            /*!
                \return The size of the linked list.
             */
            inline int Size () const;

            //! Determines whether a given index is within the bounds of the list.
            /*!
                \param _index The index to validate.
                \return True if the index is valid, false otherwise.
             */
            inline bool ValidIndex ( int _index ) const;

            //! Deletes all nodes in the list, but does not free memory allocated by data.
            void Empty();

            //! Gets the data at the specified index.
            /*!
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the data to fetch.
                \return The data contained in the node at the index.
             */
            inline T operator [] ( int _index );
        };
    }
}
#    include "llist.cpp"

#endif
