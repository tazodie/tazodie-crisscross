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

#ifndef __included_cc_sort_h
#   error "This file shouldn't be compiled directly."
#endif

namespace CrissCross
{
    namespace Data
    {

        template <class T>
        void Sorter<T>::Swap ( T *a, size_t _first, size_t _second )
        {
            T old = a[_first];
            a[_first] = a[_second];
            a[_second] = old;
        }

        template <class T>
        Sorter<T>::Sorter()
        {}

        template <class T>
        Sorter<T>::~Sorter()
        {}
    }
}
