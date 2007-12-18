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
			
			// Mutable because splaying is an operation which changes
			// the structure of the tree.
			mutable SplayNode<Key,Data> *root;

			void printTree( SplayNode<Key,Data> *t ) const;

			// Tree manipulations
			void rotateWithLeftChild( SplayNode<Key,Data> * & k2 ) const;
			void rotateWithRightChild( SplayNode<Key,Data> * & k1 ) const;
			void splay ( Key const &key, SplayNode<Key,Data> * & t ) const;
			
			SplayNode<Key,Data> *findNode ( Key const &key ) const;

			size_t m_size;

            void RecursiveConvertIndexToDArray ( DArray <Key> *_darray, SplayNode<Key,Data> *_btree ) const;
            void RecursiveConvertToDArray ( DArray <Data> *_darray, SplayNode<Key,Data> *_btree ) const;

			void findRecursive ( DArray<Data> *_array, Key const &_key, SplayNode<Key,Data> *_node ) const;

			bool erase ( Key const &key, Data const &rec, SplayNode<Key,Data> *curnode );

			bool killNode ( SplayNode<Key,Data> * z );

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
			bool exists ( Key const &_key ) const;

            //! Change the data at the given node.
			/*!
				\param _key The key of the node to be modified.
				\param _rec The data to insert.
				\return True on success, false on failure.
			 */
            bool replace ( Key const &_key, Data const &_rec );

            //! Finds a node in the tree and returns the data at that node.
			/*!
				\param _key The key of the node to find.
				\param _data On return, will contain the data at the node. If not found, _data does not change.
				\return True on success, false on failure.
			 */
			bool find ( Key const &_key, Data &_data ) const;

            //! Finds a node in the tree and returns the data at that node.
			/*!
				\param _key The key of the node to find.
				\return The data at the node. NULL if not found.
			 */
			_CC_DEPRECATE_FUNCTION_N Data find ( Key const &key ) const;

            //! Finds all instances of the specified key in the tree.
			/*!
				\param _key The key of the node to find.
				\return A DArray containing the data with key _key. MUST be deleted when done!
			 */
			DArray<Data> *findAll ( Key const &_key ) const;

            //! Deletes a node from the tree, specified by the node's key.
			/*!
				This won't free the memory occupied by the data, so the data must be freed
				seperately.
				\param _key The key of the node to delete.
				\return True on success, false on failure
			 */
			bool erase ( Key const &key );

            //! Deletes a node from the tree, specified by the node's key and data.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \param _data The data of the node to delete.
                \return True on success, false on failure.
             */
			bool erase ( Key const &_key, Data const &_data );

            //! Indicates the size of the tree.
			/*!
				\return Size of the tree.
			 */
			inline size_t size () const { return m_size; };

            //! Converts the tree data into a linearized DArray.
			/*!
				\return A DArray containing the data of the tree.
			 */
            DArray <Data> *ConvertToDArray () const;

            //! Converts the tree keys into a linearized DArray.
			/*!
				\return A DArray containing the keys in the tree.
			 */
            DArray <Key>  *ConvertIndexToDArray () const;

		};
	}
}

#include <crisscross/splaytree.cpp>

#endif
