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
            inline LListItem < T > *getItem ( int index ) const;

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
            inline void insert ( const T & _newdata );

            //! Adds data at the end of the list.
            /*!
                \param _newdata The data to add to the list.
             */
            void insert_back ( const T & _newdata );

            //! Adds data at the start of the list.
            /*!
                \param _newdata The data to add to the list.
             */
            void insert_front ( const T & _newdata );

            //! Adds data at the specified index.
            /*!
                \param _newdata The data to add to the list.
                \param _index The index where the node should be added.
             */
            void insert_at ( const T & _newdata, int _index );

            //! Gets the data at the specified index.
            /*!
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the data to fetch.
                \return The data contained in the node at the index.
             */
            inline T getData ( int _index ) const;

            //! Gets the address of where the data at the specified index is stored.
            /*!
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the node to find.
                \return The pointer to where the data record is stored.
             */
            inline T *getPointer ( int _index ) const;

            //! Removes the node at the given index.
            /*!
                This does not delete the data at the node, just the node itself.
                WARNING: Slow unless you're sequentially iterating through.
                \param _index The index of the node to delete.
             */
            void remove ( int _index );

            //! Removes the node at the end of the list.
            /*!
                This does not delete the data at the node, just the node itself.
                WARNING: Slow unless you're sequentially iterating through.
             */
            inline void removeDataAtEnd ();

            //! Finds a node's index by searching for the given data.
            /*!
                \param _data The data to find.
                \return -1 if not found, otherwise returns the index.
             */
            int findData ( const T & _data );

            //! Indicates the size of the linked list.
            /*!
                \return The size of the linked list.
             */
            inline int size () const;

            //! Determines whether a given index is within the bounds of the list.
            /*!
                \param _index The index to validate.
                \return True if the index is valid, false otherwise.
             */
            inline bool validIndex ( int _index ) const;

            //! Deletes all nodes in the list, but does not free memory allocated by data.
            void empty();

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
#include <crisscross/llist.cpp>

#endif
