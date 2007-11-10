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

#ifndef __included_cc_bubblesort_h
#define __included_cc_bubblesort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A BubbleSort implementation for sorting arrays.
        template <class T>
        class BubbleSort : public Sorter<T>
        {

        public:
            //! Sorts an array using the BubbleSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            _CC_DEPRECATE_SLOW("EXTREME") cc_uint64_t Sort ( T *_array, size_t _size )
	        {
				cc_uint64_t ret = 0;
				for ( size_t i = _size - 1; i >= 0; i-- ) {
					bool flipped = false;
					for ( size_t j = 0; j < i; j++ ) {
						ret++;
						if ( Compare ( _array[j], _array[j+1] ) > 0 ) {
							ret++;
							Swap ( _array, j, j + 1 );
							flipped = true;
						}
					}
					if ( !flipped || i == 0 ) {
						break;
					}
				}
	            return ret;
	        };
        };
    }
}

#endif
