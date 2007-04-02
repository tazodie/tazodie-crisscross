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

using namespace CrissCross;

void WritePrefix ( const char *_prefix )
{
	char temp[128];
	sprintf ( temp, "Testing %s...", _prefix );
	while ( strlen(temp) < 58 )
		strcat ( temp, " " );
	g_console->Write ( temp );
}

void WriteResult ( int _result )
{
	g_console->Write ( "[ " );
	if ( _result )
	{
		g_console->SetColour ( IO::CoreConsole::FG_RED | IO::CoreConsole::FG_INTENSITY );
		g_console->Write ( "FAILED" );
	} else {
		g_console->SetColour ( IO::CoreConsole::FG_GREEN | IO::CoreConsole::FG_INTENSITY );
		g_console->Write ( "PASSED" );
	}
	g_console->SetColour();
	g_console->WriteLine ( " ]" );
	
	if ( _result )
	{
		g_console->WriteLine ( "\ton internal test number %d\n", _result );
	}
}

char *newStr ( const char *_string )
{
	char *retval = new char[strlen(_string) + 1];
	strcpy ( retval, _string );
	return retval;
}
