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

using namespace CrissCross::Text;
using namespace CrissCross::Text::XML;
using namespace CrissCross::IO;
using namespace CrissCross::System;

int
RunApplication ( int argc, char **argv )
{
    Console *console = new Console ();

    // Begin your application here.

	XMLParser xml;
	xml.parse ( "example.xml" );

    // End your application here.

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

    delete console;

    return 0;
}
