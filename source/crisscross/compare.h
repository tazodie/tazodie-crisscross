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
