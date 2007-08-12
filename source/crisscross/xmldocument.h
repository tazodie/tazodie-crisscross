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

#ifndef __included_xmldocument_h
#define __included_xmldocument_h

namespace CrissCross
{
	namespace Text
	{
		namespace XML
		{
			class XMLDocument : public XMLNode
			{
			protected:
				XMLElement *m_rootElement;
				CrissCross::Text::Encoding::charEncoding m_xmlEncoding;

			public:
				XMLDocument ();
				~XMLDocument();

				void setEncoding ( CrissCross::Text::Encoding::charEncoding _encoding );
				CrissCross::Text::Encoding::charEncoding getEncoding ();

#if 0
				XMLDocumentType						getDoctype();
				XMLDOMImplementation				getImplementation();
#endif
				XMLElement							*getDocumentElement();
#if 0
				CrissCross::Data::LList<XMLNode *>	*getElementsByTagName ( std::string _tagName );

				static XMLElement					*createElement ( std::string _tagName );
				static XMLDocumentFragment			*createDocumentFragment ();
				static XMLText						*createTextNode ( std::string _data );
				static XMLComment					*createComment ( std::string _data );
				static XMLCDATASection				*createCDATASection ( std::string _data );
				static XMLProcessingInstruction		*createProcessingInstruction ( std::string _target, std::string _data );
				static XMLAttribute					*createAttribute ( std::string _data;
				static XMLEntityReference			*createEntityReference ( std::string _name );
#endif

			};
		}
	}
}

#endif
