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

#include <crisscross/databuffer.h>
#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

int TestRedBlackTree_DataBuffer()
{
	RedBlackTree<DataBuffer,DataBuffer*> *rbtree = new RedBlackTree<DataBuffer,DataBuffer*>();
	BinaryNode<DataBuffer,DataBuffer*> *node = NULL;
	DataBuffer *buffer = NULL;
	
	rbtree->insert ( "first", new DataBuffer ("one") );
	rbtree->insert ( "second", new DataBuffer ("two") );
	rbtree->insert ( "third", new DataBuffer ("three") );
	rbtree->insert ( "fourth", new DataBuffer ("four") );
	
	if ( (node = rbtree->findNode ( "FiRSt" ) ) == NULL )
		return 1;

	if ( *node->data != "one" )
		return 2;

	if ( (node = rbtree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = rbtree->findNode ( "SeCoND" ) ) == NULL )
		return 4;

	if ( *node->data != "two" )
		return 5;
		
	if ( rbtree->erase ("fifth") == STATUS_OK )
		return 6;
	
	if ( ( buffer = rbtree->find ( "first") ) == NULL )
		return 7;
	else
		delete buffer;
	
	if ( rbtree->erase ("first") != STATUS_OK )
		return 8;
	
	if ( ( buffer = rbtree->find ( "second") ) == NULL )
		return 9;
	else
		delete buffer;
	
	if ( rbtree->erase ("second") != STATUS_OK )
		return 10;
	
	if ( ( buffer = rbtree->find ( "third") ) == NULL )
		return 11;
	else
		delete buffer;
	
	if ( rbtree->erase ("third") != STATUS_OK )
		return 12;
	
	if ( ( buffer = rbtree->find ( "fourth") ) == NULL )
		return 13;
	else
		delete buffer;
	
	if ( rbtree->erase ("fourth") != STATUS_OK )
		return 14;

	delete rbtree;
	return 0;
}

int TestRedBlackTree_stdstring()
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

