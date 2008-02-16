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

#ifndef __included_cc_md2_h
#define __included_cc_md2_h

#include <crisscross/deprecate.h>
#include <crisscross/hash.h>

#define MD2_DIGEST_LENGTH       16

/* MD2 context. */
typedef struct  {
    unsigned char state[16];                               /* state */
    unsigned char checksum[16];                         /* checksum */
    unsigned int count;               /* number of bytes, modulo 16 */
    unsigned char buffer[16];                       /* input buffer */
} cc_md2_ctx;

namespace CrissCross
{
    namespace Crypto
    {
        class MD2Hash : public Hash
        {
private:
            unsigned char *m_hash;
            cc_md2_ctx m_state;

public:
            _CC_DEPRECATE_SLOW ("SEVERE") MD2Hash ();
            virtual ~MD2Hash ();

            int Process ( const void *_data, size_t _length );
            void Reset ();
            virtual const char *ToString () const;

        };
    }
}

#endif
