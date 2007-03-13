/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#ifndef __included_rbtree_h
#define __included_rbtree_h

#    include <crisscross/core_deprecate.h>
#    include <crisscross/darray.h>

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
        template < class dataType, class keyType >
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

            /*
                This is what a node looks like in this tree.
            */
            struct nodeType
            {
                struct nodeType *left;    // Left child.
                struct nodeType *right;    // Right child.
                struct nodeType *parent;    // Supernode.
                nodeColor color;        // Color of this node (Red/Black).

                keyType id;                // This node's key (doesn't have to be unique).
                dataType data;            // The actual record associated with this node.
                beenThereEnum beenThere;    // Used for iterators.
                struct nodeType *Left ()
                {
                    return left;
                }
                struct nodeType *Right ()
                {
                    return right;
                }

                nodeType(){};
                ~nodeType(){};
            };
            //! @endcond

            //! The root node at the top of the tree.
            nodeType *rootNode;
            
            //! The null node at the end of every branch, etc.
            nodeType *NULL_NODE;

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
            statusEnum insert ( keyType _key, dataType _rec );

            //! Deletes a node from the tree, specified by the node's key.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _key The key of the node to delete.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum deleteNode ( keyType _key );

            //! Deletes a node from the tree, specified by the pointer to the node.
            /*!
                This won't free the memory occupied by the data, so the data must be freed
                seperately.
                \param _z The node to remove.
                \return A value indicating the result of the request.
                \sa statusEnum
             */
            statusEnum killNode ( nodeType * _z );

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The data at the node. NULL if not found.
             */
            dataType find ( keyType _key ) const;

            //! Finds a node in the tree and returns the data at that node.
            /*!
                \param _key The key of the node to find.
                \return The node pointer. NULL or NULL_NODE if not found. Test result with ValidNode() function.
                \sa ValidNode()
             */
            nodeType *findNode ( keyType _key ) const;

            //! Verifies that a node is valid.
            /*!
                \param _node A node pointer.
                \return True if the node is a valid node, false otherwise.
             */
            bool ValidNode ( nodeType * _node ) const;

        protected:
            inline char *reallocKey ( char *_pointer, char *_a );
            inline int *reallocKey ( int *_pointer, int *_a );
            inline unsigned long *reallocKey ( unsigned long *_pointer, unsigned long *_a );

            inline char *newKey ( char *_a );
            inline int *newKey ( int *_a );
            inline unsigned long *newKey ( unsigned long *_a );

            inline bool compLT ( const char *_a, const char *_b ) const;
            inline bool compLTEQU ( const char *_a, const char *_b ) const;
            inline bool compEQ ( const char *_a, const char *_b ) const;

            inline bool compLT ( const int *_a, const int *_b ) const;
            inline bool compLTEQU ( const int *_a, const int *_b ) const;
            inline bool compEQ ( const int *_a, const int *_b ) const;

            inline bool compLT ( const unsigned long *_a, const unsigned long *_b ) const;
            inline bool compLTEQU ( const unsigned long *_a, const unsigned long *_b ) const;
            inline bool compEQ ( const unsigned long *_a, const unsigned long *_b ) const;

            /*
            these are automatically called. no need to use them externally at all.
            */
            void killAll ( nodeType *_rec );
            void killAll ();

        public:
            //! Indicates the size of the tree.
            /*!
                \return Size of the tree.
             */
            int size ();

            //! Will get the next node in the tree, useful as an iterator.
            void getNext ( nodeType ** _current );

            //! @cond
            /*
                other old backward-compatible functions
            */
            _CC_DEPRECATE_FUNCTION ( find )         dataType    GetData ( keyType _key ) const;
            _CC_DEPRECATE_FUNCTION ( insert )       void        PutData ( keyType _key, dataType _rec );
            _CC_DEPRECATE_FUNCTION ( deleteNode )   void        RemoveData ( keyType _key );
            _CC_DEPRECATE_FUNCTION ( findNode )     nodeType    *LookupTree ( keyType _key );
            _CC_DEPRECATE_FUNCTION ( size )         int         Size ();
                                                    void        Print ();
            //! @endcond

        public:
            //! Converts the tree data into a linearized DArray.
            /*!
                \return A DArray containing the data of the tree.
             */
            DArray < dataType > *ConvertToDArray ();

            //! Converts the tree keys into a linearized DArray.
            /*!
                \return A DArray containing the keys in the tree.
             */
            DArray < keyType >  *ConvertIndexToDArray ();

        protected:
            void RecursiveConvertIndexToDArray ( DArray < keyType > *_darray, nodeType *_btree );
            void RecursiveConvertToDArray ( DArray < dataType > *_darray, nodeType *_btree );

            void rotateLeft ( nodeType * _x );
            void rotateRight ( nodeType * _x );
            void insertFixup ( nodeType * _x );
            void deleteFixup ( nodeType * _x );
        };
    }
}

#    include <crisscross/rbtree.cpp>

#endif
