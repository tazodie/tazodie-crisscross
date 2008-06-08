
#include "header.h"

#include "datatypes.h"

int TestDatatypes_Uint8 ()
{
	if ( sizeof ( cc_uint8_t ) * 8 != 8 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint16 ()
{
	if ( sizeof ( cc_uint16_t ) * 8 != 16 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint32 ()
{
	if ( sizeof ( cc_uint32_t ) * 8 != 32 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Uint64 ()
{
	if ( sizeof ( cc_uint64_t ) * 8 != 64 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Ulong ()
{
	if ( sizeof ( cc_ulong_t ) * 8 != TARGET_CPU_BITS )
		return 1;
	else
		return 0;
}

int TestDatatypes_Bool ()
{
	if ( sizeof ( cc_bool_t ) * 8 != 8 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Float ()
{
	if ( sizeof ( cc_float32_t ) * 8 != 32 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Double ()
{
	if ( sizeof ( cc_float64_t ) * 8 != 64 )
		return 1;
	else
		return 0;
}

int TestDatatypes_Pointer ()
{
	if ( sizeof ( cc_ptr_t ) * 8 != TARGET_CPU_BITS )
		return 1;

	if ( sizeof ( cc_ptr_t ) != sizeof ( cc_ulong_t ) )
		return 2;

	return 0;
}
