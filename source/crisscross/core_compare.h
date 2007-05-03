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
			\param _first The item to compare to _second.
			\param _second The item to compare to _first.
			\return 0 if the items are equal, -1 if _first is less than _second, and 1 if _first is greater than _second.
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
		}
    }
}
