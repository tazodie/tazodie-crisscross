/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_core_databuffer_h
#define __included_core_databuffer_h

namespace CrissCross
{
	namespace Data
	{
		class DataBuffer
		{
			protected:
				char *m_buffer;
				size_t m_size;
				
			public:
				DataBuffer ();
				DataBuffer ( size_t _initialCapacity );
				DataBuffer ( const char *_initialData );
				DataBuffer ( const DataBuffer &_initialData );
				virtual ~DataBuffer ();
				
				virtual void resize ( size_t _capacity );
				virtual void setSize ( size_t _capacity );
				virtual void setData ( const char *_newData );
				
				virtual const char *getData() const;
				virtual size_t getSize() const;
				
				bool operator>  ( const DataBuffer &_buffer ) const;
				bool operator>= ( const DataBuffer &_buffer ) const;
				
				bool operator<  ( const DataBuffer &_buffer ) const;
				bool operator<= ( const DataBuffer &_buffer ) const;
				
				bool operator== ( const DataBuffer &_buffer ) const;
				bool operator!= ( const DataBuffer &_buffer ) const;
		};
	}
}
#endif
