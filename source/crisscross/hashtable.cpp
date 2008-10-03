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

			m_searches = m_hits = 0;
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
		size_t HashTable<T>::findIndex(const char * const &_key) const
		{
			size_t khash = hash(_key, strlen(_key));
			size_t pos = khash % m_size;
			return pos;
		}

		template <class T>
		T HashTable<T>::find(const char * const & _key) const
		{
			m_searches++;

			static T null(0);
			size_t   index = findIndex(_key);
			if (!m_array[index]) return null;
			T ret;
			if (m_array[index]->find(_key, ret)) {
				m_hits++;
				return ret;
			} else {
				return null;
			}
		}

		template <class T>
		bool HashTable<T>::exists(const char * const & _key) const
		{
			m_searches++;

			size_t   index = findIndex(_key);
			if (!m_array[index]) return false;
			if (m_array[index]->exists(_key)) {
				m_hits++;
				return true;
			} else {
				return false;
			}
		}

		template <class T>
		bool HashTable<T>::find(const char * const &_key, T &_data) const
		{
			m_searches++;

			size_t index = findIndex(_key);
			if (!m_array[index]) return false;
			if (m_array[index]->find(_key, _data)) {
				m_hits++;
				return true;
			} else {
				return false;
			}
		}

		template <class T>
		void HashTable<T>::print_statistics() const
		{
			double hitPercentage = ((double)m_hits / (double)m_searches) * 100.0;

			if (m_searches == 0) hitPercentage = 0.0;

			printf("\n");
			printf("HASH TABLE STATISTICS:\n\n");
			printf("SIZE: %lu (%luKB)\n", m_used, mem_usage() / 1024);
			printf("SEARCH STATISTICS:\n");
			printf("\tSEARCHES: %lu\n", m_searches);
			printf("\tHITS: %lu (%0.2f%%)\n", m_hits, hitPercentage);
			printf("INSERTION STATISTICS:\n");
			unsigned long min = (unsigned long)-1,
				max = 0,
				mean = 0;
			for (unsigned long i = 0; i < m_size; i++) {
				if (!m_array[i]) {
					min = 0;
					continue;
				}
				unsigned long used = m_array[i]->size();
				min = cc_min(min, used);
				max = cc_max(max, used);
				mean += used;
			}
			mean /= m_size;
			printf("\tAVERAGE FILL: %lu (HEIGHT %lu)\n", mean, (unsigned long)(log((float)mean) / log(2.0f)));
			printf("\tMINIMUM FILL: %lu (HEIGHT %lu)\n", min,  (unsigned long)(log((float)min)  / log(2.0f)));
			printf("\tMAXIMUM FILL: %lu (HEIGHT %lu)\n", max,  (unsigned long)(log((float)max)  / log(2.0f)));
			//printf("\tINSERTIONS: %lu\n", m_insertions);
			//printf("\tCOLLISIONS: %lu (%0.2f%%)\n", m_collisions, collisionPercentage);
			/*
			double q1 = hitPercentage,
			       q2 = (100.0 - collisionPercentage),
			       q3 = (usagePercentage * (100.0 / HASH_TABLE_FILL_THRESHHOLD));
			printf("*** OVERALL QUALITY ESTIMATION : %0.2f%% ( (%0.2f%% + %0.2f%% + %0.2f%%) / 3.0 ) ***\n",
			       (q1 + q2 + q3) / 3.0, q1, q2, q3);
			*/
			printf("\n");

			m_hits = m_searches = 0;
		}

		template <class T>
		bool HashTable<T>::erase(const char * const &_key)
		{
			size_t index = findIndex(_key);
			if (!m_array[index]) return false;
			if (m_array[index]->erase(_key)) {
				m_used--;
				return true;
			} else {
				return false;
			}
		}

		template <class T>
		size_t HashTable<T>::mem_usage() const
		{
			size_t ret = sizeof(*this);
			for (unsigned int i = 0; i < m_size; i++)
				if (m_array[i])
					ret += m_array[i]->mem_usage();
			return ret;
		}

		template <class T>
		bool HashTable<T>::insert(const char * const &_key, T const &_data)
		{
			size_t khash = hash(_key, strlen(_key));
			size_t pos = khash % m_size;

			if (!m_array[pos])
				m_array[pos] = new tree_t();

			CoreAssert(m_array[pos]);

			if (m_array[pos]->insert(_key, _data)) {
				m_used++;
				return true;
			} else {
				return false;
			}
		}
	}
}
