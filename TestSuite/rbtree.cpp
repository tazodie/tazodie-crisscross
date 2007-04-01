#include "rbtree.h"
#include "testutils.h"

#include <crisscross/rbtree.h>

using namespace CrissCross::Data;

int TestRedBlackTree()
{
	RedBlackTree<char *> *rbtree = new RedBlackTree<char *>();
	BinaryNode<char *> *node = NULL;
	char *ptr = NULL;
	
	rbtree->insert ( "first", newStr ("one") );
	rbtree->insert ( "second", newStr ("two") );
	rbtree->insert ( "third", newStr ("three") );
	rbtree->insert ( "fourth", newStr ("four") );
	
	if ( (node = rbtree->findNode ( "FiRSt" ) ) == NULL )
		return 1;

	if ( strcmp ( node->data, "one" ) != 0 )
		return 2;

	if ( (node = rbtree->findNode ( "fifth" ) ) != NULL )
		return 3;

	if ( (node = rbtree->findNode ( "SeCoND" ) ) == NULL )
		return 4;

	if ( strcmp ( node->data, "two" ) != 0 )
		return 5;
		
	if ( rbtree->deleteNode ("fifth") == STATUS_OK )
		return 6;
	
	if ( (ptr = rbtree->find ( "first")) == NULL )
		return 7;
	else
		delete [] ptr;
	
	if ( rbtree->deleteNode ("first") != STATUS_OK )
		return 8;
	
	if ( (ptr = rbtree->find ( "second")) == NULL )
		return 9;
	else
		delete [] ptr;
	
	if ( rbtree->deleteNode ("second") != STATUS_OK )
		return 10;
	
	if ( (ptr = rbtree->find ( "third")) == NULL )
		return 11;
	else
		delete [] ptr;
	
	if ( rbtree->deleteNode ("third") != STATUS_OK )
		return 12;
	
	if ( (ptr = rbtree->find ( "fourth")) == NULL )
		return 13;
	else
		delete [] ptr;
	
	if ( rbtree->deleteNode ("fourth") != STATUS_OK )
		return 14;

	delete rbtree;
	return 0;
}