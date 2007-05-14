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

#ifndef __included_quicksort_h
#define __included_quicksort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A QuickSort implementation for sorting arrays.
        template <class T>
        class QuickSort : public Sorter<T>
        {
        private:
            void InternalSort ( T *_array, size_t _beginning, size_t _end );

        public:
            //! The constructor.
            QuickSort();

            //! Sorts an array using the QuickSort method.
            /*!
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0, for the time being.
             */
            int Sort ( T *_array, size_t _size );
        };
    }
}

#include <crisscross/quicksort.cpp>

#endif
