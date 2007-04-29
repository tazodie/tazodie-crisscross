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
#include "splay.h"
#include "testutils.h"

#include <crisscross/core_databuffer.h>
#include <crisscross/splay.h>

using namespace CrissCross::Data;

int TestSplayTree_DataBuffer()
{
	SplayTree<DataBuffer,DataBuffer*> *stree = new SplayTree<DataBuffer,DataBuffer*>();
	BinaryNode<DataBuffer,DataBuffer*> *node = NULL;
	DataBuffer *buffer = NULL;
	
	stree->insert ( "first", new DataBuffer ("one") );
	stree->insert ( "second", new DataBuffer ("two") );
	stree->insert ( "third", new DataBuffer ("three") );
	stree->insert ( "fourth", new DataBuffer ("four") );
	
	if ( (node = stree->findNode ( "FiRSt" ) ) == NULL )
		return 1;

	if ( *node->data != "one" )
		return 2;

	if ( (node = stree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = stree->findNode ( "SeCoND" ) ) == NULL )
		return 4;

	if ( *node->data != "two" )
		return 5;
		
	if ( stree->remove ("fifth") == STATUS_OK )
		return 6;
	
	if ( ( buffer = stree->find ( "first") ) == NULL )
		return 7;
	else
		delete buffer;
	
	if ( stree->remove ("first") != STATUS_OK )
		return 8;
	
	if ( ( buffer = stree->find ( "second") ) == NULL )
		return 9;
	else
		delete buffer;
	
	if ( stree->remove ("second") != STATUS_OK )
		return 10;
	
	if ( ( buffer = stree->find ( "third") ) == NULL )
		return 11;
	else
		delete buffer;
	
	if ( stree->remove ("third") != STATUS_OK )
		return 12;
	
	if ( ( buffer = stree->find ( "fourth") ) == NULL )
		return 13;
	else
		delete buffer;
	
	if ( stree->remove ("fourth") != STATUS_OK )
		return 14;

	delete stree;
	return 0;
}

int TestSplayTree_stdstring()
{
	SplayTree<std::string,std::string> *stree = new SplayTree<std::string,std::string>();
	BinaryNode<std::string,std::string> *node = NULL;
	
	stree->insert ( "first", "one" );
	stree->insert ( "second", "two" );
	stree->insert ( "third", "three" );
	stree->insert ( "fourth", "four" );
	
	if ( (node = stree->findNode ( "first" ) ) == NULL )
		return 1;

	if ( node->data != "one" )
		return 2;

	if ( (node = stree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = stree->findNode ( "second" ) ) == NULL )
		return 4;

	if ( node->data != "two" )
		return 5;
		
	if ( stree->remove ("fifth") == STATUS_OK )
		return 6;
	
	if ( stree->find ( "first") == "" )
		return 7;
	
	if ( stree->remove ("first") != STATUS_OK )
		return 8;
	
	if ( stree->find ( "second") == "" )
		return 9;
	
	if ( stree->remove ("second") != STATUS_OK )
		return 10;
	
	if ( stree->find ( "third") == "" )
		return 11;
	
	if ( stree->remove ("third") != STATUS_OK )
		return 12;
	
	if ( stree->find ( "fourth") == "" )
		return 13;
	
	if ( stree->remove ("fourth") != STATUS_OK )
		return 14;

	delete stree;
	return 0;
}

int TestSplayTree_Int()
{
	SplayTree<int,int> *stree = new SplayTree<int,int>();
	BinaryNode<int,int> *node = NULL;
	
	stree->insert ( 1, 1 );
	stree->insert ( 2, 2 );
	stree->insert ( 3, 3 );
	stree->insert ( 4, 4 );
	
	if ( (node = stree->findNode ( 1 ) ) == NULL )
		return 1;

	if ( node->data != 1 )
		return 2;

	if ( (node = stree->findNode ( 5 ) ) != NULL )
		return 3;

	if ( (node = stree->findNode ( 2 ) ) == NULL )
		return 4;

	if ( node->data != 2 )
		return 5;
		
	if ( stree->remove ( 5 ) == STATUS_OK )
		return 6;
	
	if ( stree->find ( 1 ) == NULL )
		return 7;
	
	if ( stree->remove ( 1 ) != STATUS_OK )
		return 8;
	
	if ( stree->find ( 2 ) == NULL )
		return 9;
	
	if ( stree->remove ( 2 ) != STATUS_OK )
		return 10;
	
	if ( stree->find ( 3 ) == NULL )
		return 11;
	
	if ( stree->remove ( 3 ) != STATUS_OK )
		return 12;
	
	if ( stree->find ( 4 ) == NULL )
		return 13;
	
	if ( stree->remove ( 4 ) != STATUS_OK )
		return 14;

	delete stree;
	return 0;
}

