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
#include "avltree.h"
#include "testutils.h"

#include <crisscross/avltree.h>

using namespace CrissCross::Data;

int TestAVLTree_CString()
{
    AVLTree<const char *, const char *> *avltree = new AVLTree<const char *, const char *>();
    char *tmp;

	if ( avltree->size() != 0 )
		return 1;
    
    // If the tree is properly encapsulated, this won't cause an error on test #1.
    tmp = strdup ( "first" );
    avltree->insert ( tmp, "one" );
    free ( tmp ); tmp = NULL;

	if ( avltree->size() != 1 )
		return 2;
    
    avltree->insert ( "second", "two" );
    avltree->insert ( "third", "three" );
    avltree->insert ( "fourth", "four" );

	if ( avltree->size() != 4 )
		return 3;
    
    const char *tmp1 = "one", *tmp2 = NULL;
    if ( !avltree->find ( "first", tmp2 ) )
        return 4;

    if ( Compare ( tmp2, tmp1 ) != 0 )
        return 5;

    if ( avltree->exists ( "fifth" ) )
        return 6;

    if ( !avltree->find ( "second", tmp2 ) )
        return 7;

    tmp1 = "two";
    if ( Compare ( tmp2, tmp1 ) != 0 )
        return 8;
        
    if ( avltree->erase ( "fifth" ) )
        return 9;

	if ( avltree->size() != 4 )
		return 10;
    
    if ( !avltree->exists ( "first" ) )
        return 11;
    
    if ( !avltree->erase ( "first" ) )
        return 12;
	
	if ( avltree->size() != 3 )
		return 13;
    
    if ( !avltree->exists ( "second" ) )
        return 14;
    
    if ( !avltree->erase ( "second" ) )
        return 15;
    
    if ( !avltree->exists ( "third" ) )
        return 16;
    
    if ( !avltree->erase ( "third" ) )
        return 17;
    
    if ( !avltree->exists ( "fourth" ) )
        return 18;
    
    if ( !avltree->erase ( "fourth" ) )
        return 19;

	if ( avltree->size() != 0 )
		return 20;

    delete avltree;
    return 0;
}

int TestAVLTree_String()
{
    AVLTree<std::string,std::string> *avltree = new AVLTree<std::string,std::string>();
    
	if ( avltree->size() != 0 )
		return 1;

    avltree->insert ( "first", "one" );
    avltree->insert ( "second", "two" );
    avltree->insert ( "third", "three" );
    avltree->insert ( "fourth", "four" );

	if ( avltree->size() != 4 )
		return 2;
    
	std::string tmp;
    if ( !avltree->find ( "first", tmp ) )
        return 3;

    if ( tmp != "one" )
        return 4;

    if ( avltree->exists ( "fifth" ) )
        return 5;

    if ( !avltree->find ( "second", tmp ) )
        return 6;

    if ( tmp != "two" )
        return 7;
        
    if ( avltree->erase ( "fifth" ) )
        return 8;

	if ( avltree->size() != 4 )
		return 9;
    
	avltree->find ( "first", tmp );
    if ( tmp == "" )
        return 10;
    
    if ( !avltree->erase ( "first" ) )
        return 11;

	if ( avltree->size() != 3 )
		return 12;
    
	avltree->find ( "second", tmp );
    if ( tmp == "" )
        return 13;
    
    if ( !avltree->erase ( "second" ) )
        return 14;

	if ( avltree->size() != 2 )
		return 15;
    
	avltree->find ( "third", tmp );
    if ( tmp == "" )
        return 16;
    
    if ( !avltree->erase ( "third" ) )
        return 17;

	if ( avltree->size() != 1 )
		return 18;
    
	avltree->find ( "fourth", tmp );
    if ( tmp == "" )
        return 19;
    
    if ( !avltree->erase ( "fourth" ) )
        return 20;

	if ( avltree->size() != 0 )
		return 21;

    delete avltree;
    return 0;
}

int TestAVLTree_Int()
{
    AVLTree<int,int> *avltree = new AVLTree<int,int>();

	if ( avltree->size() != 0 )
		return 1;
    
    avltree->insert ( 1, 1 );
    avltree->insert ( 2, 2 );
    avltree->insert ( 3, 3 );
    avltree->insert ( 4, 4 );

	int tmp;
	if ( avltree->size() != 4 )
		return 2;
    
    if ( !avltree->find ( 1, tmp ) )
        return 3;

    if ( tmp != 1 )
        return 4;

    if ( avltree->exists ( 5 ) )
        return 5;

    if ( !avltree->find ( 2, tmp ) )
        return 6;

    if ( tmp != 2 )
        return 7;
        
    if ( avltree->erase ( 5 ) )
        return 8;

	if ( avltree->size() != 4 )
		return 9;
    
    if ( !avltree->exists ( 1 ) )
        return 10;
    
    if ( !avltree->erase ( 1 ) )
        return 11;

	if ( avltree->size() != 3 )
		return 12;
    
    if ( !avltree->exists ( 2 ) )
        return 13;
    
    if ( !avltree->erase ( 2 ) )
        return 14;

	if ( avltree->size() != 2 )
		return 15;
    
    if ( !avltree->exists ( 3 ) )
        return 16;
    
    if ( !avltree->erase ( 3 ) )
        return 17;

	if ( avltree->size() != 1 )
		return 18;
    
    if ( !avltree->exists ( 4 ) )
        return 19;
    
    if ( !avltree->erase ( 4 ) )
        return 20;

	if ( avltree->size() != 0 )
		return 21;

    delete avltree;
    return 0;
}

