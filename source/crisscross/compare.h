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
        namespace Comparison
        {
            //! Function for byte comparisons.
            int Compare ( char _first, char _second );

            //! Function for short integer comparisons.
            int Compare ( short _first, short _second );

            //! Function for integer comparisons.
            int Compare ( int _first, int _second );

            //! Function for long integer comparisons.
            int Compare ( long _first, long _second );

            //! Function for C-style string comparisons.
            int Compare ( char *_first, char *_second );

            //! Function for std::string comparisons.
            int Compare ( std::string _first, std::string _second );
        }
    }
}
