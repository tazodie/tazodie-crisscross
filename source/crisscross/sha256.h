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

#ifndef __included_cc_sha256_h
#define __included_cc_sha256_h

#include <crisscross/hash.h>

#define SHA256_DIGEST_SIZE ( 256 / 8)
#define SHA256_BLOCK_SIZE  ( 512 / 8)

typedef struct {
    unsigned int tot_len;
    unsigned int len;
    unsigned char block[2 * SHA256_BLOCK_SIZE];
    cc_uint32_t h[8];
} cc_sha256_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class SHA256Hash : public Hash
        {
        private:
            cc_sha256_ctx m_state;
            unsigned char *m_hash;

        public:
            SHA256Hash();
            virtual ~SHA256Hash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
