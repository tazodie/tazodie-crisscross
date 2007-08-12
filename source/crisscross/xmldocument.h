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

#ifndef __included_xmldocument_h
#define __included_xmldocument_h

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

#include <crisscross/encoding.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLElement;
			class XMLDocument
			{
			protected:
				XMLElement *m_rootNode;
				CrissCross::Text::Encoding::charEncoding m_xmlEncoding;

			public:
				XMLDocument ();
				~XMLDocument();

				void setEncoding ( CrissCross::Text::Encoding::charEncoding _encoding );
				CrissCross::Text::Encoding::charEncoding getEncoding ();
			};
		}
	}
}

#endif
