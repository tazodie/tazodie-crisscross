/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
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
    
#ifndef __included_sortclass_h
#define __included_sortclass_h

namespace CrissCross
{
    namespace Data
    {
        //! Comparison abstract class.
        /*!
            Used to compare two items in the sorting algorithm classes.
         */
        class Comparison
        {
        public:
            Comparison(){};
            virtual ~Comparison(){};
            virtual int Compare ( int _first, int _second ) {
                return -2;
            };
            virtual int Compare ( char *_first, char *_second ) {
                return -2;
            };
        };

        //! String comparison class.
        /*!
            \sa Comparison
         */
        class StringCompare : public Comparison
        {
        public:
            int Compare ( char *_first, char *_second );
        };

        //! Integer comparison class.
        /*!
            \sa Comparison
         */
        class IntegerCompare : public Comparison
        {
        public:
            int Compare ( int _first, int _second );
        };

        //! Sorting abstract class.
        template <class T>
        class SortClass
        {
        public:
            SortClass();
            virtual ~SortClass();
            virtual int Sort ( T *_array, int _size, Comparison *_compare ) { return 0; };
            virtual void Swap ( T *_array, int _first, int _second );
        };

        //! HeapSort class.
        template <class T>
        class HeapSort : public SortClass<T>
        {
        public:
            HeapSort();
            int Sort ( T *_array, int _size, Comparison *_compare );
        };
    }
}

#include "sortclass.cpp"

#endif
