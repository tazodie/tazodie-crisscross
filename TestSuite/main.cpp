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
#include "datatypes.h"
#include "darray.h"
#include "dstack.h"
#include "llist.h"
#include "rbtree.h"
#include "heapsort.h"
#include "quicksort.h"
#include "combsort.h"
#include "stopwatch.h"

using namespace CrissCross;

CrissCross::IO::Console *g_console;

int RunApplication (int argc, char **argv) {
	
	g_console = new IO::Console();
    
    g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
	g_console->WriteLine ( "CrissCross Test Suite v" CC_LIB_VERSION );
    g_console->SetColour ();
	g_console->WriteLine ();

    g_console->WriteLine ( "Compiled with CrissCross  v%d.%d.%d build %d",
        CC_LIB_VERSION_MAJOR, CC_LIB_VERSION_MINOR, CC_LIB_VERSION_REVISION, CC_LIB_VERSION_BUILD );
    g_console->WriteLine ( "Running with CrissCross   v%d.%d.%d build %d",
        Version::Major(), Version::Minor(), Version::Revision(), Version::Build() );
	g_console->WriteLine ();
    
	int retval = 0;

	WritePrefix ( "Size of Uint8" ); retval |= WriteResult ( TestDatatypes_Uint8() );
	WritePrefix ( "Size of Uint16" ); retval |= WriteResult ( TestDatatypes_Uint16() );
	WritePrefix ( "Size of Uint32" ); retval |= WriteResult ( TestDatatypes_Uint32() );
	WritePrefix ( "Size of Uint64" ); retval |= WriteResult ( TestDatatypes_Uint64() );
	WritePrefix ( "Size of Bool" ); retval |= WriteResult ( TestDatatypes_Bool() );
	WritePrefix ( "Size of Float" ); retval |= WriteResult ( TestDatatypes_Float() );
	WritePrefix ( "Size of Double" ); retval |= WriteResult ( TestDatatypes_Double() );
	WritePrefix ( "Size of void *" ); retval |= WriteResult ( TestDatatypes_Pointer() );

	WritePrefix ( "Stopwatch" ); retval |= WriteResult ( TestStopwatch() );

    //WritePrefix ( "char* Compare" ); retval |= WriteResult ( TestComparison_CString() );
    WritePrefix ( "std::string Compare" ); retval |= WriteResult ( TestComparison_String() );
	WritePrefix ( "Integer Compare" ); retval |= WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); retval |= WriteResult ( TestComparison_UnsignedInteger() );

	WritePrefix ( "LList" ); retval |= WriteResult ( TestLList() );
	WritePrefix ( "DArray" ); retval |= WriteResult ( TestDArray() );
	WritePrefix ( "DStack" ); retval |= WriteResult ( TestDStack() );

	WritePrefix ( "RedBlackTree<std::string, std::string>" ); retval |= WriteResult ( TestRedBlackTree_String() );
	WritePrefix ( "RedBlackTree<int, int>" ); retval |= WriteResult ( TestRedBlackTree_Int() );

	WritePrefix ( "CombSort (integer array)" ); retval |= WriteResult ( TestCombSort_IntArray() );
	WritePrefix ( "CombSort (integer DArray)" ); retval |= WriteResult ( TestCombSort_DArray() );

	WritePrefix ( "HeapSort (integer array)" ); retval |= WriteResult ( TestHeapSort_IntArray() );
	WritePrefix ( "HeapSort (integer DArray)" ); retval |= WriteResult ( TestHeapSort_DArray() );

	WritePrefix ( "QuickSort (integer array)" ); retval |= WriteResult ( TestQuickSort_IntArray() );
	WritePrefix ( "QuickSort (integer DArray)" ); retval |= WriteResult ( TestQuickSort_DArray() );


	if ( retval == 0 )
	{
		g_console->WriteLine ();
		g_console->WriteLine ( "All tests passed." );
		g_console->WriteLine ();
	}

	g_console->Flush();

    CoreAssert ( retval == 0 );

	delete g_console;

    return 0;
}
