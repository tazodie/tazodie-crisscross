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

#ifndef __included_cc_xmlelement_h
#define __included_cc_xmlelement_h

#include <crisscross/llist.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLElement : public XMLNode
			{
			protected:
				CrissCross::Data::LList<XMLElement *> m_subElements;
				CrissCross::Data::LList<XMLAttribute *> m_attributes;
			public:
				XMLElement ( CrissCross::Text::XML::XMLDocument *_ownerDocument );
				~XMLElement();
			};
		}
	}
}

#endif
