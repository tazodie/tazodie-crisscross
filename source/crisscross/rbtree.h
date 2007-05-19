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
            STATUS_NOT_FOUND,            //!< Node couldn't be found.
            STATUS_NULL_POINTER,        //!< A null pointer was found in a parameter.
            STATUS_MEM_EXHAUSTED        //!< Out of memory.
        } statusEnum;

		template <class T>
			__inline void Duplicate ( T &_data, T &_destination )
		{
			_destination = _data;
		}

		template <>
			__inline void Duplicate<char *> ( char *&_data, char *&_destination )
		{
			_destination = strdup ( _data );
		}

		template <>
			__inline void Duplicate<const char *> ( const char *&_data, const char *&_destination )
		{
			_destination = strdup ( _data );
		}

		template <class T>
			__inline void Dealloc ( T &key )
		{
			return;
		}

		template <>
			__inline void Dealloc<char *> ( char *&key )
		{
			// Deallocates char* keys.
			free ( key );
			key = NULL;
		}

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
            statusEnum insert ( const Key &_key, const Data & _rec );

            //! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum erase ( const Key &_key );

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
            Data find ( const Key &_key ) const;

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The node pointer. NULL or NULL_NODE if not found. Test result with ValidNode() function.
                \sa ValidNode()
             */
            RedBlackNode<Key,Data> *findNode ( const Key &_key ) const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            bool valid ( const RedBlackNode<Key,Data> *_node ) const;

            //inline Data &operator [] ( const Key &_key ) { return findNode(_key)->data; };

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
            int size ();

            //! Will get the next node in the tree, useful as an iterator.
            void getNext ( RedBlackNode<Key,Data> ** _current );

            //! Converts the tree data into a linearized DArray.
            /*!
                \return A DArray containing the data of the tree.
             */
            _CC_DEPRECATE_SLOW DArray <Data> *ConvertToDArray ();

            //! Converts the tree keys into a linearized DArray.
            /*!
                \return A DArray containing the keys in the tree.
             */
            _CC_DEPRECATE_SLOW DArray <Key>  *ConvertIndexToDArray ();

        protected:
            void RecursiveConvertIndexToDArray ( DArray <Key> *_darray, RedBlackNode<Key,Data> *_btree );
            void RecursiveConvertToDArray ( DArray <Data> *_darray, RedBlackNode<Key,Data> *_btree );

            void rotateLeft ( RedBlackNode<Key,Data> * _x );
            void rotateRight ( RedBlackNode<Key,Data> * _x );
            void insertFixup ( RedBlackNode<Key,Data> * _x );
            void deleteFixup ( RedBlackNode<Key,Data> * _x );
        };
    }
}

#    include <crisscross/rbtree.cpp>

#endif
