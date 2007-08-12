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

#include <crisscross/xml.h>

using namespace CrissCross;
using namespace CrissCross::Data;
using namespace CrissCross::Text::XML;
using namespace CrissCross::IO;

XMLNamedNodeMap::XMLNamedNodeMap ()
{
}

XMLNamedNodeMap::~XMLNamedNodeMap ()
{
}

XMLNode *
XMLNamedNodeMap::getNamedItem ( std::string _name )
{
	return m_nodeMap.find ( _name );
}

XMLNode *
XMLNamedNodeMap::setNamedItem ( XMLNode *_node )
{
	m_nodeMap.insert ( _node->getNodeName(), _node );
	return _node;
}

XMLNode *
XMLNamedNodeMap::item ( size_t _index )
{
	return m_nodeList.get ( _index );
}

XMLNode *
XMLNamedNodeMap::removeNamedItem ( std::string _name )
{
	XMLNode *retval = getNamedItem ( _name );
	m_nodeMap.erase ( _name );
	return retval;
}

size_t
XMLNamedNodeMap::length ()
{
	return m_nodeList.size();
}
