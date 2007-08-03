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
#include <crisscross/darray.h>
#include <crisscross/node.h>

namespace CrissCross
{
    namespace Data
    {
        //! An enumeration used to indicate the result of RedBlackTree calls.
        /*!
            \sa RedBlackTree
         */
        typedef enum
        {
            STATUS_OK,                  //!< Success.
            STATUS_NOT_FOUND,           //!< Node couldn't be found.
            STATUS_NULL_POINTER,        //!< A null pointer was found in a parameter.
            STATUS_MEM_EXHAUSTED        //!< Out of memory.
        } statusEnum;

        //! @cond

        // These functions are designed for RedBlackTree internal use.
        // You generally shouldn't use them unless you know what you're doing.

        template < class T >
        __inline T Duplicate ( T const &_data )
        {
            return _data;
        }
        
        template <>
        __inline char *Duplicate ( char * const &_data )
        {
            return strdup ( _data );
        }

        template <>
        __inline const char *Duplicate ( const char * const &_data )
        {
            return strdup ( _data );
        }

        template < class T >
        __inline void Dealloc ( T const &_data )
        {
        }
        
        template <>
        __inline void Dealloc ( char * const &_data )
        {
            if ( _data ) free ( _data );
        }
        
        template <>
        __inline void Dealloc ( const char * const &_data )
        {
            if ( _data ) free ( (char *)_data );
        }

        //! @endcond

        //! A very fast red-black tree implementation.
        template < class Key, class Data >
        class RedBlackTree
        {

        public:
            //! @cond
            typedef enum { BLACK, RED } nodeColor;
            typedef enum
            {
                NODE_ITSELF_VISITED = 0,
                LEFT_CHILD_VISITED,
                ALL_CHILDS_VISITED
            } beenThereEnum;
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
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum insert ( Key const &_key, Data const & _rec );

            //! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum erase ( Key const &_key );

            //! Deletes a node from the tree, specified by the node's key and data.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \param _rec The data of the node to delete.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum erase ( Key const &_key, Data const & _rec );

            //! Deletes a node from the tree, specified by the pointer to the node.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _z The node to remove.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum killNode ( RedBlackNode<Key,Data> * _z );

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The data at the node. NULL if not found.
             */
            Data find ( Key const &_key ) const;

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The node pointer. NULL or NULL_NODE if not found. Test result with ValidNode() function.
                \sa ValidNode()
             */
            RedBlackNode<Key,Data> *findNode ( Key const &_key ) const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            inline bool valid ( const RedBlackNode<Key,Data> *_node ) const
			{ return ( _node != NULL && _node != NULL_NODE ); };

			//! Empties the entire tree.
			inline void empty () { killAll(); rootNode = NULL_NODE; };

        protected:

            /*
            these are automatically called. no need to use them externally at all.
            */
            void killAll ( RedBlackNode<Key,Data> *_rec );
            void killAll ();

        public:
            //! Indicates the size of the tree.
            /*!
                \return Size of the tree.
             */
#ifndef _DEBUG
			inline size_t size () const { return m_cachedSize; };
#else
			size_t size () const;
#endif

            //! Will get the next node in the tree, useful as an iterator.
            void getNext ( RedBlackNode<Key,Data> ** _current ) const;

            //! Converts the tree data into a linearized DArray.
            /*!
                \return A DArray containing the data of the tree.
             */
            _CC_DEPRECATE_SLOW("MINOR") DArray <Data> *ConvertToDArray () const;

            //! Converts the tree keys into a linearized DArray.
            /*!
                \return A DArray containing the keys in the tree.
             */
            _CC_DEPRECATE_SLOW("MINOR") DArray <Key>  *ConvertIndexToDArray () const;

			/*
				Deprecated Compatibility Functions
				Provided for compatibility with Tosser I
			*/
			//! @cond
			_CC_DEPRECATE_FUNCTION(insert) inline statusEnum PutData ( Key const &_key, Data const & _rec ) { return insert ( _key, _rec ); };
			_CC_DEPRECATE_FUNCTION(erase) inline statusEnum RemoveData ( Key const &_key ) { return erase ( _key ); };
			_CC_DEPRECATE_FUNCTION(erase) inline statusEnum remove ( Key const &_key ) { return erase ( _key ); };
			_CC_DEPRECATE_FUNCTION(erase) inline statusEnum remove ( Key const &_key, Data const & _rec  ) { return erase ( _key, _rec ); };
			_CC_DEPRECATE_FUNCTION(size) inline size_t Size () const { return size(); };
			_CC_DEPRECATE_FUNCTION_N inline void Empty () { killAll(); };
			//! @endcond

        protected:
			size_t m_cachedSize;

            void RecursiveConvertIndexToDArray ( DArray <Key> *_darray, RedBlackNode<Key,Data> *_btree ) const;
            void RecursiveConvertToDArray ( DArray <Data> *_darray, RedBlackNode<Key,Data> *_btree ) const;

            void rotateLeft ( RedBlackNode<Key,Data> * _x );
            void rotateRight ( RedBlackNode<Key,Data> * _x );
            void insertFixup ( RedBlackNode<Key,Data> * _x );
            void deleteFixup ( RedBlackNode<Key,Data> * _x );
        };
    }
}

#    include <crisscross/rbtree.cpp>

#define BTree RedBlackTree

#endif
