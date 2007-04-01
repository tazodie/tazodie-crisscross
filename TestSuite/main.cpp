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
#include "compare.h"
#include "stopwatch.h"
#include "llist.h"
#include "rbtree.h"
#include "sort.h"

using namespace CrissCross;

CrissCross::IO::CoreConsole *g_console;

int RunApplication (int argc, char **argv) {
	g_console = new IO::CoreConsole();
	g_console->WriteLine ( "CrissCross Test Suite v" APP_VERSION );
	g_console->WriteLine ();
	WritePrefix ( "DataBuffer Compare" ); WriteResult ( TestComparison_DataBuffer() );
	WritePrefix ( "Integer Compare" ); WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); WriteResult ( TestComparison_UnsignedInteger() );
	WritePrefix ( "LList" ); WriteResult ( TestLList() );
	WritePrefix ( "RedBlackTree" ); WriteResult ( TestRedBlackTree() );
	WritePrefix ( "HeapSort" ); WriteResult ( TestHeapSort() );
	WritePrefix ( "Stopwatch" ); WriteResult ( TestStopwatch() );
	delete g_console;
    return 0;
}
