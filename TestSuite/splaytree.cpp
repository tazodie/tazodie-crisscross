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
#include "splaytree.h"
#include "testutils.h"

#include <crisscross/splaytree.h>

using namespace CrissCross::Data;

int TestSplayTree_CString()
{
    SplayTree<const char *, const char *> *splaytree = new SplayTree<const char *, const char *>();
    char *tmp;

	if ( splaytree->size() != 0 )
		return 1;
    
    // If the tree is properly encapsulated, this won't cause an error on test #1.
    tmp = strdup ( "first" );
    splaytree->insert ( tmp, "one" );
    free ( tmp ); tmp = NULL;

	if ( splaytree->size() != 1 )
		return 2;
    
    splaytree->insert ( "second", "two" );
    splaytree->insert ( "third", "three" );
    splaytree->insert ( "fourth", "four" );

	if ( splaytree->size() != 4 )
		return 3;
    
    const char *res = NULL;
    if ( !splaytree->find ( "first", res ) )
        return 4;

    const char *tmp1 = "one";
    if ( Compare ( res, tmp1 ) != 0 )
        return 5;

    if ( splaytree->exists ( "fifth" ) )
        return 6;

    if ( !splaytree->exists ( "second" ) )
        return 7;

    if ( !splaytree->find ( "second", res ) )
        return 7;

    tmp1 = "two";
    if ( Compare ( res, tmp1 ) != 0 )
        return 8;
        
    if ( splaytree->erase ( "fifth" ) )
        return 9;

	if ( splaytree->size() != 4 )
		return 10;
    
    if ( !splaytree->exists ( "first" ) )
        return 11;
    
    if ( !splaytree->erase ( "first" ) )
        return 12;
	
	if ( splaytree->size() != 3 )
		return 13;
    
    if ( !splaytree->find ( "second", res ) )
        return 14;
    
    if ( !splaytree->erase ( "second" ) )
        return 15;
    
    if ( !splaytree->exists ( "third" ) )
        return 16;
    
    if ( !splaytree->erase ( "third" ) )
        return 17;
    
    if ( !splaytree->exists ( "fourth" ) )
        return 18;
    
    if ( !splaytree->erase ( "fourth" ) )
        return 19;

	if ( splaytree->size() != 0 )
		return 20;

    delete splaytree;
    return 0;
}

int TestSplayTree_String()
{
    SplayTree<std::string,std::string> *splaytree = new SplayTree<std::string,std::string>();
    
	if ( splaytree->size() != 0 )
		return 1;

    splaytree->insert ( "first", "one" );
    splaytree->insert ( "second", "two" );
    splaytree->insert ( "third", "three" );
    splaytree->insert ( "fourth", "four" );

    std::string res;
    
	if ( splaytree->size() != 4 )
		return 2;
    
    if ( !splaytree->find ( "first", res ) )
        return 3;

    if ( res != "one" )
        return 4;

    if ( splaytree->exists ( "fifth" ) )
        return 5;

    if ( !splaytree->find ( "second", res ) )
        return 6;

    if ( res != "two" )
        return 7;
        
    if ( splaytree->erase ( "fifth" ) )
        return 8;

	if ( splaytree->size() != 4 )
		return 9;
    
    if ( !splaytree->exists ( "first" ) )
        return 10;
    
    if ( !splaytree->erase ( "first" ) )
        return 11;

	if ( splaytree->size() != 3 )
		return 12;
    
    if ( !splaytree->exists ( "second" ) )
        return 13;
    
    if ( !splaytree->erase ( "second" ) )
        return 14;

	if ( splaytree->size() != 2 )
		return 15;
    
    if ( !splaytree->exists ( "third" ) )
        return 16;
    
    if ( !splaytree->erase ( "third" ) )
        return 17;

	if ( splaytree->size() != 1 )
		return 18;
    
    if ( !splaytree->exists ( "fourth" ) )
        return 19;
    
    if ( !splaytree->erase ("fourth" ) )
        return 20;

	if ( splaytree->size() != 0 )
		return 21;

    delete splaytree;
    return 0;
}

int TestSplayTree_Int()
{
    SplayTree<int,int> *splaytree = new SplayTree<int,int>();

	if ( splaytree->size() != 0 )
		return 1;
    
    splaytree->insert ( 1, 1 );
    splaytree->insert ( 2, 2 );
    splaytree->insert ( 3, 3 );
    splaytree->insert ( 4, 4 );

    int res;
	if ( splaytree->size() != 4 )
		return 2;
    
    if ( !splaytree->find ( 1, res ) )
        return 3;

    if ( res != 1 )
        return 4;

    if ( splaytree->exists ( 5 ) )
        return 5;

    if ( !splaytree->find ( 2, res ) )
        return 6;

    if ( res != 2 )
        return 7;
        
    if ( splaytree->erase ( 5 ) )
        return 8;

	if ( splaytree->size() != 4 )
		return 9;
    
    if ( !splaytree->exists ( 1 ) )
        return 10;
    
    if ( !splaytree->erase ( 1 ) )
        return 11;

	if ( splaytree->size() != 3 )
		return 12;
    
    if ( !splaytree->exists ( 2 ) )
        return 13;
    
    if ( !splaytree->erase ( 2 ) )
        return 14;

	if ( splaytree->size() != 2 )
		return 15;
    
    if ( !splaytree->exists ( 3 ) )
        return 16;
    
    if ( !splaytree->erase ( 3 ) )
        return 17;

	if ( splaytree->size() != 1 )
		return 18;
    
    if ( !splaytree->exists ( 4 ) )
        return 19;
    
    if ( !splaytree->erase ( 4 ) )
        return 20;

	if ( splaytree->size() != 0 )
		return 21;

    delete splaytree;
    return 0;
}

