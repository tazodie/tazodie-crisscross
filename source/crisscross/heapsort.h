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

#ifndef __included_cc_heapsort_h
#define __included_cc_heapsort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A HeapSort implementation for sorting arrays.
        template <class T>
        class HeapSort : public Sorter<T>
        {
        public:

            //! Sorts an array using the HeapSort method.
            /*!
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0, for the time being.
             */
            int Sort ( T *_array, size_t _size );
        };
    }
}

#include <crisscross/heapsort.cpp>

#endif
