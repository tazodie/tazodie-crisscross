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

#ifndef __included_cc_node_h
#define __included_cc_node_h

#include <crisscross/internal_mem.h>

namespace CrissCross
{
    namespace Data
    {

		/*
			There's no real advantage to making these classes inherit
			a common BinaryNode class. In fact, it will impact the
			program negatively to inherit a common class because we
			are forced to either cast every reference to left/right/parent
			or override left/right/parent in the derived classes (and
			doing so would waste memory: 12 bytes per node on 32-bit
			machines).

			So we no longer inherit a common node class.
		*/

        //! A binary tree node.
        template <class Key, class Data>
        class SplayNode
        {
        public:
            //! The key for this node.
            Key         id;

            //! The data held at this node.
            Data        data;

            //! The left branch of the tree from this node.
            SplayNode *left;

            //! The right branch of the tree from this node.
            SplayNode *right;

            //! The parent node.
            SplayNode *parent;

            //! The default constructor.
            SplayNode () : left(NULL), right(NULL), parent(NULL) {}

			//! The default destructor.
			~SplayNode ()
			{
				Dealloc ( id );
				delete left; left = NULL;
				delete right; right = NULL;
			}
        };

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

        //! A binary tree node used for AVLTree.
		template <class Key, class Data>
		class AVLNode
		{
		public:
            //! The key for this node.
            Key         id;

            //! The data held at this node.
            Data        data;

			//! The state of this part of the tree's balance.
			AVLBalance balance;

            //! The left branch of the tree from this node.
			AVLNode *left;

            //! The right branch of the tree from this node.
			AVLNode *right;

            //! The parent node.
			AVLNode *parent;

            //! The default constructor.
			AVLNode (): balance(BALANCED), left(NULL), right(NULL), parent(NULL) {}

			//! The default destructor.
			~AVLNode ()
			{
				Dealloc ( id );
				delete left; left = NULL;
				delete right; right = NULL;
			}

		};

        //! A binary tree node used for RedBlackTree.
        template <class Key, class Data>
        class RedBlackNode
        {
        public:
            //! The key for this node.
            Key         id;

            //! The data held at this node.
            Data        data;

            //! The color of the node (either red or black).
            char        color;

            //! The left branch of the tree from this node.
            RedBlackNode *left;

            //! The right branch of the tree from this node.
            RedBlackNode *right;

            //! The parent node.
            RedBlackNode *parent;

            //! The default constructor.
            RedBlackNode () : left(NULL), right(NULL), parent(NULL) {}

			//! The default destructor.
			~RedBlackNode ()
			{
				Dealloc ( id );
				delete left; left = NULL;
				delete right; right = NULL;
			}
        };
    }
}

#endif
