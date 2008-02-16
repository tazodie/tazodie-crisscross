/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>

#include <crisscross/hash.h>

namespace CrissCross
{
    namespace Crypto
    {
        Hash::Hash()
            : m_hashString(NULL)
        {
        }

        Hash::~Hash()
        {
        }
    }
}
