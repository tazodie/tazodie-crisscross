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

#if 0

#include <crisscross/error.h>
#include <crisscross/encoding.h>
#include <crisscross/xml.h>

using namespace CrissCross;
using namespace CrissCross::Text;
using namespace CrissCross::Text::Encoding;
using namespace CrissCross::Text::XML;
using namespace CrissCross::IO;

XMLParser::XMLParser()
{
	m_document = new CrissCross::Text::XML::XMLDocument;
	m_document->setEncoding ( CHAR_ENCODING_NONE );
}

XMLParser::~XMLParser()
{
}

void
XMLParser::trim ( char *_buffer, size_t _bufSize )
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
XMLParser::parse ( const char *_path )
{
	TextReader *tr = new TextReader;
	tr->Open ( _path );
	int retval = parse ( tr );
	tr->Close ();
	delete tr;
	return retval;
}

XMLAttribute *
XMLParser::parseAttribute ( const char *_buffer )
{
	XMLAttribute *attr = NULL;
	char attributeName[256], attributeValue[512];
	memset ( attributeName, 0, sizeof ( attributeName ) );
	memset ( attributeValue, 0, sizeof ( attributeValue ) );

	const char *eq = strchr ( _buffer, '=' );
	if ( eq == NULL ) return NULL;
	if ( eq - _buffer > 254 ) return NULL;
	strncpy ( attributeName, _buffer, eq - _buffer );
	
	eq++;
	if ( *eq != '"' ) return NULL;
	eq++;
	const char *endq = strchr ( eq, '"' );
	if ( endq == NULL ) return NULL;
	if ( endq - eq > 510 ) return NULL;
	strncpy ( attributeValue, eq, endq - eq );


	attr = new XMLAttribute ( m_document );
	attr->setNodeName ( attributeName );
	attr->setNodeValue ( attributeValue );

	return attr;
}

int
XMLParser::parse ( CrissCross::IO::TextReader *_file )
{
	if ( !_file ) return CC_ERR_BADPARAMETER;
	if ( !_file->IsOpen() ) return CC_ERR_BADPARAMETER;
	
	char buffer[512], *bufPtr; size_t buflen;
	XMLNode *activeNode = NULL;
	while ( _file->ReadLine ( buffer, sizeof(buffer) ) > 0 )
	{
		if ( m_document->getEncoding() == CHAR_ENCODING_NONE )
		{
			m_document->setEncoding ( DetectCharEncoding ( (unsigned char *)buffer, strlen ( (char *)buffer ) ) );
			if ( m_document->getEncoding() == CHAR_ENCODING_UTF8 )
			{
				// Trim out UTF-8 byte order mark (BOM).
				if ( strncmp ( buffer, "\xEF\xBB\xBF", 3 ) == 0 )
					memmove ( buffer, buffer + 3, sizeof(buffer) - 3 );
			}
		}
		trim ( buffer, sizeof(buffer) );
		buflen = strlen ( buffer );

		bufPtr = buffer;
		while ( ( bufPtr - buffer ) < buflen )
		{
			switch ( *bufPtr )
			{
			case '<':
				
				break;
			}
		}
		g_stdout->WriteLine ( "XMLParser: %s", buffer );
	}

	return CC_ERR_NONE;
}

#endif
