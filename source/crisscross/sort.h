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

#ifndef __included_cc_sort_h
#define __included_cc_sort_h

#include <crisscross/compare.h>

namespace CrissCross
{
    namespace Data
    {
        //! Sorting abstract class.
        template <class T>
        class Sorter
        {
        public:
            //! The constructor.
            Sorter();

            //! The destructor.
            virtual ~Sorter();

            //! The abstract sort function.
            /*!
                Does nothing, and cannot be called (abstract).
                \param _array The array to sort.
                \param _size The size of the array to sort.
             */
            virtual int Sort ( T *_array, size_t _size ) = 0;

            //! The swap function.
            /*!
                Will swap two items in an array.
                \param _array The array to swap items in.
                \param _first The first item to swap.
                \param _second The second item to swap.
             */
            virtual void Swap ( T *_array, size_t _first, size_t _second );
        };
    }
}

#include <crisscross/sort.cpp>

#include <crisscross/quicksort.h>
#include <crisscross/heapsort.h>
#include <crisscross/combsort.h>

#define FastestSort				HeapSort
#define MemoryEfficientSort		HeapSort

#endif
