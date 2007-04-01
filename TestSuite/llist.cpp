#include "llist.h"
#include "testutils.h"

#include <crisscross/llist.h>

int TestLList()
{
	LList<char *> *llist = new LList<char *>();
	llist->insert ( newStr("one") );
	llist->insert ( newStr("two") );
	llist->insert ( newStr("three") );
	llist->insert ( newStr("four") );
	
	if ( strcmp ( llist->getData(0), "one" ) != 0 )
		return 1;

	if ( strcmp ( llist->getData(2), "three" ) != 0 )
		return 2;

	if ( strcmp ( llist->getData(3), "four" ) != 0 )
		return 3;

	if ( strcmp ( llist->getData(1), "two" ) != 0 )
		return 4;

	delete [] llist->getData(1);
	llist->remove ( 1 );
	
	if ( strcmp ( llist->getData(0), "one" ) != 0 )
		return 5;

	if ( strcmp ( llist->getData(1), "three" ) != 0 )
		return 6;

	if ( strcmp ( llist->getData(2), "four" ) != 0 )
		return 7;	
	
	while ( llist->validIndex(0) )
	{
		delete [] llist->getData(0);
		llist->remove(0);
	}
	delete llist;

	return 0;
}