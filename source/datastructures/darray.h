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

#ifndef __included_darray_h
#define __included_darray_h

#include "core_deprecate.h"
#include "darray.h"
#include "dstack.h"

namespace CrissCross
{
    namespace Data
    {
        template < class T > class DArray
        {

          private:
            DStack<unsigned int>    *empty_nodes;

          protected:

            int            m_stepSize;
            int            m_arraySize;
            int            m_numUsed;

            T              *m_array;
            char           *m_shadow;

            void Grow ();
            void RebuildStack   ();
            void Recount        ();
            int GetNextFree     ();

          public:

            DArray ();                // using the default constructor defeats the 
                                      // purpose of the stack. use the other one
                                      // any time possible.
            DArray ( int _newStepSize );
            ~DArray ();

            void SetSize ( int newsize );
            void SetStepSize ( int newstepsize );
            void SetStepDouble ();

            inline T GetData ( int index );

            void RemoveData ( int index );
            int FindData ( const T & data );    // -1 means 'not found'

            int PutData ( const T & newdata );    // Returns index used
            void PutData ( const T & newdata, int index );

            int NumUsed ();            // Returns the number of used entries
            inline int Size ();    // Returns the total size of the array

            bool ValidIndex ( int index );    // Returns true if the index contains used data

            void Empty ();            // Resets the array to empty    

            T & operator []( int index );

        };
    }
}

#    include "darray.cpp"

#endif
