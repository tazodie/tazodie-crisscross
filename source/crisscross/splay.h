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

#ifndef __included_splay_h
#define __included_splay_h

#include <crisscross/tree.h>

template <class Key, class Data>
class SplayTree
{
  public:
    SplayTree( );
    SplayTree( const SplayTree & rhs );
    ~SplayTree( );
    Data find( const Key &key );
    BinaryNode<Key,Data> *findNode( const Key &key );
    bool isEmpty( ) const;

    void makeEmpty();
    int insert( const Key &key, const Data &x );
    int remove( const Key &key );

    const SplayTree & operator=( const SplayTree & rhs );

    const Key &findMin( );
    const Key &findMax( );

  private:
    BinaryNode<Key,Data> *root;
    BinaryNode<Key,Data> *nullNode;

    Data elementAt( BinaryNode<Key,Data> *t ) const;

    void reclaimMemory( BinaryNode<Key,Data> * t ) const;
    void printTree( BinaryNode<Key,Data> *t ) const;
    BinaryNode<Key,Data> * clone( BinaryNode<Key,Data> *t ) const;

    // Tree manipulations
    void rotateWithLeftChild( BinaryNode<Key,Data> * & k2 ) const;
    void rotateWithRightChild( BinaryNode<Key,Data> * & k1 ) const;
    void splay( const Key &key, BinaryNode<Key,Data> * & t ) const;
};

#include "splay.cpp"

#endif
