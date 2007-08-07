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

#include "header.h"
#include "rbtree.h"
#include "testutils.h"

#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

int TestRedBlackTree_CString()
{
    RedBlackTree<const char *, const char *> *rbtree = new RedBlackTree<const char *, const char *>();
    BinaryNode<const char *, const char *> *node = NULL;
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
    
    if ( (node = rbtree->findNode ( "first" ) ) == NULL )
        return 4;

    const char *tmp1 = "one";
    if ( Compare ( node->data, tmp1 ) != 0 )
        return 5;

    if ( (node = rbtree->findNode ( "fifth" ) ) != NULL )
        return 6;

    if ( (node = rbtree->findNode ( "second" ) ) == NULL )
        return 7;

    tmp1 = "two";
    if ( Compare ( node->data, tmp1 ) != 0 )
        return 8;
        
    if ( rbtree->erase ( "fifth" ) == STATUS_OK )
        return 9;

	if ( rbtree->size() != 4 )
		return 10;
    
    if ( rbtree->find ( "first" ) == NULL )
        return 11;
    
    if ( rbtree->erase ( "first" ) != STATUS_OK )
        return 12;
	
	if ( rbtree->size() != 3 )
		return 13;
    
    if ( rbtree->find ( "second" ) == NULL )
        return 14;
    
    if ( rbtree->erase ( "second" ) != STATUS_OK )
        return 15;
    
    if ( rbtree->find ( "third" ) == NULL )
        return 16;
    
    if ( rbtree->erase ( "third" ) != STATUS_OK )
        return 17;
    
    if ( rbtree->find ( "fourth" ) == NULL )
        return 18;
    
    if ( rbtree->erase ( "fourth" ) != STATUS_OK )
        return 19;

	if ( rbtree->size() != 0 )
		return 20;

    delete rbtree;
    return 0;
}

int TestRedBlackTree_String()
{
    RedBlackTree<std::string,std::string> *rbtree = new RedBlackTree<std::string,std::string>();
    BinaryNode<std::string,std::string> *node = NULL;
    
	if ( rbtree->size() != 0 )
		return 1;

    rbtree->insert ( "first", "one" );
    rbtree->insert ( "second", "two" );
    rbtree->insert ( "third", "three" );
    rbtree->insert ( "fourth", "four" );

	if ( rbtree->size() != 4 )
		return 2;
    
    if ( ( node = rbtree->findNode ( "first" ) ) == NULL )
        return 3;

    if ( node->data != "one" )
        return 4;

    if ( ( node = rbtree->findNode ( "fifth" ) ) != NULL )
        return 5;

    if ( ( node = rbtree->findNode ( "second" ) ) == NULL )
        return 6;

    if ( node->data != "two" )
        return 7;
        
    if ( rbtree->erase ("fifth") == STATUS_OK )
        return 8;

	if ( rbtree->size() != 4 )
		return 9;
    
    if ( rbtree->find ( "first") == "" )
        return 10;
    
    if ( rbtree->erase ("first") != STATUS_OK )
        return 11;

	if ( rbtree->size() != 3 )
		return 12;
    
    if ( rbtree->find ( "second") == "" )
        return 13;
    
    if ( rbtree->erase ("second") != STATUS_OK )
        return 14;

	if ( rbtree->size() != 2 )
		return 15;
    
    if ( rbtree->find ( "third") == "" )
        return 16;
    
    if ( rbtree->erase ("third") != STATUS_OK )
        return 17;

	if ( rbtree->size() != 1 )
		return 18;
    
    if ( rbtree->find ( "fourth") == "" )
        return 19;
    
    if ( rbtree->erase ("fourth") != STATUS_OK )
        return 20;

	if ( rbtree->size() != 0 )
		return 21;

    delete rbtree;
    return 0;
}

int TestRedBlackTree_Int()
{
    RedBlackTree<int,int> *rbtree = new RedBlackTree<int,int>();
    BinaryNode<int,int> *node = NULL;

	if ( rbtree->size() != 0 )
		return 1;
    
    rbtree->insert ( 1, 1 );
    rbtree->insert ( 2, 2 );
    rbtree->insert ( 3, 3 );
    rbtree->insert ( 4, 4 );

	if ( rbtree->size() != 4 )
		return 2;
    
    if ( (node = rbtree->findNode ( 1 ) ) == NULL )
        return 3;

    if ( node->data != 1 )
        return 4;

    if ( (node = rbtree->findNode ( 5 ) ) != NULL )
        return 5;

    if ( (node = rbtree->findNode ( 2 ) ) == NULL )
        return 6;

    if ( node->data != 2 )
        return 7;
        
    if ( rbtree->erase ( 5 ) == STATUS_OK )
        return 8;

	if ( rbtree->size() != 4 )
		return 9;
    
    if ( !rbtree->find ( 1 ) )
        return 10;
    
    if ( rbtree->erase ( 1 ) != STATUS_OK )
        return 11;

	if ( rbtree->size() != 3 )
		return 12;
    
    if ( !rbtree->find ( 2 ) )
        return 13;
    
    if ( rbtree->erase ( 2 ) != STATUS_OK )
        return 14;

	if ( rbtree->size() != 2 )
		return 15;
    
    if ( !rbtree->find ( 3 ) )
        return 16;
    
    if ( rbtree->erase ( 3 ) != STATUS_OK )
        return 17;

	if ( rbtree->size() != 1 )
		return 18;
    
    if ( !rbtree->find ( 4 ) )
        return 19;
    
    if ( rbtree->erase ( 4 ) != STATUS_OK )
        return 20;

	if ( rbtree->size() != 0 )
		return 21;

    delete rbtree;
    return 0;
}

