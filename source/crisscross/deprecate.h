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

#ifndef __included_cc_deprecate_h
#define __included_cc_deprecate_h

// TODO: Comment this line to re-add deprecation for release builds.
#   define _CC_NO_DEPRECATE
//#   define _CC_ONLY_DEPRECATE_SLOW

#    if defined(TARGET_COMPILER_GCC)
#        if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#            define _CC_DEPRECATE_TEXT(_Text)  __attribute__((__deprecated__))
#        endif
#    elif defined(TARGET_COMPILER_VC)
#       if _MSC_FULL_VER >= 140050320
#           define _CC_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
#       else
#           define _CC_DEPRECATE_TEXT(_Text) __declspec(deprecated)
#       endif
#    else
#        define _CC_DEPRECATE_TEXT(_Text)
#    endif

#   if !defined(_CC_NO_DEPRECATE)
#       ifndef _CC_SLOW_NO_DEPRECATE
#           define _CC_DEPRECATE_SLOW                       _CC_DEPRECATE_TEXT("This function will result in slow-executing code.")
#       else
#           define _CC_DEPRECATE_SLOW
#       endif
#       ifndef _CC_ONLY_DEPRECATE_SLOW
#           define _CC_DEPRECATE_CLASS(_Replacement)        _CC_DEPRECATE_TEXT("This class is deprecated and may be removed from future versions. Consider using '" #_Replacement "' instead.")
#           define _CC_DEPRECATE_FUNCTION(_Replacement)     _CC_DEPRECATE_TEXT("This function is deprecated and may be removed from future versions. Consider using '" #_Replacement "' instead.")
#           define _CC_DEPRECATE_FUNCTION_N                 _CC_DEPRECATE_TEXT("This function is deprecated and may be removed from future versions.")
#       else
#           define _CC_DEPRECATE_CLASS(_Replacement)
#           define _CC_DEPRECATE_FUNCTION(_Replacement)
#           define _CC_DEPRECATE_FUNCTION_N
#       endif
#   else
#       define _CC_DEPRECATE_SLOW
#       define _CC_DEPRECATE_CLASS(_Replacement)
#       define _CC_DEPRECATE_FUNCTION(_Replacement)
#       define _CC_DEPRECATE_FUNCTION_N
#   endif
#endif
