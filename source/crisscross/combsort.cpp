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
#   error "This file shouldn't be compiled directly."
#endif

namespace CrissCross
{
    namespace Data
    {
        template <class T>
        int CombSort<T>::Sort ( T *_array, size_t _size )
        {
            size_t gap = _size;
            for (;;) {
                gap = NewGap(gap);
                bool swapped = false;
                for (size_t i = 0; i < _size - gap; i++) {
                    size_t j = i + gap;
                    if ( Compare ( _array[i], _array[j] ) > 0 ) {
                        Swap ( _array, i, j );
                        swapped = true;
                    }
                }
                if (gap == 1 && !swapped)
                break;
            }
            return 0;
        }

        template <class T>
        size_t CombSort<T>::NewGap ( size_t gap )
        {
            gap = (gap * 10) / 13;
            if (gap == 9 || gap == 10)
                gap = 11;
            if (gap < 1)
                gap = 1;
            return gap;
        }
    }
}
