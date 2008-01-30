/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_sha256_h
#define __included_sha256_h

struct sha256_state {
	cc_uint64_t length;
	cc_uint32_t state[8], curlen;
	cc_uint8_t buf[64];
};

void sha256_init(struct sha256_state *md);
int sha256_process(struct sha256_state *md, const unsigned char *in, unsigned long inlen);
int sha256_done(struct sha256_state *md, unsigned char *out);


#endif
