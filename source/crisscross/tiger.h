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

#ifndef __included_cc_tiger_h
#define __included_cc_tiger_h

#include <crisscross/deprecate.h>
#include <crisscross/hash.h>

namespace CrissCross
{
    namespace Crypto
    {
        class TigerHash : public Hash
        {
        private:
            cc_uint64_t m_hash[3];

        public:
		#if TARGET_CPU_BITS < 64
			_CC_DEPRECATE_SLOW("MODERATE")
		#endif
            TigerHash();
            virtual ~TigerHash();

            int Process ( const void *_data, size_t _length );
            void Reset();
            virtual const char *ToString () const;

        };
    }
}

#endif
