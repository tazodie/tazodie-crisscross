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

template <class T>
class SplayTree
{
  public:
    SplayTree( );
    SplayTree( const SplayTree & rhs );
    ~SplayTree( );
    T find( char *key );
    bool isEmpty( ) const;

    void makeEmpty( bool deleteData = false );
    int insert( const char *key, const T & x );
    int remove( const char *key, bool deleteData = false );

    const SplayTree & operator=( const SplayTree & rhs );

    const char *findMin( );
    const char *findMax( );

  private:
    BinaryNode<T> *root;
    BinaryNode<T> *nullNode;

    T elementAt( BinaryNode<T> *t ) const;

    void reclaimMemory( BinaryNode<T> * t ) const;
    void printTree( BinaryNode<T> *t ) const;
    BinaryNode<T> * clone( BinaryNode<T> *t ) const;

    // Tree manipulations
    void rotateWithLeftChild( BinaryNode<T> * & k2 ) const;
    void rotateWithRightChild( BinaryNode<T> * & k1 ) const;
    void splay( const char *key, BinaryNode<T> * & t ) const;
};

#include "splay.cpp"

#endif
