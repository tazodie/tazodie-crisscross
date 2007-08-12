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

#include <crisscross/xmldocument.h>

using namespace CrissCross::Text::Encoding;
using namespace CrissCross::Text::XML;

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			XMLDocument::XMLDocument ()
			{
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
			XMLDocument::setEncoding ( charEncoding _encoding )
			{
				m_xmlEncoding = _encoding;
			}
		}
	}
}