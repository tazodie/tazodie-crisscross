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
#   error "This file shouldn't be compiled directly."
#endif

#include <stdlib.h>

#include <crisscross/internal_mem.h>

namespace CrissCross
{
	namespace Data
	{
		template <class Key, class Data>
		SplayTree<Key,Data>::SplayTree ()
		{
			root = NULL;
			m_size = 0;
		}

		template <class Key, class Data>
		SplayTree<Key,Data>::~SplayTree ( )
		{
			delete root;
			root = NULL;
		}

		template <class Key, class Data>
		bool SplayTree<Key,Data>::insert ( Key const &key, Data const &x )
		{
			static BinaryNode<Key,Data> *newNode = NULL;

			if ( newNode == NULL )
				newNode = new BinaryNode<Key,Data>;
			else
				Dealloc ( newNode->id );
			newNode->id = Duplicate ( key );
			newNode->data = x;

			if ( root == NULL )
			{
				newNode->left = newNode->right = NULL;
				root = newNode;
			}
			else
			{
				splay( key, root );
				if ( Compare ( key, root->id ) < 0 )
				{
					newNode->left = root->left;
					newNode->right = root;
					root->left = NULL;
					root = newNode;
				}
				else
				if ( Compare ( root->id, key ) < 0 )
				{
					newNode->right = root->right;
					newNode->left = root;
					root->right = NULL;
					root = newNode;
				}
				else
					return false;
			}
			m_size++;
			newNode = NULL;   // So next insert will call new
			return true;
		}

		template <class Key, class Data>
		bool SplayTree<Key,Data>::erase ( Key const &key )
		{
			BinaryNode<Key,Data> *newTree;

			// If key is found, it will be at the root
			splay( key, root );
			if ( Compare ( root->id, key ) != 0 )
				return false;

			if ( root == NULL )
				return false;

			if ( root->left == NULL )
				newTree = root->right;
			else
			{
				  // Find the maximum in the left subtree
				  // Splay it to the root; and then attach right child
				newTree = root->left;
				splay( key, newTree );
				newTree->right = root->right;
			}

			m_size--;

			root->left = NULL;
			root->right = NULL;
			delete root;

			root = newTree;

			return true;
		}

		template <class Key, class Data>
		bool SplayTree<Key,Data>::exists ( Key const &key )
		{
			splay( key, root );

			if ( root == NULL || Compare ( root->id, key ) != 0 )
				return false;

			return true;
		}

		template <class Key, class Data>
		Data SplayTree<Key,Data>::find( Key const &key )
		{
			splay( key, root );

			if ( root == NULL || Compare ( root->id, key ) != 0 )
				return Data(NULL);

			return root->data;
		}

		template <class Key, class Data>
		bool SplayTree<Key,Data>::find( Key const &key, Data &data )
		{
			splay( key, root );

			if ( root == NULL || Compare ( root->id, key ) != 0 )
				return false;

			data = root->data;
			return true;
		}

		template <class Key, class Data>
		BinaryNode<Key,Data> *SplayTree<Key,Data>::findNode( Key const &key )
		{
			splay( key, root );

			if ( root == NULL || Compare ( root->id, key ) != 0 )
				return NULL;

			return root;
		}

		template <class Key, class Data>
		void SplayTree<Key,Data>::empty ()
		{
			delete root;
			root = NULL;
			m_size = 0;
		}

		template <class Key, class Data>
		size_t SplayTree<Key,Data>::size() const
		{
			return m_size;
		}

		template <class Key, class Data>
		void SplayTree<Key,Data>::splay( Key const &key, BinaryNode<Key,Data> * & t ) const
		{
			BinaryNode<Key,Data> *leftTreeMax, *rightTreeMin;
			static BinaryNode<Key,Data> header;

			header.left = header.right = NULL;
			leftTreeMax = rightTreeMin = &header;

			for( ; ; )
				if ( Compare ( key, t->id ) < 0 )
				{
					if ( t->left == NULL )
						break;
					if ( Compare ( key, t->left->id ) < 0 )
						rotateWithLeftChild( t );
					  // Link Right
					rightTreeMin->left = t;
					rightTreeMin = t;
					t = t->left;
				}
				else if ( Compare ( t->id, key ) < 0 )
				{
					if ( t->right == NULL )
						break;
					if ( Compare ( t->right->id, key ) < 0 )
						rotateWithRightChild( t );
					  // Link Left
					leftTreeMax->right = t;
					leftTreeMax = t;
					t = t->right;
				}
				else
					break;

			leftTreeMax->right = t->left;
			rightTreeMin->left = t->right;
			t->left = header.right;
			t->right = header.left;
		}


		template <class Key, class Data>
		void SplayTree<Key,Data>::rotateWithLeftChild( BinaryNode<Key,Data> * & k2 ) const
		{
			BinaryNode<Key,Data> *k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2 = k1;
		}

		template <class Key, class Data>
		void SplayTree<Key,Data>::rotateWithRightChild( BinaryNode<Key,Data> * & k1 ) const
		{
			BinaryNode<Key,Data> *k2 = k1->right;
			k1->right = k2->left;
			k2->left = k1;
			k1 = k2;
		}
	}
}