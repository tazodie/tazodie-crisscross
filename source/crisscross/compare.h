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

namespace CrissCross
{
    namespace Data
    {
		//! Function for generic data comparison.
		/*!
			Warning: This doesn't work for pointers. For character arrays,
			wrap them in a CrissCross::Data::DataBuffer class first.
		 */
		template < class T >
		int Compare ( const T &_first, const T &_second )
		{
			if ( _first < _second )
				return -1;
			else if ( _first > _second )
				return 1;
			else
				return 0;
		};
    }
}
