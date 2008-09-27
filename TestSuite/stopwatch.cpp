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
#include "stopwatch.h"

#include <crisscross/stopwatch.h>

using namespace CrissCross;

int TestStopwatch()
{
	System::Stopwatch  sw1;
	sw1.Start();
	sw1.Stop();
	if (!(sw1.Elapsed() < 1.0 && sw1.Elapsed() > -1.0))
		return 1;

	System::Stopwatch *sw2 = new System::Stopwatch();
	if (!sw2) return 2;

	sw2->Start();
	sw2->Stop();
	if (!(sw2->Elapsed() < 1.0 && sw2->Elapsed() > -1.0))
		return 3;

	delete sw2;

	return 0;
}
