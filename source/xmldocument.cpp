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

#include <crisscross/xml.h>

using namespace CrissCross::Text::Encoding;
using namespace CrissCross::Text::XML;

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			XMLDocument::XMLDocument ()
				: XMLNode ( NULL )
			{
				m_rootElement = NULL;
			}

			XMLDocument::~XMLDocument ()
			{
			}

			charEncoding
			XMLDocument::getEncoding ()
			{
				return m_xmlEncoding;
			}

			void
			XMLDocument::trim ( char *_buffer, size_t _bufSize )
			{
				size_t firstnotof = strspn ( _buffer, "\t " );
				memmove ( _buffer, &_buffer[firstnotof], _bufSize - firstnotof );
				
				char *_bufptr = _buffer + strlen(_buffer);
				while ( _bufptr-- >= _buffer )
				{
					if ( *_bufptr != '\t' && *_bufptr != ' ' )
					{
						*( _bufptr + 1 ) = '\x0';
						break;
					}
				}
			}

			int
			XMLDocument::load ( const char *_path )
			{
				CrissCross::IO::TextReader *tr = new CrissCross::IO::TextReader;
				tr->Open ( _path );
				int retval = load ( tr );
				tr->Close ();
				delete tr;
				return retval;
			}

			inline bool XMLDocument::IsWhiteSpace ( char c )		
			{ 
				return ( isspace( (unsigned char) c ) || c == '\n' || c == '\r' ); 
			}

			const char* XMLDocument::SkipWhiteSpace ( const char* p, CrissCross::Text::Encoding::charEncoding encoding )
			{
				if ( !p || !*p )
				{
					return 0;
				}
				if ( encoding == CHAR_ENCODING_UTF8 )
				{
					while ( *p )
					{
						const unsigned char* pU = (const unsigned char*)p;
						
						// Skip the stupid UTF-8 Byte order marks
						if (	*(pU+0)==0xefU
							 && *(pU+1)==0xbbU 
							 && *(pU+2)==0xbfU )
						{
							p += 3;
							continue;
						}
						else if(*(pU+0)==0xefU
							 && *(pU+1)==0xbfU
							 && *(pU+2)==0xbeU )
						{
							p += 3;
							continue;
						}
						else if(*(pU+0)==0xefU
							 && *(pU+1)==0xbfU
							 && *(pU+2)==0xbfU )
						{
							p += 3;
							continue;
						}

						if ( IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )		// Still using old rules for white space.
							++p;
						else
							break;
					}
				}
				else
				{
					while ( *p && IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )
						++p;
				}

				return p;
			}

			int
			XMLDocument::parse ( const char *_buffer )
			{
				std::cout << _buffer << std::endl;
				return 0;
			}

			int
			XMLDocument::load ( CrissCross::IO::TextReader *_file )
			{
				if ( !_file ) return CC_ERR_BADPARAMETER;
				if ( !_file->IsOpen() ) return CC_ERR_BADPARAMETER;
				
				size_t fileLen = (size_t)_file->Length();
				char *buffer = new char[fileLen + 1];
				_file->Read ( buffer, (int)fileLen + 1, 0, (int)fileLen );
				
				char *data = new char[fileLen + 1];
				char const *p = buffer;
				char const *lastPos = buffer;
				data[0] = '\x0';
				while ( *p )
				{
					CoreAssert ( p < (buffer + fileLen) );
					if ( *p == '\n' )
					{
						// No special rules.
						strncat ( data, lastPos, ( p - lastPos + 1 ) );
						lastPos = ++p;
						CoreAssert ( p <= (buffer + fileLen) );
					}
					else if ( *p == '\r' )
					{
						// Skip it, file should be UNIX format (newline only).
						strncat ( data, lastPos, ( p - lastPos ) );
						data += '\n';
						
						if ( *(p+1) == '\n' )
						{
							lastPos = ( p += 2 );
							CoreAssert ( p <= (buffer + fileLen) );
						}
						else
						{
							lastPos = ++p;
							CoreAssert ( p <= (buffer + fileLen) );
						}
					}
					else
					{
						++p;
					}
				}
				
				if ( p - lastPos )
				{
					strncat ( data, lastPos, ( p - lastPos ) );
				}

				delete [] buffer;
				buffer = NULL;

				int retval = parse ( data );
				delete [] data;
				return retval;
			}

			void
			XMLDocument::setEncoding ( charEncoding _encoding )
			{
				m_xmlEncoding = _encoding;
			}

			XMLElement *
			XMLDocument::getDocumentElement ()
			{
				CoreAssert ( m_rootElement );
				return m_rootElement;
			}
		}
	}
}
