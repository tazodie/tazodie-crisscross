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

#ifndef __included_cc_sha1_h
#define __included_cc_sha1_h

#include <crisscross/hash.h>

#define SHA1_DIGEST_SIZE 20

typedef struct {
    unsigned long state[5];
    unsigned long count[2];
    unsigned char buffer[64];
} cc_sha1_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class SHA1Hash : public Hash
        {
        private:
            cc_sha1_ctx m_state;
            unsigned char *m_hash;

        public:
            SHA1Hash();
            virtual ~SHA1Hash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
