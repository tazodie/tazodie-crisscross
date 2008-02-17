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

//@cond
typedef struct {
    unsigned int state[5];
    unsigned int count[2];
    unsigned char buffer[64];
} cc_sha1_ctx;
//@endcond

namespace CrissCross
{
    namespace Crypto
    {
		//! A SHA-1 hash generator.
		/*!
			\sa Hash SHA256Hash SHA512Hash TigerHash
		 */
        class SHA1Hash : public Hash
        {
private:
            cc_sha1_ctx m_state;
            unsigned char *m_hash;

public:
			//! The default constructor.
            SHA1Hash ();
			
			//! The default destructor.
            virtual ~SHA1Hash ();

			//! Runs a SHA-1 hash on the data provided.
			/*!
				\param _data The data to hash. The buffer does not need to be null
					terminated.
				\param _length The data length in bytes.
				\return Zero on success, nonzero on failure.
			 */
            int Process ( const void *_data, size_t _length );
			
			//! Resets the internal SHA-1 context and hash buffer.
            void Reset ();

			//! Converts the internal hash data into an hex string, a human readable format.
			/*!
				The memory location returned by this function is freed when the class
				is destructed.
			 */
            virtual const char *ToString () const;
			
			//! Equality operator.
			/*!
				Compares two instances of SHA1Hash to see if the hashes are equal.
			 */
			bool operator== ( const SHA1Hash &_other ) const;
			
			//! Inequality operator.
			/*!
				Compares two instances of SHA1Hash to see if the hashes are not equal.
			 */
			inline bool operator!= ( const SHA1Hash &_other ) const { return !( *this == _other ); };

        };
    }
}

#endif
