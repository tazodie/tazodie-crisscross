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

#include <crisscross/encoding.h>
#include <crisscross/xmlnode.h>
#include <crisscross/xmldocument.h>

using namespace CrissCross;
using namespace CrissCross::Data;
using namespace CrissCross::Text;
using namespace CrissCross::Text::Encoding;
using namespace CrissCross::Text::XML;
using namespace CrissCross::IO;

XMLNode::XMLNode ( CrissCross::Text::XML::XMLDocument *_ownerDocument )
{
	m_ownerDocument = _ownerDocument;
	m_nodeType = NULL_NODE;
}

XMLNode::~XMLNode ()
{
}

nodeType XMLNode::getNodeType ()
{
	return m_nodeType;
}

std::string XMLNode::getNodeName ()
{
	return m_nodeName;
}

std::string XMLNode::getNodeValue ()
{
	return m_nodeValue;
}

void XMLNode::setNodeValue ( std::string _nodeValue )
{
	m_nodeValue = _nodeValue;
}

bool XMLNode::hasChildNodes ()
{
	return m_childNodes.size() > 0;
}

LList<XMLAttribute *> *XMLNode::getAttributes ()
{
	return &m_attributes;
}

CrissCross::Text::XML::XMLDocument *XMLNode::getOwnerDocument ()
{
	return m_ownerDocument;
}

XMLNode *XMLNode::getFirstChild ()
{
	CoreAssert ( m_childNodes.size() > 0 );
	return m_childNodes.get(0);
}

XMLNode *XMLNode::getLastChild ()
{
	CoreAssert ( m_childNodes.size() > 0 );
	return m_childNodes.get(m_childNodes.size() - 1);
}

XMLNode *XMLNode::getNextSibling ()
{
	CoreAssert ( m_parentNode );
	LList<XMLNode *> *siblings = m_parentNode->getChildNodes();
	return siblings->get ( siblings->find ( this ) + 1 );
}

XMLNode *XMLNode::getPreviousSibling ()
{
	CoreAssert ( m_parentNode );
	LList<XMLNode *> *siblings = m_parentNode->getChildNodes();
	return siblings->get ( siblings->find ( this ) - 1 );
}

XMLNode *XMLNode::getParentNode ()
{
	return m_parentNode;
}

LList<XMLNode *> *XMLNode::getChildNodes ()
{
	return &m_childNodes;
}

XMLNode *XMLNode::removeChild ( XMLNode *_oldChild )
{
	m_childNodes.remove ( m_childNodes.find ( _oldChild ) );
	return _oldChild;
}

XMLNode *XMLNode::insertBefore ( XMLNode *_newChild, XMLNode *_refChild )
{
	m_childNodes.insert_at ( _newChild, m_childNodes.find ( _refChild ) );
	return _newChild;
}

XMLNode *XMLNode::replaceChild ( XMLNode *_newChild, XMLNode * _oldChild )
{
	m_childNodes.change ( _newChild, m_childNodes.find ( _oldChild ) );
	return _newChild;
}

XMLNode *XMLNode::appendChild ( XMLNode *_newChild )
{
	m_childNodes.insert ( _newChild );
	return _newChild;
}
