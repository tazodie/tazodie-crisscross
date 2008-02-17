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

#define SHA512_DIGEST_SIZE ( 512 / 8 )
#define SHA512_BLOCK_SIZE  ( 1024 / 8 )

//@cond
typedef struct {
    unsigned int tot_len;
    unsigned int len;
    unsigned char block[2 * SHA512_BLOCK_SIZE];
    cc_uint64_t h[8];
} cc_sha512_ctx;
//@endcond

namespace CrissCross
{
    namespace Crypto
    {
		//! A SHA-512 hash generator.
		/*!
			\warning When compiled as 32-bit code, this hash is particularly slow.
				When compiled as 64-bit code, this hash type can actually be faster
				to generate than a SHA-256 hash.
			\sa Hash SHA1Hash SHA256Hash TigerHash
		 */
        class SHA512Hash : public Hash
        {
private:
            cc_sha512_ctx m_state;
            unsigned char *m_hash;

public:
			//! The default constructor.
                #if TARGET_CPU_BITS < 64
            _CC_DEPRECATE_SLOW ("MODERATE")
                #endif
            SHA512Hash ();
			
			//! The default destructor.
            virtual ~SHA512Hash ();

			//! Runs a SHA-512 hash on the data provided.
			/*!
				\param _data The data to hash. The buffer does not need to be null
					terminated.
				\param _length The data length in bytes.
				\return Zero on success, nonzero on failure.
			 */
            int Process ( const void *_data, size_t _length );
			
			//! Resets the internal SHA-512 context and hash buffer.
            void Reset ();

			//! Converts the internal hash data into an hex string, a human readable format.
			/*!
				The memory location returned by this function is freed when the class
				is destructed.
			 */
            virtual const char *ToString () const;

        };
    }
}

#endif
