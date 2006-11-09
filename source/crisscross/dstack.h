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

#ifndef __included_dstack_h
#define __included_dstack_h

namespace CrissCross
{
    namespace Data
    {
        //! A dynamic stack implementation.
        template < class dataType >
        class DStack
        {
        private:
            //! The step size for which to increase the stack size by.
            int          m_stepSize;
            
            //! The actual stack itself.
            dataType        *m_bottom;

            //! The pointer to the current position in the stack.
            dataType        *m_top;

            //! The size of the stack.
            int          m_size;

            //! The original size of the stack (used on an empty() call to reset things to defaults).
            int          m_origSize;

        public:
            //! The constructor.
            /*!
                \param _size The step size to use.
             */
            DStack          ( int _size = 32 );

            //! The destructor.
            ~DStack         ();

            //! Increases the array size by the number in step_
            void grow       ();

            //! Pushes a value onto the stack.
            /*!
                \param _val The value to put on the stack.
             */
            void push       ( dataType _val );

            //! Pops a value off the stack.
            /*!
                \return The topmost value on the stack.
             */
            dataType pop    ();

            //! Indicates the number of items on the stack.
            /*!
                \return Number of items on the stack.
             */
            int count    () const;

            //! Empties the stack.
            /*!
                If pointers are stored in the stack, they must be freed manually via a series of pop() and delete or free() calls.
             */
            void empty      ();
        };
    }
}

#include <crisscross/dstack.cpp>

#endif
