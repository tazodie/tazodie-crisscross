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

#ifndef __included_cc_quicksort_h
#define __included_cc_quicksort_h

#include <crisscross/deprecate.h>
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
            void InternalSort ( T *_array, size_t _beginning, size_t _end )
	        {
	            if ( _end > _beginning + 1 )
	            {
	                const T &piv = _array[_beginning];
	                size_t l = _beginning + 1, r = _end;
	                while ( l < r )
	                {
	                    if ( Compare ( _array[l], piv ) <= 0 )
	                        l++;
	                    else
	                        Swap ( _array, l, --r );
	                }
	                Swap ( _array, --l, _beginning );
	                InternalSort ( _array, _beginning, l );
	                InternalSort ( _array, r, _end );
	            }
	        };

        public:

            //! Sorts an array using the QuickSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            _CC_DEPRECATE_SLOW("SEVERE") int Sort ( T *_array, size_t _size )
	        {
	            InternalSort ( _array, 0, _size );
	            return 0;
	        };
        };
    }
}

#endif
