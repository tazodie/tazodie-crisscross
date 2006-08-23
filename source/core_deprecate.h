/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net> and Rudolf Olah <omouse@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of Uplink Laboratories nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __included_deprecate_h
#    define __included_deprecate_h

#    define _DS_NO_DEPRECATE
//#define _DS_ONLY_DEPRECATE_SLOW

#    if defined(TARGET_OS_WINDOWS) && _MSC_VER >= 1300 && !defined(_DS_NO_DEPRECATE)
#        	if _MSC_FULL_VER >= 140050320
#        		define _DS_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
#        	else
#        		define _DS_DEPRECATE_TEXT(_Text) __declspec(deprecated)
#        	endif
#        ifndef _DS_SLOW_NO_DEPRECATE
#            	define _DS_DEPRECATE_SLOW						_DS_DEPRECATE_TEXT("This function will result in slow-executing code.")
#        else
#            	define _DS_DEPRECATE_SLOW
#        endif
#        ifndef _DS_ONLY_DEPRECATE_SLOW
#            	define _DS_DEPRECATE_CLASS(_Replacement)		_DS_DEPRECATE_TEXT("This class is deprecated and may be removed from future versions. Consider using '" #_Replacement "' instead.")
#            	define _DS_DEPRECATE_FUNCTION(_Replacement)		_DS_DEPRECATE_TEXT("This function is deprecated and may be removed from future versions. Consider using '" #_Replacement "' instead.")
#            	define _DS_DEPRECATE_FUNCTION_N					_DS_DEPRECATE_TEXT("This function is deprecated and may be removed from future versions.")
#        else
#            	define _DS_DEPRECATE_CLASS(_Replacement)
#            	define _DS_DEPRECATE_FUNCTION(_Replacement)
#            	define _DS_DEPRECATE_FUNCTION_N
#        endif
#    else
#        	define _DS_DEPRECATE_SLOW
#        	define _DS_DEPRECATE_CLASS(_Replacement)
#        	define _DS_DEPRECATE_FUNCTION(_Replacement)
#        	define _DS_DEPRECATE_FUNCTION_N
#    endif

#endif
