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

#ifndef __included_cc_xmlnode_h
#define __included_cc_xmlnode_h

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLNode
			{
			protected:
				XMLNodeType		m_nodeType;
				XMLDocument		*m_ownerDocument;

				std::string		m_nodeName;
				std::string		m_nodeValue;

				XMLNode			*m_parentNode;
				XMLNodeList		m_childNodes;
				XMLNamedNodeMap	m_attributes;

			public:
				//XMLNode ();
				XMLNode ( CrissCross::Text::XML::XMLDocument *_ownerDocument,
						  std::string _name = std::string(""), std::string _value = std::string("") );
				~XMLNode();

				XMLNodeType		getNodeType ();
				std::string		getNodeName ();
				std::string		getNodeValue ();
				void			setNodeValue ( std::string _nodeValue );
				void			setNodeName ( std::string _nodeName );
				bool			hasChildNodes ();
				XMLNamedNodeMap *getAttributes ();
				CrissCross::Text::XML::XMLDocument *getOwnerDocument ();

				XMLNode			*getFirstChild();
				XMLNode			*getLastChild();
				XMLNode			*getNextSibling();
				XMLNode			*getPreviousSibling();
				XMLNode			*getParentNode();
				XMLNodeList		*getChildNodes();

				XMLNode			*removeChild ( XMLNode *_oldChild );
				XMLNode			*insertBefore ( XMLNode *_newChild, XMLNode *_refChild );
				XMLNode			*appendChild ( XMLNode *_newChild );
				XMLNode			*replaceChild ( XMLNode *_newChild, XMLNode * _oldChild );
				//XMLNode			*cloneNode ( bool _deep );
			};
		}
	}
}

#endif
