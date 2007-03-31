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

#include <crisscross/universal_include.h>
#include <crisscross/core_databuffer.h>

#ifndef stricmp
#define stricmp strcasecmp
#endif

using namespace CrissCross::Data;

DataBuffer::DataBuffer()
	: m_buffer ( NULL ), m_size ( -1 )
{
}

DataBuffer::DataBuffer ( size_t _initialCapacity )
	: m_buffer ( NULL ), m_size ( -1 )
{
	setSize ( _initialCapacity );
}

DataBuffer::DataBuffer ( const char *_initialData )
	: m_buffer ( NULL ), m_size ( -1 )
{
	setData ( _initialData );
}

DataBuffer::DataBuffer ( const DataBuffer &_initialData )
	: m_buffer ( NULL ), m_size ( -1 )
{
	setData ( _initialData.getData() );
}

DataBuffer::~DataBuffer ()
{
	if ( m_buffer )
	{
		free ( m_buffer );
		m_buffer = NULL;
	}
	m_size = -1;
}

void DataBuffer::resize ( size_t _capacity )
{
	if ( !m_buffer )
	{
		setSize ( _capacity );
		return;
	}
	
	char *newBuffer = new char[_capacity];
	memcpy ( newBuffer, m_buffer, m_size );
	free ( m_buffer );
	m_buffer = newBuffer;
	m_size = _capacity;
	
}

void DataBuffer::setSize ( size_t _capacity )
{
	if ( m_buffer ) free ( m_buffer );

	m_size = _capacity;
	m_buffer = (char *)malloc ( m_size );
	memset ( m_buffer, 0, m_size );
}

void DataBuffer::setData ( const char *_data )
{
	if ( m_buffer ) free ( m_buffer );

	m_size = strlen ( _data );
	m_buffer = (char *)malloc ( m_size );
	strcpy ( m_buffer, _data );
}

size_t DataBuffer::getSize () const
{
	return m_size;
}

const char *DataBuffer::getData () const
{
	return m_buffer;
}

bool DataBuffer::operator> ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) > 0;
}

bool DataBuffer::operator>= ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) >= 0;
}

bool DataBuffer::operator< ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) < 0;
}

bool DataBuffer::operator<= ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) <= 0;
}

bool DataBuffer::operator== ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) == 0;
}

bool DataBuffer::operator!= ( const DataBuffer &_buffer ) const
{
	return stricmp ( m_buffer, _buffer.getData() ) != 0;
}
