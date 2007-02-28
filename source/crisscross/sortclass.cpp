/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of the I.O. Independent Network nor the names of its contributors
 *       may be used to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
