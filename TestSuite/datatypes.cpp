
#include "header.h"

#include "datatypes.h"

int TestDatatypes_Uint8()
{
	if ( sizeof ( unsigned char ) != 1 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint16()
{
	if ( sizeof ( unsigned short ) != 2 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint32()
{
	if ( sizeof ( unsigned int ) != 4 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint64()
{
	if ( sizeof ( unsigned long long ) != 8 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Bool()
{
	if ( sizeof ( bool ) != 1 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Float()
{
	if ( sizeof ( float ) != 4 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Double()
{
	if ( sizeof ( double ) != 8 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Pointer()
{
	if ( sizeof ( void* ) != TARGET_CPU_BITS / 8 )
		return 1;
	else
		return 0;
}

