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

#ifndef __included_rbtree_h
#define __included_rbtree_h

#include <crisscross/core_deprecate.h>
#include <crisscross/darray.h>

#include <crisscross/tree.h>

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
            STATUS_NULL_POINTER,        //!< A null pointer was found in a parameter.
            STATUS_MEM_EXHAUSTED        //!< Out of memory.
        } statusEnum;

        //! A very fast red-black tree implementation.
        template < class T >
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
            BinaryNode<T> *rootNode;
            
            //! The null node at the end of every branch, etc.
            BinaryNode<T> *NULL_NODE;

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
            statusEnum insert ( const char *_key, const T & _rec );

            //! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum deleteNode ( const char *_key );

            //! Deletes a node from the tree, specified by the pointer to the node.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _z The node to remove.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum killNode ( BinaryNode<T> * _z );

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The data at the node. NULL if not found.
             */
            T find ( const char *_key ) const;

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The node pointer. NULL or NULL_NODE if not found. Test result with ValidNode() function.
                \sa ValidNode()
             */
            BinaryNode<T> *findNode ( const char *_key ) const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            bool ValidNode ( const BinaryNode<T> *_node ) const;

        protected:
            inline char *reallocKey ( char *_pointer, char *_a );
            inline int *reallocKey ( int *_pointer, int *_a );
            inline unsigned long *reallocKey ( unsigned long *_pointer, unsigned long *_a );

            inline char *newKey ( const char *_a );
            inline int *newKey ( const int *_a );
            inline unsigned long *newKey ( const unsigned long *_a );

            inline bool compLT ( const char *_a, const char *_b ) const;
            inline bool compLTEQ ( const char *_a, const char *_b ) const;
            inline bool compEQ ( const char *_a, const char *_b ) const;

            inline bool compLT ( const int *_a, const int *_b ) const;
            inline bool compLTEQ ( const int *_a, const int *_b ) const;
            inline bool compEQ ( const int *_a, const int *_b ) const;

            inline bool compLT ( const unsigned long *_a, const unsigned long *_b ) const;
            inline bool compLTEQ ( const unsigned long *_a, const unsigned long *_b ) const;
            inline bool compEQ ( const unsigned long *_a, const unsigned long *_b ) const;

            /*
            these are automatically called. no need to use them externally at all.
            */
            void killAll ( BinaryNode<T> *_rec );
            void killAll ();

        public:
            //! Indicates the size of the tree.
            /*!
                \return Size of the tree.
             */
            int size ();

            //! Will get the next node in the tree, useful as an iterator.
            void getNext ( BinaryNode<T> ** _current );

            //! @cond
            /*
                other old backward-compatible functions
            */
            _CC_DEPRECATE_FUNCTION ( find )         T           GetData ( const char *_key ) const;
            _CC_DEPRECATE_FUNCTION ( insert )       void        PutData ( const char *_key, const T & _rec );
            _CC_DEPRECATE_FUNCTION ( deleteNode )   void        RemoveData ( const char *_key );
            _CC_DEPRECATE_FUNCTION ( findNode )     BinaryNode<T> *LookupTree ( const char *_key );
            _CC_DEPRECATE_FUNCTION ( size )         int         Size ();
                                                    void        Print ();
            //! @endcond

        public:
            //! Converts the tree data into a linearized DArray.
            /*!
                \return A DArray containing the data of the tree.
             */
            DArray <T> *ConvertToDArray ();

            //! Converts the tree keys into a linearized DArray.
            /*!
                \return A DArray containing the keys in the tree.
             */
            DArray <char *>  *ConvertIndexToDArray ();

        protected:
            void RecursiveConvertIndexToDArray ( DArray <char *> *_darray, BinaryNode<T> *_btree );
            void RecursiveConvertToDArray ( DArray <T> *_darray, BinaryNode<T> *_btree );

            void rotateLeft ( BinaryNode<T> * _x );
            void rotateRight ( BinaryNode<T> * _x );
            void insertFixup ( BinaryNode<T> * _x );
            void deleteFixup ( BinaryNode<T> * _x );
        };
    }
}

#    include <crisscross/rbtree.cpp>

#endif
