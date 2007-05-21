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

#ifndef __included_cc_darray_h
#define __included_cc_darray_h

#include <crisscross/deprecate.h>
#include <crisscross/darray.h>
#include <crisscross/dstack.h>
#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A dynamic array implementation.
        template < class T > class DArray
        {

        private:
            //! A DStack containing indices of empty nodes in the array.
            /*!
                Vastly speeds up insertions.
             */
            DStack<size_t>    *m_emptyNodes;

        protected:
            //! The size by which to increase the size of the array when there are no more empty nodes.
            /*!
                If set to -1, it will double the size of the array each time the array grows.
                \sa setStepSize
                \sa setStepDouble
             */
            int            m_stepSize;

            //! The current size of the array.
            /*!
                \sa setSize
             */
            int            m_arraySize;

            //! The number of used items in the array.
            int            m_numUsed;

            //! The actual array which stores our data.
            T              *m_array;

            //! An array to indicate which nodes in m_array are in use.
            char           *m_shadow;

            //! Increases the size of the array.
            void grow            ();

            //! Rebuilds the empty node stack.
            void rebuildStack   ();

            //! Recounts the number of used nodes.
            void recount        ();

            //! Gets the next empty node.
            /*!
                Typically can just pop an item off the empty_nodes stack. If
                there are no other empty nodes remaining, then it will
                automatically Grow() the array.
                \return An index in m_array.
             */
            int getNextFree     ();

        public:

            //! The default constructor.
            DArray ();

            //! The secondary constructor.
            /*!
                \param _newStepSize The step size to use in Grow().
             */
            DArray ( int _newStepSize );

            //! The destructor.
            ~DArray ();

            //! Sets the size of the array.
            /*!
                \param _newsize The new array size.
             */
            void setSize ( int _newsize );

            //! Sets the step size used in Grow().
            /*!
                \param _newstepsize The new step size to use.
                \sa m_stepSize
             */
            void setStepSize ( int _newstepsize );

            //! Sets the step size to double the array size when a Grow() is necessitated.
            /*!
                \sa m_stepSize
             */
            void setStepDouble ();

            //! Gets the data at the given index.
            /*!
                \param _index The index of the node to get data from.
                \return The data stored at the index.
             */
            T getData ( int _index ) const;

            //! Removes the data at the given index.
            /*!
                \param _index The index of the node to clear.
             */
            void remove ( int _index );

            //! Finds the data in the array.
            /*!
                A return value of -1 means the data couldn't be found.
                \param _data The data to find.
                \return The index where the given data is located.
             */
            int findData ( const T & _data );

            //! Inserts data into the array at the first available index.
            /*!
                \param _newdata The data to put into the array.
                \return The index of the node where the data was stored.
             */
            int insert ( const T & _newdata );

            //! Inserts data into the array at the given index.
            /*!
                \param _newdata The data to put into the array.
                \param _index The index in the array where the data should
                    be put, regardless of existing contents.
             */
            void insert ( const T & _newdata, int _index );

            //! Indicates the number of used nodes.
            /*!
                \return The number of used nodes.
             */
            int numUsed () const;

            //! Indicates the total size of the array.
            /*!
                \return The size of the array.
             */
            inline int size () const;

            //! Indicates whether a given index is valid.
            /*!
                Tests whether the index is within the bounds of the array and
                is an empty node.
                \param _index The index to test.
                \return Boolean value. True if valid, false if not.
             */
            bool validIndex ( int _index ) const;

            //! Empties the array but does NOT free any pointers stored in the array.
            /*!
                The array must be iterated through and any pointers must be freed manually before calling this.
             */
            void empty ();
            
            //! Sorts the array using the provided method.
            void sort ( CrissCross::Data::Sorter<T> *_sortMethod );

            //! Gets the data at the given index.
            /*!
                \param _index The index of the node to get data from.
                \return The data stored at the index.
             */
            T & operator []( int _index );

            //! Gets the data at the given index.
            /*!
                \param _index The index of the node to get data from.
                \return The data stored at the index.
             */
            const T & operator []( int _index ) const;

        };
    }
}

#include <crisscross/darray.cpp>

#endif
