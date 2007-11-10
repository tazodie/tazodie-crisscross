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

#ifndef __included_cc_heapsort_h
#define __included_cc_heapsort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A HeapSort implementation for sorting arrays.
        template <class T>
        class HeapSort : public Sorter<T>
        {
        public:

            //! Sorts an array using the HeapSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            cc_uint64_t Sort ( T *_array, size_t _size )
	        {
				cc_uint64_t ret = 0;
	            // Phase 1: make a heap by sifting down all non-leaf 
	            // elements, one after another, starting with the last
	            // non-leaf element and going backwards.
	            for ( size_t i = (_size / 2) - 1; (int)i >= 0; i-- ) {

	                for ( size_t j = i; j * 2 + 1 < _size; ) {
	                    size_t k = j * 2 + 1;
						ret += 2;
	                    if ( k + 1 < _size && Compare ( _array[k], _array[k + 1] ) < 0 )
	                        k++;
	                    if ( Compare ( _array[j], _array[k] ) < 0 )
						{
	                        Swap ( _array, j, k );
							ret++;
						}
	                    else
	                        break;
	                    j = k;
	                }

	            }

	            // Phase 2: Successively place the biggest, then next biggest
	            // items at the end of the array. each time reconstructing the
	            // heap in the slots of the array not yet sorted.
	            for ( size_t i = _size - 1; (int)i > 0; i-- ) {
					ret++;
	                Swap ( _array, 0, i );
	                for ( size_t j = 0; j *2 + 1 < i; ) {
	                    size_t k = (j * 2) + 1;
						ret += 2;
	                    if ( k + 1 < i && Compare ( _array[k], _array[k + 1] ) < 0 )
	                        k++;
	                    if ( Compare ( _array[j], _array[k] ) < 0 )
						{
	                        Swap ( _array, j, k );
							ret++;
						}
	                    else
	                        break;
	                    j = k;
	                }
	            }
	            return ret;
	        };
        };
    }
}

#endif
