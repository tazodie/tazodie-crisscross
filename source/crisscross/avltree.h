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

#ifndef __included_cc_avltree_h
#define __included_cc_avltree_h

#include <crisscross/deprecate.h>
#include <crisscross/node.h>
#include <crisscross/internal_mem.h>

namespace CrissCross
{
	namespace Data
	{

		//! The current balance status of a node
		typedef enum AVLBalance
		{
			//! The left side of the tree is heaviest.
			LEFTHEAVY,

			//! The tree is well balanced.
			BALANCED,

			//! The right side of the tree is heaviest.
			RIGHTHEAVY
		};

		template <class Key, class Data>
		class AVLNode : public BinaryNode<Key,Data>
		{
		public:
			AVLNode();

			AVLBalance m_balance;

			AVLNode *left;
			AVLNode *right;
			AVLNode *parent;

		};

		template <class Key, class Data>
		class AVLTree
		{
		protected:
			//! The root node.
			AVLNode<Key,Data> *m_root;

			//! The current tree size.
			size_t m_size;

			//! Result of tree operation
			typedef enum Result
			{
				//! None of the subtrees has grown in height, entire tree is still balanced
				OK,

				//! One of the branches has grown/shrunk in height, tree might need rebalancing
				BALANCE,

				//! Error
				INVALID
			};

			//! Rotate tree left
			/*!
				Rotate tree left around the given node
				\param _node                                        Pointer to current node pointer to rotate
			*/
			inline void                                             rotateLeft ( AVLNode<Key,Data> **_node );

			//! Rotate tree right
			/*!
				Rotate tree right around the given node
				\param _node                                        Pointer to current node pointer to rotate
			*/
			inline void                                             rotateRight ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after left side has grown
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has grown in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceLeftGrown ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after right side has grown
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has grown in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceRightGrown ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after left side has shrunk
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has shrunk in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceLeftShrunk ( AVLNode<Key,Data> **_node );

			//! Rebalance tree
			/*!
				Rebalance tree after right side has shrunk
				\param _node                                        Pointer to current node pointer to balance
				\return                                             OK if tree is balanced (entire tree is valid), BALANCE if local tree is balanced but has shrunk in height (entire tree not guaranteed to be valid)
			*/
			inline Result                                           balanceRightShrunk ( AVLNode<Key,Data> **_node );

			//! Replace node
			/*!
				Replace a node with the highest-ranking item in subtree
				\param _target                                      Pointer to node to be replaced
				\param _subtree                                     Pointer to subtree pointer to search
				\param _result                                      Pointer to result variable to tell caller if further checks are needed
				\return                                             true if node found, false if not
			*/
			inline bool                                             replaceWithHighest ( AVLNode<Key,Data> *_target, AVLNode<Key,Data> **_subtree, Result *_result );

			//! Replace node
			/*!
				Replace a node with the lowest-ranking item in subtree
				\param _target                                      Pointer to node to be replaced
				\param _subtree                                     Pointer to subtree pointer to search
				\param _result                                      Pointer to result variable to tell caller if further checks are needed
				\return                                             true if node found, false if not
			*/
			inline bool                                             replaceWithLowest ( AVLNode<Key,Data> *_target, AVLNode<Key,Data> **_subtree, Result *_result );

			//! Add object
			/*!
				Insert object in tree and rebalance
				\param _parent                                      Pointer to parent node pointer
				\param _node                                        Pointer to current node pointer
				\param _key                                         Key to insert
				\param _data                                        Data to insert
				\return                                             Result of addition (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  insert ( AVLNode<Key,Data> **_parent, AVLNode<Key,Data> **_node, Key const &_key, Data const &_data );

			//! Remove object
			/*!
				Remove object from tree and rebalance
				\param _node                                        Pointer to current node pointer
				\param _key                                         Identifier of node to remove
				\return                                             Result of removal (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  erase ( AVLNode<Key,Data> **_node, Key const &_key );

			//! Remove object
			/*!
				Remove object from tree and rebalance, taking the key and data into account
				\param _node                                        Pointer to current node pointer
				\param _key                                         Identifier of node to remove
				\param _data                                         Data identifier of node to remove
				\return                                             Result of removal (OK if subtree is balanced, BALANCE if tree is heavy on either side)
			*/
			Result                                                  erase ( AVLNode<Key,Data> **_node, Key const &_key, Data const &_data );

			//! Find a node in the tree
			/*!
				Get a pointer to a node with the specified key value
				\param _key                                         Identifier of node to remove
				\return                                             Address of the node. If not found, returns NULL.
			*/
			AVLNode<Key,Data>                                      *findNode ( Key const &_key ) const;

            void RecursiveConvertIndexToDArray ( DArray <Key> *_darray, AVLNode<Key,Data> *_btree ) const;
            void RecursiveConvertToDArray ( DArray <Data> *_darray, AVLNode<Key,Data> *_btree ) const;

			void findRecursive ( DArray<Data> *_array, Key const &_key, AVLNode<Key,Data> *_node ) const;

		public:
			AVLTree();
			virtual ~AVLTree();

			void insert ( Key const &_key, Data const &_data );
			bool erase ( Key const &_key );
			bool erase ( Key const &_key, Data const &_data );
			bool find ( Key const &_key, Data &_data ) const;
			_CC_DEPRECATE_FUNCTION_N Data find ( Key const &_key ) const;
			DArray<Data> *findAll ( Key const &_key ) const;
			bool exists ( Key const &_key ) const;
			inline void empty () { delete m_root; m_root = NULL; };
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

#include <crisscross/avltree.cpp>

#endif
