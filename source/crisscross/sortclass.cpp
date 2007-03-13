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

#include <crisscross/sortclass.h>

namespace CrissCross
{
    namespace Data
    {

        template <class T>
        void SortClass<T>::Swap ( T *a, int _first, int _second )
        {
            T old = a[_first];
            a[_first] = a[_second];
            a[_second] = old;
        }

        template <class T>
        SortClass<T>::SortClass()
        {}

        template <class T>
        SortClass<T>::~SortClass()
        {}

        template <class T>
        HeapSort<T>::HeapSort()
        {}

        template <class T>
        int HeapSort<T>::Sort ( T *_array, int _size )
        {
            // Phase 1: make a heap by sifting down all non-leaf 
            // elements, one after another, starting with the last
            // non-leaf element and going backwards.
            for ( int i = (_size / 2) - 1; i >= 0; i-- ) {

                for ( int j = i; j * 2 + 1 < _size; ) {
                    int k = j * 2 + 1;

                    if ( k + 1 < _size && Comparison::Compare ( _array[k], _array[k + 1] ) < 0 )
                        k++;

                    if ( Comparison::Compare ( _array[j], _array[k] ) < 0 )
                        Swap ( _array, j, k );
                    else
                        break;
                    j = k;
                }

            }

            // Phase 2: Successively place the biggest, then next biggest
            // items at the end of the array. each time reconstructing the
            // heap in the slots of the array not yet sorted.
            for ( int i = _size - 1; i > 0; i-- ) {
                Swap ( _array, 0, i );
                for ( int j = 0; j *2 + 1 < i; ) {
                    int k = (j * 2) + 1;
                    if ( k + 1 < i && Comparison::Compare ( _array[k], _array[k + 1] ) < 0 )
                        k++;
                    if ( Comparison::Compare ( _array[j], _array[k] ) < 0 )
                        Swap ( _array, j, k );
                    else
                        break;
                    j = k;
                }
            }
            return 0;
        }
    }
}
