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

#include <crisscross/universal_include.h>

#ifdef ENABLE_HASHES

#include <crisscross/core_io_reader.h>
#include <crisscross/sha256.h>

static cc_int32_t sha256_h0[8] =
{0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

static cc_int32_t sha256_k[64] =
{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

#define SHFR(x, n)    ( x >> n )
#define ROTR(x, n)   (( x >> n ) | ( x << (( sizeof( x ) << 3 ) - n )))
#define ROTL(x, n)   (( x << n ) | ( x >> (( sizeof( x ) << 3 ) - n )))
#define CH(x, y, z)  (( x & y ) ^ ( ~x & z ))
#define MAJ(x, y, z) (( x & y ) ^ ( x & z ) ^ ( y & z ))

#define SHA256_F1(x) ( ROTR (x,  2) ^ ROTR (x, 13) ^ ROTR (x, 22))
#define SHA256_F2(x) ( ROTR (x,  6) ^ ROTR (x, 11) ^ ROTR (x, 25))
#define SHA256_F3(x) ( ROTR (x,  7) ^ ROTR (x, 18) ^ SHFR (x,  3))
#define SHA256_F4(x) ( ROTR (x, 17) ^ ROTR (x, 19) ^ SHFR (x, 10))

#define UNPACK32(x, str)                      \
    {                                             \
        *(( str ) + 3 ) = (cc_uint8_t)(( x )      );       \
        *(( str ) + 2 ) = (cc_uint8_t)(( x ) >>  8 );       \
        *(( str ) + 1 ) = (cc_uint8_t)(( x ) >> 16 );       \
        *(( str ) + 0 ) = (cc_uint8_t)(( x ) >> 24 );       \
    }

#define PACK32(str, x)                        \
    {                                             \
        *( x ) =   ((cc_uint32_t)*(( str ) + 3 )      )    \
                 | ((cc_uint32_t)*(( str ) + 2 ) <<  8 )    \
                 | ((cc_uint32_t)*(( str ) + 1 ) << 16 )    \
                 | ((cc_uint32_t)*(( str ) + 0 ) << 24 );   \
    }

#define SHA256_SCR(i)                         \
    {                                             \
        w[i] =  SHA256_F4 (w[i -  2]) + w[i -  7]  \
               + SHA256_F3 (w[i - 15]) + w[i - 16]; \
    }

#define SHA256_EXP(a, b, c, d, e, f, g, h, j)               \
    {                                                           \
        t1 = wv[h] + SHA256_F2 (wv[e]) + CH (wv[e], wv[f], wv[g]) \
             + sha256_k[j] + w[j];                              \
        t2 = SHA256_F1 (wv[a]) + MAJ (wv[a], wv[b], wv[c]);       \
        wv[d] += t1;                                            \
        wv[h] = t1 + t2;                                        \
    }

static void sha256_transf ( cc_sha256_ctx *ctx, const unsigned char *message,
                            unsigned int block_nb )
{
    cc_uint32_t w[64];
    cc_uint32_t wv[8];
    cc_uint32_t t1, t2;
    const unsigned char *sub_block;
    int i;

#ifndef UNROLL_LOOPS
    int j;
#endif

    for (i = 0; i < (int)block_nb; i++){
        sub_block = message + ( i << 6 );

#ifndef UNROLL_LOOPS
        for (j = 0; j < 16; j++){
            PACK32 (&sub_block[j << 2], &w[j]);
        }

        for (j = 16; j < 64; j++){
            SHA256_SCR (j);
        }

        for (j = 0; j < 8; j++){
            wv[j] = ctx->h[j];
        }

        for (j = 0; j < 64; j++){
            t1 = wv[7] + SHA256_F2 (wv[4]) + CH (wv[4], wv[5], wv[6])
                 + sha256_k[j] + w[j];
            t2 = SHA256_F1 (wv[0]) + MAJ (wv[0], wv[1], wv[2]);
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }

        for (j = 0; j < 8; j++){
            ctx->h[j] += wv[j];
        }
#else
        PACK32 (&sub_block[ 0], &w[ 0]); PACK32 (&sub_block[ 4], &w[ 1]);
        PACK32 (&sub_block[ 8], &w[ 2]); PACK32 (&sub_block[12], &w[ 3]);
        PACK32 (&sub_block[16], &w[ 4]); PACK32 (&sub_block[20], &w[ 5]);
        PACK32 (&sub_block[24], &w[ 6]); PACK32 (&sub_block[28], &w[ 7]);
        PACK32 (&sub_block[32], &w[ 8]); PACK32 (&sub_block[36], &w[ 9]);
        PACK32 (&sub_block[40], &w[10]); PACK32 (&sub_block[44], &w[11]);
        PACK32 (&sub_block[48], &w[12]); PACK32 (&sub_block[52], &w[13]);
        PACK32 (&sub_block[56], &w[14]); PACK32 (&sub_block[60], &w[15]);

        SHA256_SCR (16); SHA256_SCR (17); SHA256_SCR (18); SHA256_SCR (19);
        SHA256_SCR (20); SHA256_SCR (21); SHA256_SCR (22); SHA256_SCR (23);
        SHA256_SCR (24); SHA256_SCR (25); SHA256_SCR (26); SHA256_SCR (27);
        SHA256_SCR (28); SHA256_SCR (29); SHA256_SCR (30); SHA256_SCR (31);
        SHA256_SCR (32); SHA256_SCR (33); SHA256_SCR (34); SHA256_SCR (35);
        SHA256_SCR (36); SHA256_SCR (37); SHA256_SCR (38); SHA256_SCR (39);
        SHA256_SCR (40); SHA256_SCR (41); SHA256_SCR (42); SHA256_SCR (43);
        SHA256_SCR (44); SHA256_SCR (45); SHA256_SCR (46); SHA256_SCR (47);
        SHA256_SCR (48); SHA256_SCR (49); SHA256_SCR (50); SHA256_SCR (51);
        SHA256_SCR (52); SHA256_SCR (53); SHA256_SCR (54); SHA256_SCR (55);
        SHA256_SCR (56); SHA256_SCR (57); SHA256_SCR (58); SHA256_SCR (59);
        SHA256_SCR (60); SHA256_SCR (61); SHA256_SCR (62); SHA256_SCR (63);

        wv[0] = ctx->h[0]; wv[1] = ctx->h[1];
        wv[2] = ctx->h[2]; wv[3] = ctx->h[3];
        wv[4] = ctx->h[4]; wv[5] = ctx->h[5];
        wv[6] = ctx->h[6]; wv[7] = ctx->h[7];

        SHA256_EXP (0,1,2,3,4,5,6,7, 0); SHA256_EXP (7,0,1,2,3,4,5,6, 1);
        SHA256_EXP (6,7,0,1,2,3,4,5, 2); SHA256_EXP (5,6,7,0,1,2,3,4, 3);
        SHA256_EXP (4,5,6,7,0,1,2,3, 4); SHA256_EXP (3,4,5,6,7,0,1,2, 5);
        SHA256_EXP (2,3,4,5,6,7,0,1, 6); SHA256_EXP (1,2,3,4,5,6,7,0, 7);
        SHA256_EXP (0,1,2,3,4,5,6,7, 8); SHA256_EXP (7,0,1,2,3,4,5,6, 9);
        SHA256_EXP (6,7,0,1,2,3,4,5,10); SHA256_EXP (5,6,7,0,1,2,3,4,11);
        SHA256_EXP (4,5,6,7,0,1,2,3,12); SHA256_EXP (3,4,5,6,7,0,1,2,13);
        SHA256_EXP (2,3,4,5,6,7,0,1,14); SHA256_EXP (1,2,3,4,5,6,7,0,15);
        SHA256_EXP (0,1,2,3,4,5,6,7,16); SHA256_EXP (7,0,1,2,3,4,5,6,17);
        SHA256_EXP (6,7,0,1,2,3,4,5,18); SHA256_EXP (5,6,7,0,1,2,3,4,19);
        SHA256_EXP (4,5,6,7,0,1,2,3,20); SHA256_EXP (3,4,5,6,7,0,1,2,21);
        SHA256_EXP (2,3,4,5,6,7,0,1,22); SHA256_EXP (1,2,3,4,5,6,7,0,23);
        SHA256_EXP (0,1,2,3,4,5,6,7,24); SHA256_EXP (7,0,1,2,3,4,5,6,25);
        SHA256_EXP (6,7,0,1,2,3,4,5,26); SHA256_EXP (5,6,7,0,1,2,3,4,27);
        SHA256_EXP (4,5,6,7,0,1,2,3,28); SHA256_EXP (3,4,5,6,7,0,1,2,29);
        SHA256_EXP (2,3,4,5,6,7,0,1,30); SHA256_EXP (1,2,3,4,5,6,7,0,31);
        SHA256_EXP (0,1,2,3,4,5,6,7,32); SHA256_EXP (7,0,1,2,3,4,5,6,33);
        SHA256_EXP (6,7,0,1,2,3,4,5,34); SHA256_EXP (5,6,7,0,1,2,3,4,35);
        SHA256_EXP (4,5,6,7,0,1,2,3,36); SHA256_EXP (3,4,5,6,7,0,1,2,37);
        SHA256_EXP (2,3,4,5,6,7,0,1,38); SHA256_EXP (1,2,3,4,5,6,7,0,39);
        SHA256_EXP (0,1,2,3,4,5,6,7,40); SHA256_EXP (7,0,1,2,3,4,5,6,41);
        SHA256_EXP (6,7,0,1,2,3,4,5,42); SHA256_EXP (5,6,7,0,1,2,3,4,43);
        SHA256_EXP (4,5,6,7,0,1,2,3,44); SHA256_EXP (3,4,5,6,7,0,1,2,45);
        SHA256_EXP (2,3,4,5,6,7,0,1,46); SHA256_EXP (1,2,3,4,5,6,7,0,47);
        SHA256_EXP (0,1,2,3,4,5,6,7,48); SHA256_EXP (7,0,1,2,3,4,5,6,49);
        SHA256_EXP (6,7,0,1,2,3,4,5,50); SHA256_EXP (5,6,7,0,1,2,3,4,51);
        SHA256_EXP (4,5,6,7,0,1,2,3,52); SHA256_EXP (3,4,5,6,7,0,1,2,53);
        SHA256_EXP (2,3,4,5,6,7,0,1,54); SHA256_EXP (1,2,3,4,5,6,7,0,55);
        SHA256_EXP (0,1,2,3,4,5,6,7,56); SHA256_EXP (7,0,1,2,3,4,5,6,57);
        SHA256_EXP (6,7,0,1,2,3,4,5,58); SHA256_EXP (5,6,7,0,1,2,3,4,59);
        SHA256_EXP (4,5,6,7,0,1,2,3,60); SHA256_EXP (3,4,5,6,7,0,1,2,61);
        SHA256_EXP (2,3,4,5,6,7,0,1,62); SHA256_EXP (1,2,3,4,5,6,7,0,63);

        ctx->h[0] += wv[0]; ctx->h[1] += wv[1];
        ctx->h[2] += wv[2]; ctx->h[3] += wv[3];
        ctx->h[4] += wv[4]; ctx->h[5] += wv[5];
        ctx->h[6] += wv[6]; ctx->h[7] += wv[7];
#endif /* !UNROLL_LOOPS */
    }
}

static void sha256_init ( cc_sha256_ctx *ctx )
{
#ifndef UNROLL_LOOPS
    int i;
    for (i = 0; i < 8; i++){
        ctx->h[i] = sha256_h0[i];
    }
#else
    ctx->h[0] = sha256_h0[0]; ctx->h[1] = sha256_h0[1];
    ctx->h[2] = sha256_h0[2]; ctx->h[3] = sha256_h0[3];
    ctx->h[4] = sha256_h0[4]; ctx->h[5] = sha256_h0[5];
    ctx->h[6] = sha256_h0[6]; ctx->h[7] = sha256_h0[7];
#endif /* !UNROLL_LOOPS */

    ctx->len = 0;
    ctx->tot_len = 0;
}

static void sha256_update ( cc_sha256_ctx *ctx, const unsigned char *message,
                            unsigned int len )
{
    unsigned int block_nb;
    unsigned int new_len, rem_len, tmp_len;
    const unsigned char *shifted_message;

    tmp_len = SHA256_BLOCK_SIZE - ctx->len;
    rem_len = len < tmp_len ? len : tmp_len;

    memcpy (&ctx->block[ctx->len], message, rem_len);

    if (ctx->len + len < SHA256_BLOCK_SIZE){
        ctx->len += len;
        return;
    }

    new_len = len - rem_len;
    block_nb = new_len / SHA256_BLOCK_SIZE;

    shifted_message = message + rem_len;

    sha256_transf (ctx, ctx->block, 1);
    sha256_transf (ctx, shifted_message, block_nb);

    rem_len = new_len % SHA256_BLOCK_SIZE;

    memcpy (ctx->block, &shifted_message[block_nb << 6],
            rem_len);

    ctx->len = rem_len;
    ctx->tot_len += ( block_nb + 1 ) << 6;
}

static void sha256_final ( cc_sha256_ctx *ctx, unsigned char *digest )
{
    unsigned int block_nb;
    unsigned int pm_len;
    unsigned int len_b;

#ifndef UNROLL_LOOPS
    int i;
#endif

    block_nb = ( 1 + (( SHA256_BLOCK_SIZE - 9 )
                      < ( ctx->len % SHA256_BLOCK_SIZE )));

    len_b = ( ctx->tot_len + ctx->len ) << 3;
    pm_len = block_nb << 6;

    memset (ctx->block + ctx->len, 0, pm_len - ctx->len);
    ctx->block[ctx->len] = 0x80;
    UNPACK32 (len_b, ctx->block + pm_len - 4);

    sha256_transf (ctx, ctx->block, block_nb);

#ifndef UNROLL_LOOPS
    for (i = 0 ; i < 8; i++){
        UNPACK32 (ctx->h[i], &digest[i << 2]);
    }
#else
    UNPACK32 (ctx->h[0], &digest[ 0]);
    UNPACK32 (ctx->h[1], &digest[ 4]);
    UNPACK32 (ctx->h[2], &digest[ 8]);
    UNPACK32 (ctx->h[3], &digest[12]);
    UNPACK32 (ctx->h[4], &digest[16]);
    UNPACK32 (ctx->h[5], &digest[20]);
    UNPACK32 (ctx->h[6], &digest[24]);
    UNPACK32 (ctx->h[7], &digest[28]);
#endif /* !UNROLL_LOOPS */
}

namespace CrissCross
{
    namespace Crypto
    {
        SHA256Hash::SHA256Hash () : m_hashString (NULL), m_hash (NULL)
        {
            Reset ();
        }

        SHA256Hash::~SHA256Hash ()
        {
            Reset ();
        }

        int SHA256Hash::Process ( const void * _data, size_t _length )
        {
            Reset ();
            if ( !_length || !_data ) return -1;

            sha256_update ( &m_state,(const unsigned char *)_data, _length );
            m_hash = new unsigned char[SHA256_DIGEST_SIZE];
            sha256_final ( &m_state, m_hash );
            return 0;
        }

        int SHA256Hash::Process ( CrissCross::IO::CoreIOReader *_reader )
        {
            Reset ();
            if ( !_reader ) return -1;

            cc_int64_t pos = _reader->Position ();
            _reader->Seek ( 0 );
            char buffer[8192]; int bytesRead = 0;
            do
            {
                bytesRead = _reader->Read ( buffer, sizeof( buffer ), 0, sizeof( buffer ) );
                if ( bytesRead >= 0 )
                    ProcessBlock ( buffer, bytesRead );
            } while ( bytesRead == sizeof( buffer ) && !_reader->EndOfFile () );
            Finalize ();
            _reader->Seek ( pos );
            return 0;
        }

        int SHA256Hash::ProcessBlock ( const void * _data, size_t _length )
        {
            if ( !_data ) return -1;

            sha256_update ( &m_state, (unsigned char *)_data, _length );
            return 0;
        }

        void SHA256Hash::Finalize ()
        {
            if ( m_hash ) delete [] m_hash;

            m_hash = new unsigned char[SHA256_DIGEST_SIZE];
            sha256_final ( &m_state, m_hash );
        }

        const char *SHA256Hash::ToString () const
        {
            if ( m_hashString ) return m_hashString;

            m_hashString = new char[SHA256_DIGEST_SIZE * 2 + 1];
            for ( int i = 0; i < SHA256_DIGEST_SIZE; i++ )
                sprintf ( m_hashString + ( i * 2 ), "%02x", m_hash[i] );
            return m_hashString;
        }

        void SHA256Hash::Reset ()
        {
            delete [] m_hash; m_hash = NULL;
            delete [] m_hashString; m_hashString = NULL;

            sha256_init ( &m_state );
        }

        bool SHA256Hash::operator== ( const SHA256Hash &_other ) const
        {
            return ( memcmp ( m_hash, _other.m_hash, SHA256_DIGEST_SIZE ) == 0 );
        }
    }
}

#endif
