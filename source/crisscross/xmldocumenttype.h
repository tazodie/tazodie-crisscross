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

#ifndef __included_xmldocumenttype_h
#define __included_xmldocumenttype_h

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLDocumentType : public XMLNode
			{
			protected:
				std::string		m_name;

			public:
				XMLDocumentType ();
				~XMLDocumentType ();
			};
		}
	}
}

#endif
