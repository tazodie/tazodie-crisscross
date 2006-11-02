/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006 IO.IN Research
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

#include "universal_include.h"
#include "compare.h"

namespace CrissCross
{
    namespace Data
    {
        namespace Comparison
        {
            int Compare ( CHAR _first, CHAR _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }

#if defined ( ENABLE_UNICODE )
            int Compare ( WCHAR _first, WCHAR _second )
            {
                if ( _first < _second )
                    return -1;
                else if ( _first > _second )
                    return 1;
                else
                    return 0;
            }
#endif

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

            int Compare ( CHAR *_first, CHAR *_second )
            {
                return strcmp ( _first, _second );
            }

#if defined ( ENABLE_UNICODE )
            int Compare ( WCHAR *_first, WCHAR *_second )
            {
                return wcscmp ( _first, _second );
            }
#endif

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
