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
        /*
         * TODO:
         *      - Logical operators.
         *      - Retrieve checksum value as string or as a long if possible.
         */

        class Hash
        {
protected:
            mutable char *m_hashString;

public:
            Hash ();
            virtual ~Hash ();

            virtual int Process ( const void *_data, size_t _length ) = 0;
            virtual void Reset () = 0;
            virtual const char *ToString () const = 0;

        };
    }
}

#endif
