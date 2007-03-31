#include <crisscross/universal_include.h>

#include <crisscross/compare.h>
#include <crisscross/core_console.h>
#include <crisscross/core_databuffer.h>

using namespace CrissCross;

IO::CoreConsole console;

int TestComparison_DataBuffer();
int TestComparison_Integer();
int TestComparison_UnsignedInteger();

void WriteResult ( int _result );
void WritePrefix ( const char *_prefix ); 

int RunApplication (int argc, char **argv) {
	console.WriteLine ( "CrissCross Test Suite v" APP_VERSION );
	console.WriteLine ();
	console.WriteLine ( "Running CrissCross::Data::Compare tests..." );
	WritePrefix ( "DataBuffer Compare" ); WriteResult ( TestComparison_DataBuffer() );
	WritePrefix ( "Integer Compare" ); WriteResult ( TestComparison_Integer() );
	WritePrefix ( "Unsigned Integer Compare" ); WriteResult ( TestComparison_UnsignedInteger() );
    return 0;
}

int TestComparison_DataBuffer()
{	
	Data::DataBuffer greaterString("beta");
	Data::DataBuffer lesserString("alpha");
	Data::DataBuffer dupLesserString(lesserString);
	
	if ( Data::Compare ( lesserString, greaterString ) != -1 )
		return 1;
	
	if ( Data::Compare ( greaterString, lesserString ) != 1 )
		return 2;
	
	if ( Data::Compare ( lesserString, dupLesserString ) != 0 )
		return 3;
	
	return 0;
}

int TestComparison_Integer()
{	
	int greaterInt = 200;
	int lesserInt = -200;
	int dupLesserInt = lesserInt;
	
	if ( Data::Compare ( lesserInt, greaterInt ) != -1 )
		return 1;
	
	if ( Data::Compare ( greaterInt, lesserInt ) != 1 )
		return 2;
	
	if ( Data::Compare ( lesserInt, dupLesserInt ) != 0 )
		return 3;
	
	return 0;
}
int TestComparison_UnsignedInteger()
{	
	unsigned int greaterInt = 200;
	unsigned int lesserInt = 100;
	unsigned int dupLesserInt = lesserInt;
	
	if ( Data::Compare ( lesserInt, greaterInt ) != -1 )
		return 1;
	
	if ( Data::Compare ( greaterInt, lesserInt ) != 1 )
		return 2;
	
	if ( Data::Compare ( lesserInt, dupLesserInt ) != 0 )
		return 3;
	
	return 0;
}

void WritePrefix ( const char *_prefix )
{
	console.Write ( "Testing %s... ", _prefix );
}

void WriteResult ( int _result )
{
	console.Write ( "[ " );
	if ( _result )
	{
		console.SetColour ( IO::CoreConsole::FG_RED | IO::CoreConsole::FG_INTENSITY );
		console.Write ( "FAILED" );
	} else {
		console.SetColour ( IO::CoreConsole::FG_GREEN | IO::CoreConsole::FG_INTENSITY );
		console.Write ( "PASSED" );
	}
	console.SetColour();
	console.WriteLine ( " ]" );
	
	if ( _result )
	{
		console.WriteLine ( "\ton internal test number %d\n", _result );
	}
}