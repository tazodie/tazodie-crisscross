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
	RedBlackTree<char *, char*> *rbtree = new RedBlackTree<char *, char*>();
	BinaryNode<char *, char*> *node = NULL;
    char *tmp;
	
    // If the tree is properly encapsulated, this won't cause an error on test #1.
    tmp = strdup ( "first" );
	rbtree->insert ( tmp, "one" );
    free ( tmp ); tmp = NULL;
    
	rbtree->insert ( "second", "two" );
	rbtree->insert ( "third", "three" );
	rbtree->insert ( "fourth", "four" );
	
	if ( (node = rbtree->findNode ( "first" ) ) == NULL )
		return 1;

    tmp = "one";
	if ( Compare ( node->data, tmp ) != 0 )
		return 2;

	if ( (node = rbtree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = rbtree->findNode ( "second" ) ) == NULL )
		return 4;

    tmp = "two";
	if ( Compare ( node->data, tmp ) != 0 )
		return 5;
		
	if ( rbtree->erase ( "fifth" ) == STATUS_OK )
		return 6;
	
	if ( rbtree->find ( "first" ) == NULL )
		return 7;
	
	if ( rbtree->erase ( "first" ) != STATUS_OK )
		return 8;
	
    if ( rbtree->find ( "second" ) == NULL )
		return 9;
	
	if ( rbtree->erase ( "second" ) != STATUS_OK )
		return 10;
	
	if ( rbtree->find ( "third" ) == NULL )
		return 11;
	
	if ( rbtree->erase ( "third" ) != STATUS_OK )
		return 12;
	
	if ( rbtree->find ( "fourth" ) == NULL )
		return 13;
	
	if ( rbtree->erase ( "fourth" ) != STATUS_OK )
		return 14;

	delete rbtree;
	return 0;
}

int TestRedBlackTree_String()
{
	RedBlackTree<std::string,std::string> *rbtree = new RedBlackTree<std::string,std::string>();
	BinaryNode<std::string,std::string> *node = NULL;
	
	rbtree->insert ( "first", "one" );
	rbtree->insert ( "second", "two" );
	rbtree->insert ( "third", "three" );
	rbtree->insert ( "fourth", "four" );
	
	if ( (node = rbtree->findNode ( "first" ) ) == NULL )
		return 1;

	if ( node->data != "one" )
		return 2;

	if ( (node = rbtree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = rbtree->findNode ( "second" ) ) == NULL )
		return 4;

	if ( node->data != "two" )
		return 5;
		
	if ( rbtree->erase ("fifth") == STATUS_OK )
		return 6;
	
	if ( rbtree->find ( "first") == "" )
		return 7;
	
	if ( rbtree->erase ("first") != STATUS_OK )
		return 8;
	
	if ( rbtree->find ( "second") == "" )
		return 9;
	
	if ( rbtree->erase ("second") != STATUS_OK )
		return 10;
	
	if ( rbtree->find ( "third") == "" )
		return 11;
	
	if ( rbtree->erase ("third") != STATUS_OK )
		return 12;
	
	if ( rbtree->find ( "fourth") == "" )
		return 13;
	
	if ( rbtree->erase ("fourth") != STATUS_OK )
		return 14;

	delete rbtree;
	return 0;
}

int TestRedBlackTree_Int()
{
	RedBlackTree<int,int> *rbtree = new RedBlackTree<int,int>();
	BinaryNode<int,int> *node = NULL;
	
	rbtree->insert ( 1, 1 );
	rbtree->insert ( 2, 2 );
	rbtree->insert ( 3, 3 );
	rbtree->insert ( 4, 4 );
	
	if ( (node = rbtree->findNode ( 1 ) ) == NULL )
		return 1;

	if ( node->data != 1 )
		return 2;

	if ( (node = rbtree->findNode ( 5 ) ) != NULL )
		return 3;

	if ( (node = rbtree->findNode ( 2 ) ) == NULL )
		return 4;

	if ( node->data != 2 )
		return 5;
		
	if ( rbtree->erase ( 5 ) == STATUS_OK )
		return 6;
	
	if ( !rbtree->find ( 1 ) )
		return 7;
	
	if ( rbtree->erase ( 1 ) != STATUS_OK )
		return 8;
	
	if ( !rbtree->find ( 2 ) )
		return 9;
	
	if ( rbtree->erase ( 2 ) != STATUS_OK )
		return 10;
	
	if ( !rbtree->find ( 3 ) )
		return 11;
	
	if ( rbtree->erase ( 3 ) != STATUS_OK )
		return 12;
	
	if ( !rbtree->find ( 4 ) )
		return 13;
	
	if ( rbtree->erase ( 4 ) != STATUS_OK )
		return 14;

	delete rbtree;
	return 0;
}

