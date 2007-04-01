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

#include <crisscross/universal_include.h>

#include "testutils.h"
#include "compare.h"
#include "llist.h"

using namespace CrissCross;

CrissCross::IO::CoreConsole *g_console;

int RunApplication (int argc, char **argv) {
	g_console = new IO::CoreConsole();
	g_console->WriteLine ( "CrissCross Test Suite v" APP_VERSION );
	g_console->WriteLine ();
	g_console->WriteLine ( "Running CrissCross::Data::Compare tests..." );
	WritePrefix ( "DataBuffer Compare" ); WriteResult ( TestComparison_DataBuffer() );
	WritePrefix ( "Integer Compare" ); WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); WriteResult ( TestComparison_UnsignedInteger() );
	g_console->WriteLine ( "Running CrissCross::Data::LList tests..." );
	WritePrefix ( "LList" ); WriteResult ( TestLList() );
    return 0;
}
