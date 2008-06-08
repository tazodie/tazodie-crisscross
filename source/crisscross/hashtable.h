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
#define __included_cc_hashtable_h

namespace CrissCross
{
	namespace Data
	{
		//! A simple HashTable.
		/*!
		 *      Only accepts C-style strings as keys.
		 * \warning This class is currently not recommended for general use. It hasn't been fully
		 *              tested yet and is only under consideration for being a future feature.
		 */
		template <class T>
		class HashTable
		{
			private:
				//! Private copy constructor.
				/*!
				 *      Not yet written, so declared private for now to prevent an auto-generated
				 *      one from performing an unexpected operation.
				 */
				HashTable ( const HashTable<T> & );

				//! Private assignment operator.
				/*!
				 *      Not yet written, so declared private for now to prevent an auto-generated
				 *      one from performing an unexpected operation.
				 */
				HashTable<T> &operator = ( const HashTable<T> & );

			protected:
				T *m_array;
				char **m_keys;
				size_t m_size;
				size_t m_used;
				mutable size_t m_searches;
				mutable size_t m_hits;

				mutable size_t m_insertions;
				mutable size_t m_collisions;

				size_t hash ( const char * const &_key, size_t _length ) const;

				size_t findIndex ( const char * const &_key ) const;

			public:
				//! The constructor.
				/*!
				 * \param _initialSize The initial size of the hash table. Minimum is 500.
				 */
				HashTable ( size_t _initialSize = 500 );
				~HashTable ();

				//! Inserts data into the table.
				/*!
				 * \param _key The key of the data.
				 * \param _data The data to insert.
				 * \return True on success, false on failure.
				 */
				bool insert ( const char * const &_key, T const &_data );

				//! Finds a node in the table and copies the data from that node to a specified location.
				/*!
				 * \param _key The key of the node to find.
				 * \param _data On return, will contain the data at the node. If not found, _data does not change.
				 * \return True on success, false on failure.
				 */
				bool find ( const char * const &_key, T &_data ) const;

				//! Finds a node in the table and returns the data at that node.
				/*!
				 * \param _key The key of the item to find.
				 * \return The data at the node. NULL if not found.
				 * \deprecated The return value of this function could be unpredictable if the
				 *                          contents of the table was anything but pointers or integers.
				 * \sa find
				 */
				T const &find ( const char * const & _key ) const;

				//! Deletes a node from the table, specified by the node's key.
				/*!
				 * \warning This won't free the memory occupied by the data, so the data must be freed separately.
				 * \param _key The key of the node to delete.
				 * \return True on success, false on failure
				 */
				bool erase ( const char * const &_key );

				//! Indicates the size of the table.
				/*!
				 * \return Size of the table.
				 */
				inline size_t size () const
				{
					return m_size;
				};

				//! Returns the memory usage of the table.
				/*!
				 * \return Memory usage in bytes.
				 */
				size_t mem_usage () const;

				//! Forces the table to increase in size.
				/*!
				 *  It's highly recommended that you let the hash table manage this on its own and that
				 *  you don't call this function unless you know what the implications are.
				 */
				void grow ();

				void print_statistics () const;
		};
	}
}

#include <crisscross/hashtable.cpp>

#endif
