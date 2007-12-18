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

#ifndef __included_cc_splaytree_h
#define __included_cc_splaytree_h

#include <crisscross/deprecate.h>
#include <crisscross/node.h>

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
		class SplayTree
		{
		private:

			//! Private copy constructor.
			/*!
				If your code needs to invoke the copy constructor, you've probably written
				the code wrong. A tree copy is generally unnecessary, and in cases that it
				is, it can be achieved by other means.
			 */
			SplayTree ( const SplayTree<Key,Data> & );

			//! Private assignment operator.
			/*!
				If your code needs to invoke the assignment operator, you've probably written
				the code wrong. A tree copy is generally unnecessary, and in cases that it
				is, it can be achieved by other means.
			 */
			SplayTree<Key,Data> &operator = ( const SplayTree<Key,Data> & );
			
			BinaryNode<Key,Data> *root;

			void printTree( BinaryNode<Key,Data> *t ) const;

			// Tree manipulations
			void rotateWithLeftChild( BinaryNode<Key,Data> * & k2 ) const;
			void rotateWithRightChild( BinaryNode<Key,Data> * & k1 ) const;
			void splay( Key const &key, BinaryNode<Key,Data> * & t ) const;
			
			BinaryNode<Key,Data> *findNode ( Key const &key );

			size_t m_size;

		public:

			//! The default constructor.
			SplayTree ();

			//! The destructor.
			~SplayTree ();

			//! Empties the entire tree.
			void empty ();

            //! Inserts data into the tree.
			/*!
				\param _key The key of the data.
				\param _rec The data to insert.
				\return True on success, false on failure.
			 */
			bool insert ( Key const &key, Data const &x );

            //! Tests whether a key is in the tree or not.
			/*!
				\param _key The key of the node to find.
				\return True if the key is in the tree, false if not.
			 */
			bool exists ( Key const &_key );

            //! Finds a node in the tree and returns the data at that node.
			/*!
				\param _key The key of the node to find.
				\param _data On return, will contain the data at the node. If not found, _data does not change.
				\return True on success, false on failure.
			 */
			bool find ( Key const &_key, Data &_data );

            //! Finds a node in the tree and returns the data at that node.
			/*!
				\param _key The key of the node to find.
				\return The data at the node. NULL if not found.
			 */
			_CC_DEPRECATE_FUNCTION_N Data find ( Key const &key );

            //! Deletes a node from the tree, specified by the node's key.
			/*!
				This won't free the memory occupied by the data, so the data must be freed
				seperately.
				\param _key The key of the node to delete.
				\return True on success, false on failure
			 */
			bool erase ( Key const &key );

            //! Indicates the size of the tree.
			/*!
				\return Size of the tree.
			 */
			size_t size() const;

		};
	}
}

#include <crisscross/splaytree.cpp>

#endif
