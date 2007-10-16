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

#ifndef __included_cc_hashtable_h
#define __included_cc_hashtable_h

namespace CrissCross
{
	namespace Data
	{
		template <class T>
		class HashTable
		{
		protected:
			T			*m_array;
			char		**m_keys;
			size_t		m_size;
			size_t		m_used;
			size_t		m_searches;
			size_t		m_hits;

			size_t		m_insertions;
			size_t		m_collisions;

			size_t hash ( const char *_key, size_t _length );
			void grow ();

			size_t findIndex ( const char * const &_key );

		public:
			HashTable ( size_t _initialSize = 500 );
			virtual ~HashTable ();

			int insert ( const char * const &_key, T const &_data );
			T const &find ( const char * const &_key );
			int remove ( const char * const &_key );

			void print_statistics ();

		};
	}
}

#include <crisscross/hashtable.cpp>

#endif
