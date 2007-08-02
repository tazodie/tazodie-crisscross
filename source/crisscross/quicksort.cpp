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

#ifndef __included_cc_quicksort_h
#   error "This file shouldn't be compiled directly."
#endif

namespace CrissCross
{
    namespace Data
    {
        template <class T>
        int QuickSort<T>::Sort ( T *_array, size_t _size )
        {
            InternalSort ( _array, 0, _size );
            return 0;
        }

        template <class T>
        void QuickSort<T>::InternalSort ( T *_array, size_t _beginning, size_t _end )
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
        }
    }
}
