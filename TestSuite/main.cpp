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
#include "testutils.h"

#include "pass.h"
#include "fail.h"

#include "compare.h"
#include "darray.h"
#include "dstack.h"
#include "llist.h"
#include "rbtree.h"
#include "splay.h"
#include "sort.h"
#include "stopwatch.h"

using namespace CrissCross;

CrissCross::IO::CoreConsole *g_console;

int RunApplication (int argc, char **argv) {
	
	g_console = new IO::CoreConsole();
	g_console->WriteLine ( "CrissCross Test Suite v" CC_LIB_VERSION );
	g_console->WriteLine ();
    
	int retval = 0;

	WritePrefix ( "DataBuffer Compare" ); retval &= WriteResult ( TestComparison_DataBuffer() );
	WritePrefix ( "Integer Compare" ); retval &= WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); retval &= WriteResult ( TestComparison_UnsignedInteger() );
	WritePrefix ( "LList" ); retval &= WriteResult ( TestLList() );
	WritePrefix ( "DArray" ); retval &= WriteResult ( TestDArray() );
	WritePrefix ( "DStack" ); retval &= WriteResult ( TestDStack() );

	WritePrefix ( "RedBlackTree<DataBuffer, DataBuffer *>" ); retval &= WriteResult ( TestRedBlackTree_DataBuffer() );
	WritePrefix ( "RedBlackTree<std::string, std::string>" ); retval &= WriteResult ( TestRedBlackTree_stdstring() );
	WritePrefix ( "RedBlackTree<int, int>" ); retval &= WriteResult ( TestRedBlackTree_Int() );

	WritePrefix ( "SplayTree<DataBuffer, DataBuffer *>" ); retval &= WriteResult ( TestSplayTree_DataBuffer() );
	WritePrefix ( "SplayTree<std::string, std::string>" ); retval &= WriteResult ( TestSplayTree_stdstring() );
	WritePrefix ( "SplayTree<int, int>" ); retval &= WriteResult ( TestSplayTree_Int() );

	WritePrefix ( "HeapSort (integer array)" ); retval &= WriteResult ( TestHeapSort_IntArray() );
	WritePrefix ( "HeapSort (integer DArray)" ); retval &= WriteResult ( TestHeapSort_DArray() );

	WritePrefix ( "Stopwatch" ); retval &= WriteResult ( TestStopwatch() );
	g_console->Flush(); CoreAssert ( retval == 0 );

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

	delete g_console;

	return 0;
}
