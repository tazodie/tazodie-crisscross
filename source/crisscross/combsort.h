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

#ifndef __included_cc_combsort_h
#define __included_cc_combsort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A CombSort implementation for sorting arrays.
        template <class T>
        class CombSort : public Sorter<T>
        {
        private:
            size_t NewGap ( size_t gap )
	        {
	            gap = (gap * 10) / 13;
	            if (gap == 9 || gap == 10)
	                gap = 11;
	            if (gap < 1)
	                gap = 1;
	            return gap;
	        };

        public:
            //! Sorts an array using the CombSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            cc_uint64_t Sort ( T *_array, size_t _size )
	        {
				cc_uint64_t ret = 0;
	            size_t gap = _size;
	            for (;;) {
	                gap = NewGap(gap);
	                bool swapped = false;
	                for (size_t i = 0; i < _size - gap; i++) {
	                    size_t j = i + gap;
						ret++;
	                    if ( Compare ( _array[i], _array[j] ) > 0 ) {
							ret++;
	                        Swap ( _array, i, j );
	                        swapped = true;
	                    }
	                }
	                if (gap == 1 && !swapped)
	                break;
	            }
	            return ret;
	        };
        };
    }
}

#endif
