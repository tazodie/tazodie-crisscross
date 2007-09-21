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

#ifndef __included_cc_xml_h
#define __included_cc_xml_h

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLNode;
			class XMLNodeList;
			class XMLNamedNodeMap;
			class XMLAttribute;
			class XMLElement;
			class XMLDocument;
			class XMLDocumentType;
			class XMLParser;

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
			} XMLNodeType;
		}
	}
}

#include <crisscross/llist.h>
#include <crisscross/rbtree.h>

#include <crisscross/encoding.h>

#include <crisscross/xmlnodelist.h>
#include <crisscross/xmlnamednodemap.h>
#include <crisscross/xmlnode.h>
#include <crisscross/xmlattribute.h>
#include <crisscross/xmlelement.h>
#include <crisscross/xmldocument.h>
#include <crisscross/xmldocumenttype.h>
#include <crisscross/xmlparser.h>

#endif
