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

template <class Key, class Data>
SplayTree<Key,Data>::SplayTree( )
{
    nullNode = new BinaryNode<Key,Data>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
}

template <class Key, class Data>
SplayTree<Key,Data>::SplayTree( const SplayTree<Key,Data> & rhs )
{
    nullNode = new BinaryNode<Key,Data>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
    *this = rhs;
}

template <class Key, class Data>
SplayTree<Key,Data>::~SplayTree( )
{
    makeEmpty( );
    delete nullNode;
}

template <class Key, class Data>
int SplayTree<Key,Data>::insert( const Key &key, const Data &x )
{
    static BinaryNode<Key,Data> *newNode = NULL;

    if( newNode == NULL )
        newNode = new BinaryNode<Key,Data>;
    newNode->id = key;
    newNode->data = x;

    if( root == nullNode )
    {
        newNode->left = newNode->right = nullNode;
        root = newNode;
    }
    else
    {
        splay( key, root );
        if ( key < root->id )
        {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullNode;
            root = newNode;
        }
        else
        if ( root->id < key )
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

template <class Key, class Data>
int SplayTree<Key,Data>::remove( const Key &key )
{
    BinaryNode<Key,Data> *newTree;

    // If key is found, it will be at the root
    splay( key, root );
    if( root->id != key )
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

    delete root;
    root = newTree;

    return 0;
}

template <class Key, class Data>
Data SplayTree<Key,Data>::elementAt( BinaryNode<Key,Data> *t ) const
{
    return t == NULL ? NULL : t->data;
}

template <class Key, class Data>
const Key &SplayTree<Key,Data>::findMin( )
{
    if( isEmpty( ) )
        return elementAt( NULL );

    BinaryNode<Key,Data> *ptr = root;

    while( ptr->left != nullNode )
        ptr = ptr->left;

    splay( ptr->id, root );
    return root->id;
}

template <class Key, class Data>
const Key &SplayTree<Key,Data>::findMax( )
{
    BinaryNode<Key,Data> *ptr = root;

    while( ptr->right != nullNode )
        ptr = ptr->right;

    splay( ptr->id, root );
    return root->id;
}

template <class Key, class Data>
Data SplayTree<Key,Data>::find( const Key &key )
{
    splay( key, root );

    if ( isEmpty( ) || root->id != key )
        return elementAt( NULL );

    return elementAt( root );
}

template <class Key, class Data>
BinaryNode<Key,Data> *SplayTree<Key,Data>::findNode( const Key &key )
{
    splay( key, root );

    if ( isEmpty( ) || root->id != key )
        return NULL;

    return root;
}

template <class Key, class Data>
void SplayTree<Key,Data>::makeEmpty ()
{
    findMax( );
    while( !isEmpty( ) )
        remove( root->id );
}

template <class Key, class Data>
bool SplayTree<Key,Data>::isEmpty( ) const
{
    return root == nullNode;
}

template <class Key, class Data>
const SplayTree<Key,Data> &SplayTree<Key,Data> :: operator=( const SplayTree<Key,Data> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }

    return *this;
}

template <class Key, class Data>
void SplayTree<Key,Data>::splay( const Key &key, BinaryNode<Key,Data> * & t ) const
{
    BinaryNode<Key,Data> *leftTreeMax, *rightTreeMin;
    static BinaryNode<Key,Data> header;

    header.left = header.right = nullNode;
    leftTreeMax = rightTreeMin = &header;

    nullNode->id = key;   // Guarantee a match

    for( ; ; )
        if ( key < t->id )
        {
            if ( key < t->left->id )
                rotateWithLeftChild( t );
            if ( t->left == nullNode )
                break;
              // Link Right
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        }
        else if ( t->id < key  )
        {
            if ( t->right->id < key )
                rotateWithRightChild( t );
            if ( t->right == nullNode )
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


template <class Key, class Data>
void SplayTree<Key,Data>::rotateWithLeftChild( BinaryNode<Key,Data> * & k2 ) const
{
    BinaryNode<Key,Data> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

template <class Key, class Data>
void SplayTree<Key,Data>::rotateWithRightChild( BinaryNode<Key,Data> * & k1 ) const
{
    BinaryNode<Key,Data> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

template <class Key, class Data>
void SplayTree<Key,Data>::reclaimMemory( BinaryNode<Key,Data> * t ) const
{
    if( t != t->left )
    {
        reclaimMemory( t->left );
        reclaimMemory( t->right );
        free ( t->key );
        delete t;
    }
}

template <class Key, class Data>
BinaryNode<Key,Data> *SplayTree<Key,Data>::clone( BinaryNode<Key,Data> * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new BinaryNode<Key,Data>( t->element, clone( t->left ), clone( t->right ) );
}
