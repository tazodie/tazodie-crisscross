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

#ifndef __included_xmlelement_h
#define __included_xmlelement_h

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

#include <crisscross/xmlnode.h>
#include <crisscross/xmlattribute.h>
#include <crisscross/xmlparser.h>

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
			};
		}
	}
}

#endif
