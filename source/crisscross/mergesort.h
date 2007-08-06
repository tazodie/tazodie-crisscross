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

#ifndef __included_cc_mergesort_h
#define __included_cc_mergesort_h

#include <crisscross/sort.h>

namespace CrissCross
{
    namespace Data
    {
        //! A MergeSort implementation for sorting arrays.
        template <class T>
        class MergeSort : public Sorter<T>
        {
        private:
			void InternalSort ( T *a, size_t lo, size_t hi, T *&scratch )
			{
				if ( lo >= hi ) {
					return;                 /* a[lo] is sorted already   */
				}

				size_t mid = ( lo + hi ) / 2;
				InternalSort ( a, lo, mid, scratch );      /* Sort sublist a[lo..mid]   */
				InternalSort ( a, mid + 1, hi, scratch );    /* Sort sublist a[mid+1..hi] */

				size_t k, t_lo = lo, t_hi = mid + 1;  
				for ( k = lo; k <= hi; k++ )            /* Merge sorted sublists    */
					if ( ( t_lo <= mid ) && ( ( t_hi > hi ) ||
					     ( Compare ( a[t_lo], a[t_hi] ) < 0 ) ) )
					{
						scratch[k] = a[t_lo++];
					} else {
						scratch[k] = a[t_hi++];
					}

				for ( k = lo; k <= hi; k++ ) {
					a[k] = scratch[k]; /* Copy back to a   */
				}
			};
		
        public:
            //! Sorts an array using the MergeSort method.
            /*!
				\param _array The array to sort.
				\param _size The size of the array to sort.
				\return Always 0, for the time being.
			 */
            int Sort ( T *_array, size_t _size )
	        {
				T *scratch = new T[_size];
				InternalSort ( _array, 0, _size - 1, scratch);
				delete [] scratch;
				scratch = NULL;
	            return 0;
	        };
        };
    }
}

#endif
