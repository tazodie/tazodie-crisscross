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

#ifndef __included_cc_internal_mem_h
#define __included_cc_internal_mem_h

namespace CrissCross
{
    namespace Data
    {
        //! @cond

        // These functions are designed for internal use.
        // You generally shouldn't use them unless you know what you're doing.

        template < class T >
        __inline T Duplicate ( T const &_data )
        {
            return _data;
        }
        
        template <>
        __inline char *Duplicate ( char * const &_data )
        {
            return strdup ( _data );
        }

        template <>
        __inline const char *Duplicate ( const char * const &_data )
        {
            return strdup ( _data );
        }

        template < class T >
        __inline void Dealloc ( T const &_data )
        {
        }
        
        template <>
        __inline void Dealloc ( char * const &_data )
        {
            if ( _data ) free ( _data );
        }
        
        template <>
        __inline void Dealloc ( const char * const &_data )
        {
            if ( _data ) free ( (char *)_data );
        }

        //! @endcond
	}
}

#endif
