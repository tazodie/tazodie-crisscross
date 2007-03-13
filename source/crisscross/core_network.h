/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#ifndef __included_core_network_h
#define __included_core_network_h

#include <crisscross/core_error.h>

namespace CrissCross
{
    namespace Network
    {
        // Undocumented for a reason. Don't call them.
        CrissCross::Errors __initialise_network();
        CrissCross::Errors __cleanup_network();
    }
}

#endif
