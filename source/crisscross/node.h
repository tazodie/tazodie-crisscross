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

			//! The default destructor.
			virtual ~BinaryNode ()
			{
				delete left; left = NULL;
				delete right; right = NULL;
			}
        };
    }
}

#endif
