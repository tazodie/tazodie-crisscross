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

#ifndef __included_cc_xmlnodelist_h
#define __included_cc_xmlnodelist_h

#include <crisscross/llist.h>

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLNodeList
			{
			protected:
				CrissCross::Data::LList<XMLNode *>						m_nodeList;

			public:
				XMLNodeList ();
				~XMLNodeList ();

				XMLNode						*item ( size_t _index );
				size_t						length ();

				friend class XMLNode;
			};
		}
	}
}

#endif
