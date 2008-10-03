/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_hashtable_h
#error "This file shouldn't be compiled directly."
#endif

#include <crisscross/stopwatch.h>

namespace CrissCross
{
	namespace Data
	{
		template <class T>
		HashTable<T>::HashTable(size_t _initialSize)
		{
			if (_initialSize < 25) _initialSize = 25;

			m_size = _initialSize;
			m_used = 0;
			m_array = new tree_t *[_initialSize];
			memset(m_array, 0, sizeof(tree_t *) * _initialSize);

			m_insertions = m_collisions = m_searches = m_hits = 0;
		}

		template <class T>
		HashTable<T>::~HashTable()
		{
			for (size_t i = 0; i < m_size; i++) {
				delete m_array[i];
				m_array[i] = NULL;
			}
			delete [] m_array;
			m_array = NULL;

			m_size = 0;
		}

		template <class T>
		size_t HashTable<T>::hash(const char * const &_key, size_t _length) const
		{
			CoreAssert(_key);
			size_t hash = 0;
			size_t i;
			for (i = 0; i < _length; i++) {
				hash += _key[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}

			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}

		template <class T>
		void HashTable<T>::grow()
		{
			/*
			size_t  oldSize = m_size;
			m_size *= HASH_TABLE_SIZE_MAGNITUDE;
			m_used = 0;

			T      *oldArray = m_array;
			m_array = new T[m_size ];
			memset(m_array, 0, sizeof(T) * m_size);

			char * *oldKeys = m_keys;
			m_keys = new char *[m_size];
			memset(m_keys, 0, sizeof(char *) * m_size);

			for (size_t i = 0; i < oldSize; i++) {
				if (oldKeys[i])	{
					insert(oldKeys[i], oldArray[i]);
					delete [] oldKeys[i];
				}
			}

			delete [] oldArray;
			delete [] oldKeys;
			*/
		}

		template <class T>
		size_t HashTable<T>::findIndex(const char * const &_key) const
		{
			size_t khash = hash(_key, strlen(_key));
			size_t pos = khash % m_size;
			return pos;
		}

		template <class T>
		T HashTable<T>::find(const char * const & _key) const
		{
			static T null(0);
			size_t   index = findIndex(_key);
			if (!m_array[index]) return null;
			return m_array[index]->find(_key);
		}

		template <class T>
		bool HashTable<T>::exists(const char * const & _key) const
		{
			size_t   index = findIndex(_key);
			if (!m_array[index]) return false;
			return m_array[index]->exists(_key);
		}

		template <class T>
		bool HashTable<T>::find(const char * const &_key, T &_data) const
		{
			size_t index = findIndex(_key);
			if (!m_array[index]) return false;
			return m_array[index]->find(_key, _data);
		}

		template <class T>
		void HashTable<T>::print_statistics() const
		{
			double hitPercentage = ((double)m_hits / (double)m_searches) * 100.0,
			       collisionPercentage = ((double)m_collisions / (double)m_insertions) * 100.0,
			       usagePercentage = ((double)m_used / (double)m_size) * 100.0;
			if (m_searches == 0) hitPercentage = 0.0;

			if (m_insertions == 0) collisionPercentage = 0.0;

			printf("\n");
			printf("HASH TABLE STATISTICS:\n\n");
			printf("SIZE: %lu (%luKB)\n", m_size, ((m_size * sizeof(T)) + (m_size * sizeof(char *))) / 1024);
			printf("USED: %lu (%0.2f%%)\n", m_used, usagePercentage);
			printf("SEARCH STATISTICS:\n");
			printf("\tSEARCHES: %lu\n", m_searches);
			printf("\tHITS: %lu (%0.2f%%)\n", m_hits, hitPercentage);
			printf("INSERTION STATISTICS:\n");
			printf("\tINSERTIONS: %lu\n", m_insertions);
			printf("\tCOLLISIONS: %lu (%0.2f%%)\n", m_collisions, collisionPercentage);
			double q1 = hitPercentage,
			       q2 = (100.0 - collisionPercentage),
			       q3 = (usagePercentage * (100.0 / HASH_TABLE_FILL_THRESHHOLD));
			printf("*** OVERALL QUALITY ESTIMATION : %0.2f%% ( (%0.2f%% + %0.2f%% + %0.2f%%) / 3.0 ) ***\n",
			       (q1 + q2 + q3) / 3.0, q1, q2, q3);
			printf("\n");

			m_hits = m_searches = m_collisions = m_insertions = 0;
		}

		template <class T>
		bool HashTable<T>::erase(const char * const &_key)
		{
			size_t index = findIndex(_key);
			if (!m_array[index]) return false;
			return m_array[index]->erase(_key);
		}

		template <class T>
		size_t HashTable<T>::mem_usage() const
		{
			/*
			size_t ret = sizeof(*this);
			ret += m_size * sizeof(T);
			ret += m_size * sizeof(char *);
			return ret;
			*/
			return 0;
		}

		template <class T>
		bool HashTable<T>::insert(const char * const &_key, T const &_data)
		{
			size_t khash = hash(_key, strlen(_key));
			size_t pos = khash % m_size;

			if (!m_array[pos])
				m_array[pos] = new tree_t();

			CoreAssert(m_array[pos]);

			return m_array[pos]->insert(_key, _data);
		}
	}
}
