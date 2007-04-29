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

#ifndef __included_tree_h
#define __included_tree_h

template <class Key, class Data>
class BinaryNode
{
public:
    char        beenThere;
    char        color;
    Key			id;
    Data        data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;

    BinaryNode( ) : id (), left( NULL ), right( NULL ), parent ( NULL ) { }

    BinaryNode( const Key &theKey, const Data &theElement, BinaryNode *pt, BinaryNode *lt, BinaryNode *rt )
      : data ( theElement ), id ( theKey), left( lt ), right( rt ), parent ( pt ) { }
};

#include <crisscross/rbtree.h>
#include <crisscross/splay.h>

#endif
