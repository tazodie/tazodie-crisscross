/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include "header.h"
#include "rbtree.h"
#include "testutils.h"

#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

int TestRedBlackTree_CString()
{
    RedBlackTree<const char *, const char *> *rbtree = new RedBlackTree<const char *, const char *>();
    char *tmp;

	if ( rbtree->size() != 0 )
		return 1;
    
    // If the tree is properly encapsulated, this won't cause an error on test #1.
    tmp = strdup ( "first" );
    rbtree->insert ( tmp, "one" );
    free ( tmp ); tmp = NULL;

	if ( rbtree->size() != 1 )
		return 2;
    
    rbtree->insert ( "second", "two" );
    rbtree->insert ( "third", "three" );
    rbtree->insert ( "fourth", "four" );

	if ( rbtree->size() != 4 )
		return 3;
    
    const char *res = NULL;
    if ( !rbtree->find ( "first", res ) )
        return 4;

    const char *tmp1 = "one";
    if ( Compare ( res, tmp1 ) != 0 )
        return 5;

    if ( rbtree->exists ( "fifth" ) )
        return 6;

    if ( !rbtree->exists ( "second" ) )
        return 7;

    if ( !rbtree->find ( "second", res ) )
        return 7;

    tmp1 = "two";
    if ( Compare ( res, tmp1 ) != 0 )
        return 8;
        
    if ( rbtree->erase ( "fifth" ) )
        return 9;

	if ( rbtree->size() != 4 )
		return 10;
    
    if ( !rbtree->exists ( "first" ) )
        return 11;
    
    if ( !rbtree->erase ( "first" ) )
        return 12;
	
	if ( rbtree->size() != 3 )
		return 13;
    
    if ( !rbtree->find ( "second", res ) )
        return 14;
    
    if ( !rbtree->erase ( "second" ) )
        return 15;
    
    if ( !rbtree->exists ( "third" ) )
        return 16;
    
    if ( !rbtree->erase ( "third" ) )
        return 17;
    
    if ( !rbtree->exists ( "fourth" ) )
        return 18;
    
    if ( !rbtree->erase ( "fourth" ) )
        return 19;

	if ( rbtree->size() != 0 )
		return 20;

    delete rbtree;
    return 0;
}

int TestRedBlackTree_String()
{
    RedBlackTree<std::string,std::string> *rbtree = new RedBlackTree<std::string,std::string>();
    
	if ( rbtree->size() != 0 )
		return 1;

    rbtree->insert ( "first", "one" );
    rbtree->insert ( "second", "two" );
    rbtree->insert ( "third", "three" );
    rbtree->insert ( "fourth", "four" );

    std::string res;
    
	if ( rbtree->size() != 4 )
		return 2;
    
    if ( !rbtree->find ( "first", res ) )
        return 3;

    if ( res != "one" )
        return 4;

    if ( rbtree->exists ( "fifth" ) )
        return 5;

    if ( !rbtree->find ( "second", res ) )
        return 6;

    if ( res != "two" )
        return 7;
        
    if ( rbtree->erase ( "fifth" ) )
        return 8;

	if ( rbtree->size() != 4 )
		return 9;
    
    if ( !rbtree->exists ( "first" ) )
        return 10;
    
    if ( !rbtree->erase ( "first" ) )
        return 11;

	if ( rbtree->size() != 3 )
		return 12;
    
    if ( !rbtree->exists ( "second" ) )
        return 13;
    
    if ( !rbtree->erase ( "second" ) )
        return 14;

	if ( rbtree->size() != 2 )
		return 15;
    
    if ( !rbtree->exists ( "third" ) )
        return 16;
    
    if ( !rbtree->erase ( "third" ) )
        return 17;

	if ( rbtree->size() != 1 )
		return 18;
    
    if ( !rbtree->exists ( "fourth" ) )
        return 19;
    
    if ( !rbtree->erase ("fourth" ) )
        return 20;

	if ( rbtree->size() != 0 )
		return 21;

    delete rbtree;
    return 0;
}

int TestRedBlackTree_Int()
{
    RedBlackTree<int,int> *rbtree = new RedBlackTree<int,int>();

	if ( rbtree->size() != 0 )
		return 1;
    
    rbtree->insert ( 1, 1 );
    rbtree->insert ( 2, 2 );
    rbtree->insert ( 3, 3 );
    rbtree->insert ( 4, 4 );

    int res;
	if ( rbtree->size() != 4 )
		return 2;
    
    if ( !rbtree->find ( 1, res ) )
        return 3;

    if ( res != 1 )
        return 4;

    if ( rbtree->exists ( 5 ) )
        return 5;

    if ( !rbtree->find ( 2, res ) )
        return 6;

    if ( res != 2 )
        return 7;
        
    if ( rbtree->erase ( 5 ) )
        return 8;

	if ( rbtree->size() != 4 )
		return 9;
    
    if ( !rbtree->exists ( 1 ) )
        return 10;
    
    if ( !rbtree->erase ( 1 ) )
        return 11;

	if ( rbtree->size() != 3 )
		return 12;
    
    if ( !rbtree->exists ( 2 ) )
        return 13;
    
    if ( !rbtree->erase ( 2 ) )
        return 14;

	if ( rbtree->size() != 2 )
		return 15;
    
    if ( !rbtree->exists ( 3 ) )
        return 16;
    
    if ( !rbtree->erase ( 3 ) )
        return 17;

	if ( rbtree->size() != 1 )
		return 18;
    
    if ( !rbtree->exists ( 4 ) )
        return 19;
    
    if ( !rbtree->erase ( 4 ) )
        return 20;

	if ( rbtree->size() != 0 )
		return 21;

    delete rbtree;
    return 0;
}

