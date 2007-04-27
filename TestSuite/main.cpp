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
#include "sort.h"
#include "stopwatch.h"

using namespace CrissCross;

CrissCross::IO::CoreConsole *g_console;

int RunApplication (int argc, char **argv) {
	
	g_console = new IO::CoreConsole();
	g_console->WriteLine ( "CrissCross Test Suite v" CC_LIB_VERSION );
	g_console->WriteLine ();
    
	int retval = 0;
	
    g_console->WriteLine ( "Testing pass/fail detection." );
	WritePrefix ( "Pass" ); retval = WriteResult ( TestPass() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "Fail" ); retval = WriteResult ( TestFail() ); g_console->Flush(); CoreAssert ( retval == 0 );
    
    g_console->WriteLine ( "Entering CrissCross test phase." );
	WritePrefix ( "DataBuffer Compare" ); retval = WriteResult ( TestComparison_DataBuffer() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "Integer Compare" ); retval = WriteResult ( TestComparison_Integer() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "Unsigned Integer Compare" ); retval = WriteResult ( TestComparison_UnsignedInteger() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "LList" ); retval = WriteResult ( TestLList() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "DArray" ); retval = WriteResult ( TestDArray() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "DStack" ); retval = WriteResult ( TestDStack() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "RedBlackTree" ); retval = WriteResult ( TestRedBlackTree() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "HeapSort (integer array)" ); retval = WriteResult ( TestHeapSort_IntArray() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "HeapSort (integer DArray)" ); retval = WriteResult ( TestHeapSort_DArray() ); g_console->Flush(); CoreAssert ( retval == 0 );
	WritePrefix ( "Stopwatch" ); retval = WriteResult ( TestStopwatch() ); g_console->Flush(); CoreAssert ( retval == 0 );

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

	delete g_console;

	return 0;
}
