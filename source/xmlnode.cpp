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

std::string XMLNode::getNodeName ()
{
	return m_nodeName;
}

std::string XMLNode::getNodeValue ()
{
	return m_nodeValue;
}

nodeType XMLNode::getNodeType ()
{
	return m_nodeType;
}

void XMLNode::setNodeValue ( std::string _nodeValue )
{
	m_nodeValue = _nodeValue;
}

bool XMLNode::hasChildNodes ()
{
	return m_childNodes.size() > 0;
}

LList<XMLNode *> *XMLNode::getChildNodes ()
{
	return &m_childNodes;
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

XMLNode *XMLNode::getPreviousSibling ()
{
	CoreAssert ( m_parentNode );
	LList<XMLNode *> *siblings = m_parentNode->getChildNodes();
	return siblings->get ( siblings->find ( this ) - 1 );
}

XMLNode *XMLNode::getNextSibling ()
{
	CoreAssert ( m_parentNode );
	LList<XMLNode *> *siblings = m_parentNode->getChildNodes();
	return siblings->get ( siblings->find ( this ) + 1 );
}

LList<XMLAttribute *> *XMLNode::getAttributes ()
{
	return &m_attributes;
}

CrissCross::Text::XML::XMLDocument *XMLNode::getOwnerDocument ()
{
	return m_ownerDocument;
}