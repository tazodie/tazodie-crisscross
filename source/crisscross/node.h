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
            Key            id;

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
            char        beenThere;

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
    }
}

#include <crisscross/rbtree.h>

#endif
