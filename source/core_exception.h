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

#ifndef __included_core_exception_h
#    define __included_core_exception_h

#    include "core_debug.h"

//! The core exception class.
/*!
	This class should be inherited by whatever exception needs
	to be created, but not thrown as an exception in itself.
*/
class CoreException
{
	//! The file in which the exception was thrown.
	const char *m_file;

	//! The line in CoreException::m_file at which the exception was thrown.
	int m_line;
  public:

	//! The constructor.
	/*!
	   \param _file The file in which the exception was thrown. (usually specified with __FILE__ by a macro)
	   \param _line The line in _file at which the exception was thrown. (usually specified with __LINE__ by a macro)
	 */
	  CoreException ( const char *_file, int _line ):m_file ( _file ),
		m_line ( _line )
	{
		g_stderr->WriteLine ( "=== STACK TRACE ===\n" );
		PrintStackTrace ( g_stderr );
	};

	//! The destructor.
	virtual ~ CoreException (  )
	{
	};

	//! Returns the file in which the exception was thrown.
	/*!
	   \return CoreException::m_file
	 */
	const char *ShowFile (  )
	{
		return m_file;
	};

	//! Returns the line in CoreException::m_file at which the exception was thrown.
	int ShowLine (  )
	{
		return m_line;
	};

	//! Returns the exception description.
	/*!
	   Should be replaced in any classes inheriting CoreException to properly
	   describe the exception conditions.
	   \return Exception description ("A core exception has occurred.")
	 */
	virtual const char *ShowReason (  ) const
	{
		return "A core exception has occurred.";
	};
};

//! The assertion failure exception.
class AssertionFailureException:public CoreException
{
  public:
	//! The constructor.
	/*!
	   \param _file The file in which the exception was thrown. (usually specified with __FILE__ by a macro)
	   \param _line The line in _file at which the exception was thrown. (usually specified with __LINE__ by a macro)
	 */
	AssertionFailureException ( const char *_file,
								int _line ):CoreException ( _file, _line )
	{
	};

	//! Returns the exception description.
	/*!
	   \return Exception description ("Assertion failure.")
	 */
	const char *ShowReason (  ) const
	{
		return "Assertion failure.";
	};
};

#endif
