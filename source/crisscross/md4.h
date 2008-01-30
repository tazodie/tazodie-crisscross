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

#ifndef __included_cc_md4_h
#define __included_cc_md4_h

#include <crisscross/deprecate.h>
#include <crisscross/hash.h>

#define	MD4_DIGEST_LENGTH	16

/* MD4 context. */
typedef struct	{
  cc_uint32_t state[4];                                   /* state (ABCD) */
  cc_uint32_t count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} cc_md4_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class MD4Hash : public Hash
        {
        private:
            unsigned char *m_hash;
            cc_md4_ctx m_state;

        public:
            MD4Hash();
            virtual ~MD4Hash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
