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

#ifndef __included_sortclass_h
#define __included_sortclass_h

#include <crisscross/core_compare.h>

namespace CrissCross
{
    namespace Data
    {
        //! Sorting abstract class.
        template <class T>
        class SortClass
        {
        public:
            //! The constructor.
            SortClass();

            //! The destructor.
            virtual ~SortClass();

            //! The abstract sort function.
            /*!
                Does nothing, and cannot be called (abstract).
                \param _array The array to sort.
                \param _size The size of the array to sort.
             */
            virtual int Sort ( T *_array, int _size ) = 0;

            //! The swap function.
            /*!
                Will swap two items in an array.
                \param _array The array to swap items in.
                \param _first The first item to swap.
                \param _second The second item to swap.
             */
            virtual void Swap ( T *_array, int _first, int _second );
        };

        //! A HeapSort implementation for sorting arrays.
        template <class T>
        class HeapSort : public SortClass<T>
        {
        public:
            //! The constructor.
            HeapSort();

            //! Sorts an array using the HeapSort method.
            /*!
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0, for the time being.
             */
            int Sort ( T *_array, int _size );
        };
    }
}

#include <crisscross/sortclass.cpp>

#endif
