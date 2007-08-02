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

#ifndef __included_cc_dstack_h
#define __included_cc_dstack_h

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
            size_t          m_stepSize;
            
            //! The actual stack itself.
            dataType        *m_bottom;

            //! The pointer to the current position in the stack.
            dataType        *m_top;

            //! The size of the stack.
            size_t          m_size;

            //! The original size of the stack (used on an empty() call to reset things to defaults).
            size_t          m_origSize;

        public:
            //! The constructor.
            /*!
                \param _size The step size to use.
             */
            DStack          ( size_t _size = 32 );

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
            
            //! Returns whatever value is on the top of the stack without removing it from the stack.
            /*!
                \return The topmost value on the stack.
             */
            const dataType &peek    ();

            //! Indicates the number of items on the stack.
            /*!
                \return Number of items on the stack.
             */
            size_t count    () const;

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
