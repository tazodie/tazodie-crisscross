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

#ifndef __included_xmlnode_h
#define __included_xmlnode_h

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

#include <crisscross/xmldocument.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			typedef enum
			{
				NULL_NODE = 0,
				ELEMENT_NODE = 1,
				ATTRIBUTE_NODE = 2,
				TEXT_NODE = 3,
				CDATA_SECTION_NODE = 4,
				ENTITY_REFERENCE_NODE = 5,
				ENTITY_NODE = 6,
				PROCESSING_INSTRUCTION_NODE = 7,
				COMMENT_NODE = 8,
				DOCUMENT_NODE = 9,
				DOCUMENT_TYPE_NODE = 10,
				DOCUMENT_FRAGMENT_NODE = 11,
				NOTATION_NODE = 12
			} nodeType;

			class XMLAttribute;

			class XMLNode
			{
			protected:
				nodeType		m_nodeType;
				XMLDocument		*m_ownerDocument;

				std::string		m_nodeName;
				std::string		m_nodeValue;

				XMLNode			*m_parentNode;
				CrissCross::Data::LList<XMLNode *> m_childNodes;
				CrissCross::Data::LList<XMLAttribute *> m_attributes;

			public:
				//XMLNode ();
				XMLNode ( CrissCross::Text::XML::XMLDocument *_ownerDocument );
				XMLNode ( CrissCross::Text::XML::XMLDocument *_ownerDocument, std::string name );
				XMLNode ( CrissCross::Text::XML::XMLDocument *_ownerDocument, std::string _name, std::string _value );
				~XMLNode();

				nodeType		getNodeType (); //
				std::string		getNodeName (); //
				std::string		getNodeValue (); //
				void			setNodeValue ( std::string _nodeValue ); //
				bool			hasChildNodes (); //
				CrissCross::Data::LList<XMLAttribute *> *getAttributes (); //
				CrissCross::Text::XML::XMLDocument		*getOwnerDocument ();

				XMLNode			*getFirstChild();
				XMLNode			*getLastChild();
				XMLNode			*getNextSibling();
				XMLNode			*getPreviousSibling();
				XMLNode			*getParentNode();
				CrissCross::Data::LList<XMLNode *> *getChildNodes();

				XMLNode			*removeChild ( XMLNode *_oldChild );
				XMLNode			*insertBefore ( XMLNode *_newChild, XMLNode *_refChild );
				XMLNode			*appendChild ( XMLNode *_newChild );
				XMLNode			*replaceChild ( XMLNode *_newChild, XMLNode * _oldChild );
				XMLNode			*cloneNode ( bool _deep );
			};
		}
	}
}

#endif
