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

#ifndef __included_darray_h
#define __included_darray_h

#include <crisscross/core_deprecate.h>
#include <crisscross/datastructures/darray.h>
#include <crisscross/datastructures/dstack.h>

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
            DStack<unsigned int>    *m_emptyNodes;

        protected:
            //! The size by which to increase the size of the array when there are no more empty nodes.
            /*!
                If set to -1, it will double the size of the array each time the array grows.
             */
            int            m_stepSize;

            //! The current size of the array.
            int            m_arraySize;

            //! The number of used items in the array.
            int            m_numUsed;

            //! The actual array which stores our data.
            T              *m_array;

            //! An array to indicate which nodes in m_array are in use.
            char           *m_shadow;

            //! Increases the size of the array.
            void Grow ();

            //! Rebuilds the empty node stack.
            void RebuildStack   ();

            //! Recounts the number of used nodes.
            void Recount        ();

            //! Gets the next empty node.
            /*!
                Typically can just pop an item off the empty_nodes stack. If
                there are no other empty nodes remaining, then it will
                automatically Grow() the array.
                \return An index in m_array.
             */
            int GetNextFree     ();

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
            void SetSize ( int _newsize );

            //! Sets the step size used in Grow().
            /*!
                 \param _newstepsize The new step size to use.
             */
            void SetStepSize ( int _newstepsize );

            //! Sets the step size to double the array size when a Grow() is necessitated.
            /*!
                \sa m_stepSize
             */
            void SetStepDouble ();

            //! Gets the data at the given index.
            /*!
                \param _index The index of the node to get data from.
                \return The data stored at the index.
             */
            T GetData ( int _index );

            //! Removes the data at the given index.
            /*!
                \param _index The index of the node to clear.
             */
            void RemoveData ( int _index );

            //! Finds the data in the array.
            /*!
                A return value of -1 means the data couldn't be found.
                \param _data The data to find.
                \return The index where the given data is located.
             */
            int FindData ( const T & _data );

            //! Inserts data into the array at the first available index.
            /*!
                \param _newdata The data to put into the array.
                \return The index of the node where the data was stored.
             */
            int PutData ( const T & _newdata );

            //! Inserts data into the array at the given index.
            /*!
                \param _newdata The data to put into the array.
                \param _index The index in the array where the data should
                    be put, regardless of existing contents.
             */
            void PutData ( const T & _newdata, int _index );

            //! Indicates the number of used nodes.
            /*!
                \return The number of used nodes.
             */
            int NumUsed ();

            //! Indicates the total size of the array.
            /*!
                \return The size of the array.
             */
            inline int Size ();

            //! Indicates whether a given index is valid.
            /*!
                Tests whether the index is within the bounds of the array and
                is an empty node.
                \param _index The index to test.
                \return Boolean value. True if valid, false if not.
             */
            bool ValidIndex ( int _index );

            //! Empties the array but does NOT free any pointers stored in the array.
            /*!
                The array must be iterated through and any pointers must be freed manually before calling this.
             */
            void Empty ();            // Resets the array to empty    

            //! Gets the data at the given index.
            /*!
                \param _index The index of the node to get data from.
                \return The data stored at the index.
             */
            T & operator []( int _index );

        };
    }
}

#    include "darray.cpp"

#endif