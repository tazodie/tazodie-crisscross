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
#include "rbtree.h"
#include "splaytree.h"
#include "hashtable.h"
#include "llist.h"
#include "darray.h"

using namespace CrissCross::IO;
using namespace std;

Console *console = NULL;

int RunApplication ( int argc, char **argv )
{
	console = new Console ();

	// Begin your application here.

	ProfileAVLTree ();
	ProfileRedBlackTree ();
	ProfileSplayTree ();
#ifndef TARGET_OS_NDSFIRMWARE
	ProfileHashTable ();
#endif
	ProfileLList ();
	ProfileDArray ();

	// End your application here.

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

	delete console;
	return 0;
}
