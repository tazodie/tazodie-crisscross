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

#ifndef __included_cc_md5_h
#define __included_cc_md5_h

#include <crisscross/hash.h>

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
    cc_int32_t i[2];          /* number of _bits_ handled mod 2^64 */
    cc_int32_t buf[4];        /* scratch buffer */
    unsigned char in[64];     /* input buffer */
    unsigned char digest[16]; /* actual digest after MD5Final call */
} cc_md5_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class MD5Hash : public Hash
        {
        private:
            cc_md5_ctx m_state;

        public:
            MD5Hash();
            virtual ~MD5Hash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
