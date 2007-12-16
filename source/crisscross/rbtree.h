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

#ifndef __included_cc_rbtree_h
#define __included_cc_rbtree_h

#include <crisscross/deprecate.h>
#include <crisscross/internal_mem.h>
#include <crisscross/darray.h>
#include <crisscross/node.h>
#include <crisscross/mutex.h>

namespace CrissCross
{
    namespace Data
    {

        //! A binary tree node used for RedBlackTree.
        /*!
            \sa BinaryNode
         */
        template <class Key, class Data>
        class RedBlackNode: public BinaryNode<Key,Data>
        {
        public:
            //! The color of the node (either red or black).
            char        color;

            //! The left branch of the tree from this node.
            RedBlackNode *left;

            //! The right branch of the tree from this node.
            RedBlackNode *right;

            //! The parent node.
            RedBlackNode *parent;

            //! The default constructor.
            RedBlackNode () : BinaryNode<Key,Data>() {}
        };

        //! A very fast red-black tree implementation.
        template < class Key, class Data >
        class RedBlackTree
        {
        protected:

			//! The cached size() return value. Changes on each tree modification (insertions and deletions).
			size_t m_cachedSize;

            void RecursiveConvertIndexToDArray ( DArray <Key> *_darray, RedBlackNode<Key,Data> *_btree ) const;
            void RecursiveConvertToDArray ( DArray <Data> *_darray, RedBlackNode<Key,Data> *_btree ) const;

            void rotateLeft ( RedBlackNode<Key,Data> * _x );
            void rotateRight ( RedBlackNode<Key,Data> * _x );
            void insertFixup ( RedBlackNode<Key,Data> * _x );
            void deleteFixup ( RedBlackNode<Key,Data> * _x );

			void findRecursive ( DArray<Data> *_array, Key const &_key, RedBlackNode<Key,Data> *_node ) const;

			void killAll ();
			void killAll ( RedBlackNode<Key,Data> *rec );

			bool killNode ( RedBlackNode<Key,Data> * z );
			
			bool erase ( Key const &key, Data const &rec, RedBlackNode<Key,Data> *curnode );

			RedBlackNode<Key,Data> *findNode ( Key const &key ) const;

        public:
            //! @cond
            typedef enum { BLACK, RED } nodeColor;
            //! @endcond

            //! The root node at the top of the tree.
            RedBlackNode<Key,Data> *rootNode;
            
            //! The null node at the end of every branch, etc.
            RedBlackNode<Key,Data> *NULL_NODE;

            //! The constructor.
            RedBlackTree ();
            
            //! The destructor.
            ~RedBlackTree ();

            //! Inserts data into the tree.
            /*!
                \param _key The key of the data.
                \param _rec The data to insert.
                \return True on success, false on failure.
             */
            bool insert ( Key const &_key, Data const &_rec );

            //! Change the data at the given node.
            /*!
                \param _key The key of the node to be modified.
                \param _rec The data to insert.
                \return True on success, false on failure.
             */
            bool replace ( Key const &_key, Data const &_rec );

            //! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return True on success, false on failure
             */
            bool erase ( Key const &_key );

            //! Deletes a node from the tree, specified by the node's key and data.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \param _rec The data of the node to delete.
                \return True on success, false on failure.
             */
            bool erase ( Key const &_key, Data const & _rec );

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
			_CC_DEPRECATE_FUNCTION_N Data find ( Key const &_key ) const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            inline bool valid ( const RedBlackNode<Key,Data> *_node ) const
			{ return ( _node != NULL && _node != NULL_NODE ); };

			//! Empties the entire tree.
			inline void empty () { killAll(); rootNode = NULL_NODE; };

            //! Indicates the size of the tree.
            /*!
                \return Size of the tree.
             */
			inline size_t size () const { return m_cachedSize; };

            //! Finds all instances of the specified key in the tree.
            /*!
                \param _key The key of the node to find.
                \return A DArray containing the data with key _key. MUST be deleted when done!
             */
			DArray<Data> *findAll ( Key const &_key ) const;

            //! Tests whether a key is in the tree or not.
            /*!
                \param _key The key of the node to find.
                \return True if the key is in the tree, false if not.
             */
			bool exists ( Key const &_key ) const;

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

#    include <crisscross/rbtree.cpp>

#endif
