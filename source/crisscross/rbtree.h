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
// TODO: Does RedBlackNode need Parent, Left, and Right redefined?
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
		private:
			//! Private copy constructor.
			/*!
				If your code needs to invoke the copy constructor, you've probably written
				the code wrong. A tree copy is generally unnecessary, and in cases that it
				is, it can be achieved by other means.
			 */
			RedBlackTree ( const RedBlackTree<Key,Data> & );

			//! Private assignment operator.
			/*!
				If your code needs to invoke the assignment operator, you've probably written
				the code wrong. A tree copy is generally unnecessary, and in cases that it
				is, it can be achieved by other means.
			 */
			RedBlackTree<Key,Data> &operator = ( const RedBlackTree<Key,Data> & );

        protected:

            //! The root node at the top of the tree.
            RedBlackNode<Key,Data> *rootNode;
            
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

            //! Verifies that a node is valid.
			/*!
				\param _node A node pointer.
				\return True if the node is a valid node, false otherwise.
			 */
            inline bool valid ( const RedBlackNode<Key,Data> *_node ) const
			{ return ( _node != NULL ); };

        public:
            //! @cond
            typedef enum { BLACK, RED } nodeColor;
            //! @endcond

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

			//! Empties the entire tree.
			inline void empty () { killAll(); };

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

			/*
				Deprecated Compatibility Functions
				Provided for compatibility with Tosser I
			*/
			//! @cond
			_CC_DEPRECATE_FUNCTION(insert)	inline void	PutData		( Key const &_key, Data const & _rec )	{ return insert ( _key, _rec ); };
			_CC_DEPRECATE_FUNCTION(erase)	inline void	RemoveData	( Key const &_key )						{ return erase ( _key ); };
			_CC_DEPRECATE_FUNCTION(erase)	inline void	RemoveData	( Key const &_key, Data const & _rec  )	{ return erase ( _key, _rec ); };
			_CC_DEPRECATE_FUNCTION(size)	inline int	Size		() const								{ return (int)size(); };
			_CC_DEPRECATE_FUNCTION(empty)	inline void	Empty		()										{ empty(); };
			//! @endcond
        };
    }
}

#    include <crisscross/rbtree.cpp>

#endif
