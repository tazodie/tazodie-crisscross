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

#ifndef __included_xmlattribute_h
#define __included_xmlattribute_h

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

#include <crisscross/xmlnode.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLAttribute : public XMLNode
			{
			public:
				XMLAttribute ( XMLDocument *_ownerDocument );
				XMLAttribute ( XMLDocument *_ownerDocument, std::string _name, std::string _value );
				~XMLAttribute ();
			};
		}
	}
}

#endif
