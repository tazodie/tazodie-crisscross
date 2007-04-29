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
				DataBuffer ( const char *_initialString );
				DataBuffer ( const char *_initialData, size_t _size );
				DataBuffer ( const DataBuffer &_initialData );
				virtual ~DataBuffer ();
				
				//! Resize the data buffer while preserving the contents.
				virtual void resize ( size_t _capacity );

				//! Resize the data buffer, dropping existing contents.
				virtual void setSize ( size_t _capacity );

				//! Set the data buffer contents.
				virtual int setData ( const char *_newData, size_t _size );

				//! Set the data buffer contents.
				virtual int setDataString ( const char *_newData );
				
				virtual const char *getData() const;
				virtual size_t getSize() const;

				DataBuffer &operator=  ( const DataBuffer &_buffer );

				bool operator>  ( const DataBuffer &_buffer ) const;
				bool operator>= ( const DataBuffer &_buffer ) const;
				
				bool operator<  ( const DataBuffer &_buffer ) const;
				bool operator<= ( const DataBuffer &_buffer ) const;
				
				bool operator== ( const DataBuffer &_buffer ) const;
				bool operator!= ( const DataBuffer &_buffer ) const;

				inline bool operator! () const { return ( m_buffer == NULL ); };
				
				inline char &operator[] ( unsigned int index ) {
						static char c = '\x0';
						if ( m_buffer && m_size > index )
							return m_buffer[index];
						else
							return c;
				};
				inline const char &operator[] ( unsigned int index ) const {
						static const char c = '\x0';
						if ( m_buffer && m_size > index )
							return m_buffer[index];
						else
							return c;
				};
		};
	}
}
#endif
