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

#ifndef __included_rbtree_cpp
#define __included_rbtree_cpp

#include <stdlib.h>

#include <crisscross/core_debug.h>
#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

#ifndef TARGET_OS_WINDOWS
#    define stricmp strcasecmp
#endif

template <class T>
    RedBlackTree<T>::RedBlackTree ()
{
    NULL_NODE = new BinaryNode<T> ();
    NULL_NODE->color = BLACK;
    rootNode = NULL_NODE;
}

template <class T>
    RedBlackTree<T>::~RedBlackTree ()
{
    killAll ();
    delete NULL_NODE;
}

template <class T>
	inline bool RedBlackTree<T>::compLT ( const char *a, const char *b ) const
{
    return ( stricmp ( a, b ) < 0 );
}

template <class T>
	inline bool RedBlackTree<T>::compLTEQ ( const char *a, const char *b ) const
{
    return ( stricmp ( a, b ) <= 0 );
}

template <class T>
	inline bool RedBlackTree<T>::compEQ ( const char *a, const char *b ) const
{
    return ( stricmp ( a, b ) == 0 );
}

template <class T>
	inline bool RedBlackTree<T>::compLT ( const int *a, const int *b ) const
{
    return ( *a < *b );
}

template <class T>
	inline bool RedBlackTree<T>::compLTEQ ( const int *a, const int *b ) const
{
    return ( *a <= *b );
}

template <class T>
	inline bool RedBlackTree<T>::compEQ ( const int *a, const int *b ) const
{
    return ( *a == *b );
}

template <class T>
	inline bool RedBlackTree<T>::compLT ( const unsigned long *a, const unsigned long *b ) const
{
    return ( *a < *b );
}


template <class T>
	inline bool RedBlackTree<T>::compLTEQ ( const unsigned long *a, const unsigned long *b ) const
{
    return ( *a <= *b );
}

template <class T>
	inline bool RedBlackTree<T>::compEQ ( const unsigned long *a, const unsigned long *b ) const

{
    return ( *a == *b );
}

template <class T>
    inline char *RedBlackTree<T>::newKey ( const char *a )
{
    char *b = ( char * ) malloc ( strlen ( a ) + 1 );
    if ( !b )
        return 0;
    memset ( b, 0, strlen ( a ) + 1 );
    strcpy ( b, a );
    return b;
}

template <class T>
    inline int *RedBlackTree<T>::newKey ( const int *a )
{
    int *b = ( int * ) malloc ( sizeof ( int ) );

    if ( !b )
        return 0;
    memset ( b, 0, sizeof ( int ) );
    *b = *a;
    return b;
}

template <class T>
    inline unsigned long *RedBlackTree<T>::newKey ( const unsigned long *a )
{
    unsigned long *b = ( unsigned long * ) malloc ( sizeof ( unsigned long ) );

    if ( !b )
        return 0;
    memset ( b, 0, sizeof ( unsigned long ) );
    *b = *a;
    return b;
}

template <class T>
    inline char *RedBlackTree<T>::reallocKey ( char *pointer, char *a )
{
    char *tmp = NULL;

    tmp = ( char * ) realloc ( pointer, strlen ( a ) + 1 );
    if ( !tmp )
        return 0;
    memset ( tmp, 0, strlen ( a ) + 1 );
    strcpy ( tmp, a );
    return tmp;
}

template <class T>
    inline int *RedBlackTree<T>::reallocKey ( int *pointer, int *a )
{
    /* since integers don't have varying size, just overwrite */
    *pointer = *a;
    return pointer;
}

template <class T>
    inline unsigned long *RedBlackTree<T>::reallocKey ( unsigned long *pointer, unsigned long *a )
{
    /* since unsigned longs don't have varying size, just overwrite */
    *pointer = *a;
    return pointer;
}

template <class T>
    void RedBlackTree<T>::rotateLeft ( BinaryNode<T> * x )
{
    BinaryNode<T> *y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if ( y->left != NULL_NODE )
        y->left->parent = x;

    /* establish y->parent link */
    if ( y != NULL_NODE )
        y->parent = x->parent;
    if ( x->parent )
    {
        if ( x == x->parent->left )
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else
    {
        rootNode = y;
    }

    /* link x and y */
    y->left = x;
    if ( x != NULL_NODE )
        x->parent = y;
}

template <class T>
    void RedBlackTree<T>::rotateRight ( BinaryNode<T> * x )
{
    BinaryNode<T> *y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if ( y->right != NULL_NODE )
        y->right->parent = x;

    /* establish y->parent link */
    if ( y != NULL_NODE )
        y->parent = x->parent;
    if ( x->parent )
    {
        if ( x == x->parent->right )
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else
    {
        rootNode = y;
    }

    /* link x and y */
    y->right = x;
    if ( x != NULL_NODE )
        x->parent = y;
}

template <class T>
    void RedBlackTree<T>::insertFixup ( BinaryNode<T> * x )
{
    /* check Red-Black properties */
    while ( x != rootNode && x->parent->color == RED )
    {
        /* we have a violation */
        if ( x->parent == x->parent->parent->left )
        {
            BinaryNode<T> *y = x->parent->parent->right;

            if ( y->color == RED )
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if ( x == x->parent->right )
                {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft ( x );
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight ( x->parent->parent );
            }
        }
        else
        {

            /* mirror image of above code */
            BinaryNode<T> *y = x->parent->parent->left;

            if ( y->color == RED )
            {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                /* uncle is BLACK */
                if ( x == x->parent->left )
                {
                    x = x->parent;
                    rotateRight ( x );
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft ( x->parent->parent );
            }
        }
    }
    rootNode->color = BLACK;
}

template <class T>
    statusEnum RedBlackTree<T>::insert ( const char *key, const T & rec )
{
    BinaryNode<T> *current = NULL_NODE, *parent = NULL, *x = NULL_NODE;

    if ( !key )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::insert() called with NULL key pointer!\n" );
    }
    if ( !rec )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::insert() called with NULL data pointer!\n" );
    }
    if ( !key || !rec )
        return STATUS_NULL_POINTER;

    /* find future parent */
    current = rootNode;
    while ( current != NULL_NODE )
    {
        parent = current;
        current = compLTEQ ( key, current->id ) ?
            current->left : current->right;
    }

    /* setup new node */
    if ( (x = new BinaryNode<T>()) == 0 )
        return STATUS_MEM_EXHAUSTED;

    x->parent = parent;
    x->left = NULL_NODE;
    x->right = NULL_NODE;
    x->color = RED;
    x->id = newKey ( key );
    x->data = rec;
    x->beenThere = NODE_ITSELF_VISITED;

    /* insert node in tree */
    if ( parent != NULL )
    {
        if ( compLTEQ ( key, parent->id ) )
            parent->left = x;
        else
            parent->right = x;
    }
    else
    {
        rootNode = x;
    }

    insertFixup ( x );

    return STATUS_OK;
}

template <class T>
    void RedBlackTree<T>::deleteFixup ( BinaryNode<T> * x )
{
    while ( x != rootNode && x->color == BLACK )
    {
        if ( x == x->parent->left )
        {
            BinaryNode<T> *w = x->parent->right;

            if ( w->color == RED )
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft ( x->parent );
                w = x->parent->right;
            }
            if ( w->left->color == BLACK && w->right->color == BLACK )
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if ( w->right->color == BLACK )
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight ( w );
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft ( x->parent );
                x = rootNode;
            }
        }
        else
        {
            BinaryNode<T> *w = x->parent->left;

            if ( w->color == RED )
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight ( x->parent );
                w = x->parent->left;
            }
            if ( w->right->color == BLACK && w->left->color == BLACK )
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if ( w->left->color == BLACK )
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft ( w );
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight ( x->parent );
                x = rootNode;
            }
        }
    }
    x->color = BLACK;
}

template <class T>
    statusEnum RedBlackTree<T>::deleteNode ( const char *key )
{
    BinaryNode<T> *z, *parent;

    //  delete node z from tree

    /* find node in tree */
    z = rootNode;
    parent = 0;

    while ( z != NULL_NODE )
    {
        if ( compEQ ( key, z->id ) )
            break;
        else
        {
            parent = z;
            z = compLTEQ ( key, z->id ) ? z->left : z->right;
        }
    }

    if ( z == NULL_NODE )
        throw;

    return killNode ( z );
}

template <class T>
    statusEnum RedBlackTree<T>::killNode ( BinaryNode<T> * z )
{
    BinaryNode<T> *x, *y;

    if ( z->left == NULL_NODE || z->right == NULL_NODE )
    {
        /* y has a NULL_NODE node as a child */
        y = z;
    }
    else
    {
        /* find tree successor with a NULL_NODE node as a child */
        y = z->right;

        while ( y->left != NULL_NODE )
            y = y->left;
    }

    /* x is y's only child */
    if ( y->left != NULL_NODE )
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if ( y->parent )
    {
        if ( y == y->parent->left )
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    else
        rootNode = x;

    if ( y != z )
    {
        if ( !z->id )
            z->id = newKey ( y->id );
        else
            z->id = reallocKey ( z->id, y->id );

        z->data = y->data;
    }

    if ( y->color == BLACK )
        deleteFixup ( x );

    free ( y->id );
    delete y;

    return STATUS_OK;
}


/* --------------------------------------------------------------------------------
    getNext:
        Get next node in tree after the one specified.
    
    TAKES:
        current        -    The node whose successor we are to get, or NULL_NODE to
                        get the first node.
    
    GIVES:
        current        -    The node following the one specified on input, or
                        NULL_NODE if there are no more nodes.
    
    NOTE:        Iterating a tree this way is kinda hairy. For this reason we keep
                some data in each node that tells us whether we already visited
                this node. There are three states: NODE_ITSELF_VISITED means we
                are returning this node right now, and this is set whenever a node
                is returned.
                LEFT_CHILD_VISITED means this node has been visited and it has two
                children of which we are now returning the left one.
                ALL_CHILDS_VISITED means this node has been visited and it has one
                unvisited child which we are now returning.
            
                If a node with ALL_CHILDS_VISITED is passed in, this means we are
                completely done with this node. So we loop uptree again (using the
                "parent" field) until we encounter a node that is
                LEFT_CHILD_VISITED (it can't be NODE_ITSELF_VISITED since it's our
                parent and we do a left-first search) or until we are at the root
                and the root also has ALL_CHILDS_VISITED set, in which case we
                return NULL.
        
    WARNING:    If you call getNext() in a loop, be sure to check the node pointer
                you pass in against the NULL node (NULL_NODE) and exit if that's the
                case, or you could enter an endless loop. Also verify that the new
                pointer for 'current' points to a valid node (ValidNode() does this
                trick).

   ----------------------------------------------------------------------------- */

template <class T>
    void RedBlackTree<T>::getNext ( BinaryNode<T> ** current )
{
    if ( ( *current ) == NULL_NODE )
    {
        ( *current ) = rootNode;
        if ( ( **current ).left == NULL_NODE )
        {
            if ( ( **current ).right == NULL_NODE )
                ( **current ).beenThere = ALL_CHILDS_VISITED;
            else
                ( **current ).beenThere = LEFT_CHILD_VISITED;
        }
        else
            ( **current ).beenThere = NODE_ITSELF_VISITED;
        return;
    }

    switch ( ( **current ).beenThere )
    {
    case NODE_ITSELF_VISITED:
        // Go to our left child:
        if ( ( **current ).right != NULL_NODE )    // Have a right child that also needs to be walked?
            ( **current ).beenThere = LEFT_CHILD_VISITED;
        else                    // This is the only child?
            ( **current ).beenThere = ALL_CHILDS_VISITED;    // We're done.
        if ( ( **current ).left != NULL_NODE )
        {
            ( *current ) = ( **current ).left;
            // Clear left child's flag:
            ( **current ).beenThere = NODE_ITSELF_VISITED;
            break;
        }
        // Else drop through!!!

    case LEFT_CHILD_VISITED:
        // Go to our right child:
        ( **current ).beenThere = ALL_CHILDS_VISITED;
        if ( ( **current ).right != NULL_NODE )
        {
            ( *current ) = ( **current ).right;
            // Clear right child's flag:
            ( **current ).beenThere = NODE_ITSELF_VISITED;
            break;
        }
        // Else drop through!

    case ALL_CHILDS_VISITED:
        // Go to our boss:
        // Note that for some strange reason this NULL_NODE nonsense isn't used for parents.
        while ( ( *current ) != NULL_NODE
                && ( **current ).beenThere == ALL_CHILDS_VISITED )
            if ( ( **current ).parent != NULL )
                ( *current ) = ( **current ).parent;
            else
            {
                ( *current ) = NULL;
                return;
            }

        if ( ( *current ) != NULL_NODE )    // We're about to return a node:
        {
            if ( ( **current ).beenThere == NODE_ITSELF_VISITED )
            {
                if ( ( **current ).right == NULL_NODE )
                    ( **current ).beenThere = ALL_CHILDS_VISITED;
                else
                    ( **current ).beenThere = LEFT_CHILD_VISITED;

                ( *current ) = ( **current ).left;
                ( **current ).beenThere = NODE_ITSELF_VISITED;
            }
            else if ( ( **current ).beenThere == LEFT_CHILD_VISITED )
            {
                ( **current ).beenThere = ALL_CHILDS_VISITED;

                ( *current ) = ( **current ).right;
                ( **current ).beenThere = NODE_ITSELF_VISITED;
            }
        }
        break;
    }
}

template <class T>
    T RedBlackTree<T>::find ( const char *key ) const
{
    BinaryNode<T> *current = rootNode;

#    ifdef SHOW_NODE_SEARCH_PROGRESS
    int hops = 0;
#    endif
    if ( !key )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::find() called with NULL key pointer!\n" );
        return NULL;
    }
#    ifdef SHOW_NODE_SEARCH_PROGRESS
    printf ( "Searching for '%s'... ", ( char * ) key );
#    endif
    while ( current != NULL_NODE )
    {
#    ifdef SHOW_NODE_SEARCH_PROGRESS
        hops++;
#    endif
        if ( compEQ ( key, current->id ) )
        {
#    ifdef SHOW_NODE_SEARCH_PROGRESS
            printf ( "Found in %d hops.\n", hops );
#    endif
            return current->data;
        }
        else
        {
            current = compLTEQ ( key, current->id ) ?
                current->left : current->right;
        }
    }

    return NULL;
}

template <class T>
    BinaryNode<T> * RedBlackTree<T>::findNode ( const char *key ) const
{
    BinaryNode<T> * current = rootNode;

#    ifdef SHOW_NODE_SEARCH_PROGRESS
    int hops = 0;
#    endif
    if ( !key )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::findNode() called with NULL key pointer!\n" );
        return NULL;
    }
#    ifdef SHOW_NODE_SEARCH_PROGRESS
    printf ( "Searching for '%s'...", ( char * ) key );
#    endif
    while ( current != NULL_NODE )
    {
#    ifdef SHOW_NODE_SEARCH_PROGRESS
        hops++;
#    endif
        if ( compEQ ( key, current->id ) )
        {
#    ifdef SHOW_NODE_SEARCH_PROGRESS
            printf ( "Found in %d hops!\n", hops );
#    endif
            return current;
        }
        else
        {
            current = compLTEQ ( key, current->id ) ? current->left : current->right;
        }
    }

    return NULL;
}

template <class T>
    void RedBlackTree<T>::killAll ( BinaryNode<T> * rec )
{
    if ( rec == NULL_NODE )
        return;

    // First kill our subnodes:
    if ( rec->left != NULL_NODE )
        killAll ( rec->left );

    if ( rec->right != NULL_NODE )
        killAll ( rec->right );

    if ( rec->parent != NULL )    // We're not root.
    {
        if ( rec->parent->left == rec )
            rec->parent->left = NULL_NODE;
        else
            rec->parent->right = NULL_NODE;
    }

    free ( rec->id );
    delete rec;
}

template <class T>
    void RedBlackTree<T>::killAll ()
{
    killAll ( rootNode );
}

template <class T>
    int RedBlackTree<T>::size ()
{
    BinaryNode<T> *vNode = NULL_NODE;
    int vCount = 0;

    getNext ( &vNode );
    while ( ValidNode ( vNode ) )
    {
        vCount++;
        getNext ( &vNode );
    }

    return vCount;
}

template <class T>
    bool RedBlackTree <T>::ValidNode ( const BinaryNode<T> * node ) const
{
    if ( node != NULL && node != NULL_NODE )
        return true;
    else
        return false;
}

/* ******************************************************
 *            RedBlackTree backward-compatibility
 * ******************************************************
 *
 * These functions are only here to make the transition
 * to the RedBlackTree class easier.
 *
 * NOTE: Most of the functions below this comment
 *         block are deprecated. Do not use these
 *         functions in new software, as they may
 *         be removed from future versions.
 */

template <class T>
    DArray<T> *RedBlackTree <T>::ConvertToDArray ()
{
    DArray<T> *darray = new DArray<T> ( (int)size() );
    RecursiveConvertToDArray ( darray, rootNode );
    return darray;
}

template <class T>
    DArray<char *> *RedBlackTree <T>::ConvertIndexToDArray ()
{
    DArray<char *> *darray = new DArray<T> ( (int)size () );
    RecursiveConvertIndexToDArray ( darray, rootNode );
    return darray;
}

template <class T>
    void RedBlackTree<T>::RecursiveConvertToDArray ( DArray<T> *darray, BinaryNode<T> *btree )
{
    // note that the btree parameter is ignored

    BinaryNode<T> *current = NULL_NODE;

    CoreAssert ( darray != NULL );

    getNext ( &current );
    while ( ValidNode ( current ) )
    {
        if ( current->data )
            darray->insert ( current->data );
        getNext ( &current );
    }
}

template <class T>
    void RedBlackTree<T>::RecursiveConvertIndexToDArray ( DArray <char *> *darray, BinaryNode<T> * btree )
{
    // note that the btree parameter is ignored

    BinaryNode<T> *current = NULL_NODE;

    CoreAssert ( darray != NULL );

    getNext ( &current );
    while ( ValidNode ( current ) )
    {
        if ( current->id )
            darray->insert ( current->id );
        getNext ( &current );
    }
}

template <class T>
    void RedBlackTree<T>::Print ()
{
    BinaryNode<T> *current = NULL_NODE;

    getNext ( &current );
    while ( ValidNode ( current ) )
    {
        if ( current->id )
            printf ( "%s : %s\n", current->key, current->data );
        getNext ( &current );
    }
}

template <class T>
    T RedBlackTree<T>::GetData ( const char *key ) const
{
    if ( !key )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::GetData() called with NULL key pointer!\n" );
        return NULL;
    }
    return find ( key );
}

template <class T>
    void RedBlackTree<T>::PutData ( const char *key, const T & rec )
{
    if ( !key )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::PutData() called with NULL key pointer!\n" );
    }
    if ( !rec )
    {
        fprintf ( stderr, "WARNING: RedBlackTree<T>::PutData() called with NULL data pointer!\n" );
    }
    if ( !key || !rec )
        return;
    insert ( key, rec );
}

template <class T>
    void RedBlackTree<T>::RemoveData ( const char *key )
{
    deleteNode ( key );
}

template <class T>
	BinaryNode<T> *RedBlackTree<T>::LookupTree ( const char *key )
{
    return findNode ( key );
}

template <class T>
    int RedBlackTree<T>::Size ()
{
    return ( int ) size ();
}

#endif
