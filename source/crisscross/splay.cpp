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

#include <stdlib.h>

template <class T>
SplayTree<T>::SplayTree( )
{
    nullNode = new BinaryNode<T>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
}

template <class T>
SplayTree<T>::SplayTree( const SplayTree<T> & rhs )
{
    nullNode = new BinaryNode<T>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
    *this = rhs;
}

template <class T>
SplayTree<T>::~SplayTree( )
{
    makeEmpty( );
    delete nullNode;
}

template <class T>
int SplayTree<T>::insert( const char *key, const T & x )
{
    static BinaryNode<T> *newNode = NULL;

    if( newNode == NULL )
        newNode = new BinaryNode<T>;
    newNode->key = strdup ( key );
    newNode->element = x;

    if( root == nullNode )
    {
        newNode->left = newNode->right = nullNode;
        root = newNode;
    }
    else
    {
        splay( key, root );
        if( strcmp(key, root->key) < 0 )
        {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullNode;
            root = newNode;
        }
        else
        if( strcmp ( root->key, key ) < 0 )
        {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullNode;
            root = newNode;
        }
        else
            return 1;
    }
    newNode = NULL;   // So next insert will call new
    return 0;
}

template <class T>
int SplayTree<T>::remove( const char *key, bool deleteData )
{
    BinaryNode<T> *newTree;

    // If key is found, it will be at the root
    splay( key, root );
    if( strcmp ( root->key, key ) != 0 )
        return 1;

	if( root == nullNode )
		return 1;

    if( root->left == nullNode )
        newTree = root->right;
    else
    {
          // Find the maximum in the left subtree
          // Splay it to the root; and then attach right child
        newTree = root->left;
        splay( key, newTree );
        newTree->right = root->right;
    }
    free ( (char*)root->key );
	if ( deleteData )
		delete root->element;
    delete root;
    root = newTree;
    return 0;
}

template <class T>
T SplayTree<T>::elementAt( BinaryNode<T> *t ) const
{
    return t == NULL ? NULL : t->element;
}

template <class T>
const char *SplayTree<T>::findMin( )
{
    if( isEmpty( ) )
        return elementAt( NULL );

    BinaryNode<T> *ptr = root;

    while( ptr->left != nullNode )
        ptr = ptr->left;

    splay( ptr->element, root );
    return root->key;
}

template <class T>
const char *SplayTree<T>::findMax( )
{
    if( isEmpty( ) )
        return NULL;

    BinaryNode<T> *ptr = root;

    while( ptr->right != nullNode )
        ptr = ptr->right;

    splay( ptr->key, root );
    return root->key;
}

template <class T>
T SplayTree<T>::find( char *key )
{
    splay( key, root );
    if( isEmpty( ) || strcmp ( root->key, key ) != 0 )
        return elementAt( NULL );

    return elementAt( root );
}

template <class T>
void SplayTree<T>::makeEmpty( bool deleteData )
{
    findMax( );
    while( !isEmpty( ) )
        remove( root->key, deleteData );
}

template <class T>
bool SplayTree<T>::isEmpty( ) const
{
    return root == nullNode;
}

template <class T>
const SplayTree<T> &SplayTree<T> :: operator=( const SplayTree<T> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }

    return *this;
}

template <class T>
void SplayTree<T>::splay( const char *key, BinaryNode<T> * & t ) const
{
    BinaryNode<T> *leftTreeMax, *rightTreeMin;
    static BinaryNode<T> header;

    header.left = header.right = nullNode;
    leftTreeMax = rightTreeMin = &header;

    nullNode->key = (char *)key;   // Guarantee a match

    for( ; ; )
        if( strcmp ( key, t->key ) < 0 )
        {
            if( strcmp ( key, t->left->key ) < 0 )
                rotateWithLeftChild( t );
            if( t->left == nullNode )
                break;
              // Link Right
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        }
        else if( strcmp ( t->key, key ) < 0 )
        {
            if( strcmp ( t->right->key, key ) < 0 )
                rotateWithRightChild( t );
            if( t->right == nullNode )
                break;
              // Link Left
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        }
        else
            break;

    leftTreeMax->right = t->left;
    rightTreeMin->left = t->right;
    t->left = header.right;
    t->right = header.left;
}


template <class T>
void SplayTree<T>::rotateWithLeftChild( BinaryNode<T> * & k2 ) const
{
    BinaryNode<T> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

template <class T>
void SplayTree<T>::rotateWithRightChild( BinaryNode<T> * & k1 ) const
{
    BinaryNode<T> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

template <class T>
void SplayTree<T>::reclaimMemory( BinaryNode<T> * t ) const
{
    if( t != t->left )
    {
        reclaimMemory( t->left );
        reclaimMemory( t->right );
        free ( t->key );
        delete t;
    }
}

template <class T>
BinaryNode<T> *SplayTree<T>::clone( BinaryNode<T> * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new BinaryNode<T>( t->element, clone( t->left ), clone( t->right ) );
}
