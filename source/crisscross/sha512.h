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

#ifndef __included_cc_sha512_h
#define __included_cc_sha512_h

#include <crisscross/deprecate.h>
#include <crisscross/hash.h>

#define SHA512_DIGEST_SIZE ( 512 / 8)
#define SHA512_BLOCK_SIZE  (1024 / 8)

typedef struct {
    unsigned int tot_len;
    unsigned int len;
    unsigned char block[2 * SHA512_BLOCK_SIZE];
    cc_uint64_t h[8];
} cc_sha512_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class SHA512Hash : public Hash
        {
        private:
            cc_sha512_ctx m_state;
            unsigned char *m_hash;

        public:
		#if TARGET_CPU_BITS < 64
			_CC_DEPRECATE_SLOW("MODERATE")
		#endif
            SHA512Hash();
            virtual ~SHA512Hash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
