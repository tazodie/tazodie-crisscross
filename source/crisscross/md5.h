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

#define	MD5_DIGEST_LENGTH	16

/* MD5 context. */
typedef struct	{
	cc_uint32_t state[4];	/* state (ABCD) */
	cc_uint32_t count[2];	/* number of bits, modulo 2^64 (lsb first) */
	union	{
		cc_uint8_t  buf8[64];	/* undigested input */
		cc_uint32_t	buf32[16];	/* realigned input */
	} buf_un;
} cc_md5_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class MD5Hash : public Hash
        {
        private:
            unsigned char *m_hash;
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
