/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>

#include <crisscross/encoding.h>

using namespace CrissCross;
using namespace CrissCross::Text;
using namespace CrissCross::Text::Encoding;
using namespace CrissCross::IO;

namespace CrissCross
{
	namespace Text
	{
		namespace Encoding
		{

			charEncoding DetectCharEncoding ( const unsigned char* in, size_t len )
			{
				if (in == NULL) 
					return(CHAR_ENCODING_NONE);
				if (len >= 4) {
				if ((in[0] == 0x00) && (in[1] == 0x00) &&
					(in[2] == 0x00) && (in[3] == 0x3C))
					return(CHAR_ENCODING_UCS4BE);
				if ((in[0] == 0x3C) && (in[1] == 0x00) &&
					(in[2] == 0x00) && (in[3] == 0x00))
					return(CHAR_ENCODING_UCS4LE);
				if ((in[0] == 0x00) && (in[1] == 0x00) &&
					(in[2] == 0x3C) && (in[3] == 0x00))
					return(CHAR_ENCODING_UCS4_2143);
				if ((in[0] == 0x00) && (in[1] == 0x3C) &&
					(in[2] == 0x00) && (in[3] == 0x00))
					return(CHAR_ENCODING_UCS4_3412);
				if ((in[0] == 0x4C) && (in[1] == 0x6F) &&
					(in[2] == 0xA7) && (in[3] == 0x94))
					return(CHAR_ENCODING_EBCDIC);
				if ((in[0] == 0x3C) && (in[1] == 0x3F) &&
					(in[2] == 0x78) && (in[3] == 0x6D))
					return(CHAR_ENCODING_UTF8);
				/*
				 * Although not part of the recommendation, we also
				 * attempt an "auto-recognition" of UTF-16LE and
				 * UTF-16BE encodings.
				 */
				if ((in[0] == 0x3C) && (in[1] == 0x00) &&
					(in[2] == 0x3F) && (in[3] == 0x00))
					return(CHAR_ENCODING_UTF16LE);
				if ((in[0] == 0x00) && (in[1] == 0x3C) &&
					(in[2] == 0x00) && (in[3] == 0x3F))
					return(CHAR_ENCODING_UTF16BE);
				}
				if (len >= 3) {
					/*
					 * Errata on XML-1.0 June 20 2001
					 * We now allow an UTF8 encoded BOM
					 */
					if ((in[0] == 0xEF) && (in[1] == 0xBB) &&
						(in[2] == 0xBF))
						return(CHAR_ENCODING_UTF8);
					}
					/* For UTF-16 we can recognize by the BOM */
					if (len >= 2) {
					if ((in[0] == 0xFE) && (in[1] == 0xFF))
						return(CHAR_ENCODING_UTF16BE);
					if ((in[0] == 0xFF) && (in[1] == 0xFE))
						return(CHAR_ENCODING_UTF16LE);
				}
				return(CHAR_ENCODING_NONE);
			}

			int
			asciiToUTF8 ( unsigned char* out, size_t *outlen, const unsigned char* in, size_t *inlen ) {
				unsigned char* outstart = out;
				const unsigned char* base = in;
				const unsigned char* processed = in;
				unsigned char* outend = out + *outlen;
				const unsigned char* inend;
				unsigned int c;

				inend = in + (*inlen);
				while ((in < inend) && (out - outstart + 5U < *outlen)) {
				c= *in++;

					if (out >= outend)
					break;
					if (c < 0x80) {
					*out++ = c;
				} else { 
					*outlen = out - outstart;
					*inlen = processed - base;
					return(-1);
				}
			 
				processed = (const unsigned char*) in;
				}
				*outlen = out - outstart;
				*inlen = processed - base;
				return (int)(*outlen);
			}

			int
			UTF8Toascii ( unsigned char* out, size_t *outlen, const unsigned char* in, size_t *inlen ) {
				const unsigned char* processed = in;
				const unsigned char* outend;
				const unsigned char* outstart = out;
				const unsigned char* instart = in;
				const unsigned char* inend;
				unsigned int c, d;
				int trailing;

				if ((out == NULL) || (outlen == NULL) || (inlen == NULL)) return(-1);
				if (in == NULL) {
					/*
					* initialization nothing to do
					*/
					*outlen = 0;
					*inlen = 0;
					return(0);
				}
				inend = in + (*inlen);
				outend = out + (*outlen);
				while (in < inend) {
				d = *in++;
				if      (d < 0x80)  { c= d; trailing= 0; }
				else if (d < 0xC0) {
					/* trailing byte in leading position */
					*outlen = out - outstart;
					*inlen = processed - instart;
					return(-2);
					} else if (d < 0xE0)  { c= d & 0x1F; trailing= 1; }
					else if (d < 0xF0)  { c= d & 0x0F; trailing= 2; }
					else if (d < 0xF8)  { c= d & 0x07; trailing= 3; }
				else {
					/* no chance for this in Ascii */
					*outlen = out - outstart;
					*inlen = processed - instart;
					return(-2);
				}

				if (inend - in < trailing) {
					break;
				} 

				for ( ; trailing; trailing--) {
					if ((in >= inend) || (((d= *in++) & 0xC0) != 0x80))
					break;
					c <<= 6;
					c |= d & 0x3F;
				}

				/* assertion: c is a single UTF-4 value */
				if (c < 0x80) {
					if (out >= outend)
					break;
					*out++ = c;
				} else {
					/* no chance for this in Ascii */
					*outlen = out - outstart;
					*inlen = processed - instart;
					return(-2);
				}
				processed = in;
				}
				*outlen = out - outstart;
				*inlen = processed - instart;
				return (int)(*outlen);
			}
		}
	}
}