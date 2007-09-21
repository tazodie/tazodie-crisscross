/*!<
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_encoding_h
#define __included_cc_encoding_h

namespace CrissCross
{
	namespace Text
	{
		namespace Encoding
		{
			typedef enum {
				CHAR_ENCODING_ERROR =    -1,		/*!< No char encoding detected */
				CHAR_ENCODING_NONE =	  0,		/*!< No char encoding detected */
				CHAR_ENCODING_UTF8 =	  1,		/*!< UTF-8 */
				CHAR_ENCODING_UTF16LE =	  2,		/*!< UTF-16 little endian */
				CHAR_ENCODING_UTF16BE =	  3,		/*!< UTF-16 big endian */
				CHAR_ENCODING_UCS4LE =	  4,		/*!< UCS-4 little endian */
				CHAR_ENCODING_UCS4BE =	  5,		/*!< UCS-4 big endian */
				CHAR_ENCODING_EBCDIC =	  6,		/*!< EBCDIC */
				CHAR_ENCODING_UCS4_2143 = 7,		/*!< UCS-4 unusual ordering */
				CHAR_ENCODING_UCS4_3412 = 8,		/*!< UCS-4 unusual ordering */
				CHAR_ENCODING_UCS2 =	  9,		/*!< UCS-2 */
				CHAR_ENCODING_8859_1 =	  10,		/*!< ISO-8859-1 ISO Latin 1 */
				CHAR_ENCODING_8859_2 =	  11,		/*!< ISO-8859-2 ISO Latin 2 */
				CHAR_ENCODING_8859_3 =	  12,		/*!< ISO-8859-3 */
				CHAR_ENCODING_8859_4 =	  13,		/*!< ISO-8859-4 */
				CHAR_ENCODING_8859_5 =	  14,		/*!< ISO-8859-5 */
				CHAR_ENCODING_8859_6 =	  15,		/*!< ISO-8859-6 */
				CHAR_ENCODING_8859_7 =	  16,		/*!< ISO-8859-7 */
				CHAR_ENCODING_8859_8 =	  17,		/*!< ISO-8859-8 */
				CHAR_ENCODING_8859_9 =	  18,		/*!< ISO-8859-9 */
				CHAR_ENCODING_2022_JP =   19,		/*!< ISO-2022-JP */
				CHAR_ENCODING_SHIFT_JIS = 20,		/*!< Shift_JIS */
				CHAR_ENCODING_EUC_JP =    21,		/*!< EUC-JP */
				CHAR_ENCODING_ASCII =     22		/*!< pure ASCII */
			} charEncoding;

			charEncoding DetectCharEncoding ( const unsigned char* in, size_t len );

			int asciiToUTF8 ( unsigned char* out, size_t *outlen, const unsigned char* in, size_t *inlen );
			int UTF8Toascii ( unsigned char* out, size_t *outlen, const unsigned char* in, size_t *inlen );
		}
	}
}

#endif
