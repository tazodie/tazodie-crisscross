/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_insertionsort_h
#define __included_cc_insertionsort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A InsertionSort implementation for sorting arrays.
        template <class T>
        class InsertionSort : public Sorter<T>
        {
        public:
            //! Sorts an array using the InsertionSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            int Sort ( T *_array, size_t _size )
			{
				for ( int i = 1; i < _size; i++ )
				{
					int j = i;
					T b = _array[i];
					while ( ( j > 0 ) && ( a[j-1] > b ) )
					{
						a[j] = a[j-1];
						j--;
					}
					a[j] = b;
				}
	            return 0;
			};
        };
    }
}

#endif
