/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#ifndef __included_sortclass_h
#define __included_sortclass_h

#include <crisscross/compare.h>

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
                Does nothing except return 0.
                \param _array The array to sort.
                \param _size The size of the array to sort.
                \return Always 0. Abstract class.
             */
            virtual int Sort ( T *_array, int _size ) { return 0; };

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

            //! Sorts the array using the HeapSort method.
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
