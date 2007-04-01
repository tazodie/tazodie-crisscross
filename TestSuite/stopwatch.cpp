#include "stopwatch.h"

#include <crisscross/stopwatch.h>

using namespace CrissCross;

int TestStopwatch()
{
	System::Stopwatch sw1;
	sw1.Start();
	sw1.Stop();
	if ( !(sw1.Elapsed() < 1 && sw1.Elapsed() > -1) )
		return 1;

	System::Stopwatch *sw2 = new System::Stopwatch();
	if ( !sw2 ) return 2;
	sw2->Start();
	sw2->Stop();
	if ( !(sw2->Elapsed() < 1 && sw2->Elapsed() > -1 ) )
		return 3;
	delete sw2;

	return 0;
}
