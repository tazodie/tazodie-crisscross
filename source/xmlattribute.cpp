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

using namespace CrissCross;
using namespace CrissCross::Data;
using namespace CrissCross::Text;
using namespace CrissCross::Text::Encoding;
using namespace CrissCross::Text::XML;
using namespace CrissCross::IO;

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{

			XMLAttribute::XMLAttribute ( CrissCross::Text::XML::XMLDocument *_ownerDocument )
			 : XMLNode ( _ownerDocument )
			{
				m_nodeType = ATTRIBUTE_NODE;
			}

			XMLAttribute::XMLAttribute ( CrissCross::Text::XML::XMLDocument *_ownerDocument, std::string _name, std::string _value )
			 : XMLNode ( _ownerDocument, _name, _value )
			{
				m_nodeType = ATTRIBUTE_NODE;
			}

			XMLAttribute::~XMLAttribute()
			{
			}
		}
	}
}
