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

#ifndef __included_xmlparser_h
#define __included_xmlparser_h

#include <crisscross/textreader.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLParser
			{
			private:
				CrissCross::Text::XML::XMLDocument *m_document;

				//! Trim all whitespace in the string.
				/*!
					\param _string The pointer to the string to trim.
					\param _bufSize The size of the buffer referenced by _string.
				 */
				void trim ( char *_string, size_t _bufSize );

				XMLAttribute *parseAttribute ( const char *_buffer );

			public:
				XMLParser ();
				// Implement the alternate constructors later.
				//XMLParser ( const char *_path );
				//XMLParser ( CrissCross::IO::TextReader *_file );
				~XMLParser();

				int parse ( const char *_path );
				int parse ( CrissCross::IO::TextReader *_file );
			};
		}
	}
}

#endif
