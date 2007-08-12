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

using namespace CrissCross::Text::XML;

XMLNodeList::XMLNodeList ()
{
}

XMLNodeList::~XMLNodeList ()
{
}

XMLNode *
XMLNodeList::item ( size_t _index )
{
	return m_nodeList.get ( _index );
}

size_t
XMLNodeList::length ()
{
	return m_nodeList.size();
}
