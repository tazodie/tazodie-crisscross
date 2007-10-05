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

#ifndef __included_cc_node_h
#define __included_cc_node_h

namespace CrissCross
{
    namespace Data
    {
        //! A binary tree node.
        /*!
            \sa RedBlackNode
         */
        template <class Key, class Data>
        class BinaryNode
        {
        public:
            //! The key for this node.
            Key         id;

            //! The data held at this node.
            Data        data;

            //! The left branch of the tree from this node.
            BinaryNode *left;

            //! The right branch of the tree from this node.
            BinaryNode *right;

            //! The default constructor.
            BinaryNode () : left(NULL), right(NULL) {}

        };

        //! A binary tree node used for RedBlackTree.
        /*!
            \sa BinaryNode
         */
        template <class Key, class Data>
        class RedBlackNode: public BinaryNode<Key,Data>
        {
        public:
            //! Indicates whether or not the node has been visited in an iteration sequence.
            mutable char beenThere;

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

        //! A leaf node used for BPlusTree.
        /*!
            \sa BinaryNode
         */
        template <class Key, class Data>
        class LeafNode: public BinaryNode<Key,Data>
        {
        public:
            //! Indicates whether or not the node has been visited in an iteration sequence.
            mutable char beenThere;

            //! The color of the node (either red or black).
            char        color;

            //! The left branch of the tree from this node.
            LeafNode *left;

            //! The right branch of the tree from this node.
            LeafNode *right;

            //! The parent node.
            LeafNode *parent;

            //! The default constructor.
            LeafNode () : BinaryNode<Key,Data>() {}
        };

        //! An inner node used for BPlusTree.
        /*!
            \sa BinaryNode
         */
        template <class Key, class Data>
        class InnerNode: public BinaryNode<Key,Data>
        {
        public:
            //! Indicates whether or not the node has been visited in an iteration sequence.
            mutable char beenThere;

            //! The color of the node (either red or black).
            char        color;

            //! The left branch of the tree from this node.
            InnerNode *left;

            //! The right branch of the tree from this node.
            InnerNode *right;

            //! The parent node.
            InnerNode *parent;

            //! The default constructor.
            InnerNode () : BinaryNode<Key,Data>() {}
        };
    }
}

#include <crisscross/rbtree.h>

#endif
