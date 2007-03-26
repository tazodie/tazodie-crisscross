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

#include <crisscross/universal_include.h>
#include <crisscross/compare.h>

namespace CrissCross
{
    namespace Data
    {
        namespace Comparison
        {
            int Compare ( char _first, char _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }

            int Compare ( short _first, short _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }

            int Compare ( int _first, int _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }

            int Compare ( long _first, long _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }

            int Compare ( char *_first, char *_second )
            {
                return strcmp ( _first, _second );
            }

            int Compare ( std::string _first, std::string _second )
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
}
