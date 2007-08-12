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

#ifndef __included_xmlnamednodemap_h
#define __included_xmlnamednodemap_h

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLNamedNodeMap
			{
			protected:
				CrissCross::Data::RedBlackTree<std::string, XMLNode *>	m_nodeMap;
				CrissCross::Data::LList<XMLNode *>						m_nodeList;

			public:
				XMLNamedNodeMap ();
				~XMLNamedNodeMap ();

				XMLNode						*getNamedItem ( std::string _name );
				XMLNode						*setNamedItem ( XMLNode *_node );
				XMLNode						*removeNamedItem ( std::string _name );
				XMLNode						*item ( size_t _index );

				size_t						length ();
			};
		}
	}
}

#endif
