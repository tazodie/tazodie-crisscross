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

#define SHA256_DIGEST_SIZE ( 256 / 8 )
#define SHA256_BLOCK_SIZE  ( 512 / 8 )

//@cond
typedef struct {
    unsigned int tot_len;
    unsigned int len;
    unsigned char block[2 * SHA256_BLOCK_SIZE];
    cc_uint32_t h[8];
} cc_sha256_ctx;
//@endcond

namespace CrissCross
{
    namespace Crypto
    {
        //! A SHA-256 hash generator.
        /*!
         \sa Hash SHA1Hash SHA512Hash TigerHash
         */
        class SHA256Hash : public Hash
        {
private:
            cc_sha256_ctx m_state;
            unsigned char *m_hash;

public:
            //! The default constructor.
            SHA256Hash ();

            //! The default destructor.
            virtual ~SHA256Hash ();

            //! Runs a SHA-256 hash on the data provided.
            /*!
             \param _data The data to hash. The buffer does not need to be null
                            terminated.
             \param _length The data length in bytes.
             \return Zero on success, nonzero on failure.
             */
            int Process ( const void *_data, size_t _length );

            //! Resets the internal SHA-256 context and hash buffer.
            void Reset ();

            //! Converts the internal hash data into an hex string, a human readable format.
            /*!
                    The memory location returned by this function is freed when the class
                    is destructed.
             */
            virtual const char *ToString () const;

            //! Equality operator.
            /*!
                    Compares two instances of SHA256Hash to see if the hashes are equal.
             \param _other The other instance of SHA256Hash to compare to.
             */
            bool operator== ( const SHA256Hash &_other ) const;

            //! Inequality operator.
            /*!
                    Compares two instances of SHA256Hash to see if the hashes are not equal.
             \param _other The other instance of SHA256Hash to compare to.
             */
            inline bool operator!= ( const SHA256Hash &_other ) const {
                return !( *this == _other );
            };

        };
    }
}

#endif
