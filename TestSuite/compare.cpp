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
#include "compare.h"
#include "testutils.h"

#include <crisscross/compare.h>

using namespace CrissCross;

int TestComparison_CString ()
{
	char *greaterString = strdup ( "beta" );
	char *lesserString = strdup ( "alpha" );
	char *dupLesserString = strdup ( lesserString );
	char * const constString = strdup ( dupLesserString );

	if ( Data::Compare ( lesserString, greaterString ) != -1 )
		return 1;

	if ( Data::Compare ( greaterString, lesserString ) != 1 )
		return 2;

	if ( Data::Compare ( lesserString, dupLesserString ) != 0 )
		return 3;

	if ( Data::Compare<char *> ( dupLesserString, constString ) != 0 )
		return 4;

	free ( (char *)constString );
	free ( dupLesserString );
	free ( lesserString );
	free ( greaterString );

	return 0;
}

int TestComparison_String ()
{
	std::string greaterString ( "beta" );
	std::string lesserString ( "alpha" );
	std::string dupLesserString ( lesserString );

	if ( Data::Compare ( lesserString, greaterString ) != -1 )
		return 1;

	if ( Data::Compare ( greaterString, lesserString ) != 1 )
		return 2;

	if ( Data::Compare ( lesserString, dupLesserString ) != 0 )
		return 3;

	return 0;
}

int TestComparison_Integer ()
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

int TestComparison_UnsignedInteger ()
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
