/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_hash_h
#define __included_cc_hash_h

namespace CrissCross
{
    namespace Crypto
    {
        //! An abstract Hash class.
        class Hash
        {
protected:
            mutable char *m_hashString;

public:
            //! The default constructor.
            Hash ();

            //! The default destructor.
            virtual ~Hash ();

            //! Abstract hash generator function.
            virtual int Process ( const void *_data, size_t _length ) = 0;

            //! Abstract reset function.
            virtual void Reset () = 0;

            //! Abstract string conversion function.
            virtual const char *ToString () const = 0;
        };
    }
}

#endif
