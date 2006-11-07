/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006 IO.IN Research
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list
 *       of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this
 *       list of conditions and the following disclaimer in the documentation and/or other
 *       materials provided with the distribution.
 *     * Neither the name of the I.O. Independent Network nor the names of its contributors
 *       may be used to endorse or promote products derived from this software without
 *       specific prior written permission.
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

#ifndef __included_core_debuglog_h
#define __included_core_debuglog_h

#ifdef ENABLE_DEBUGLOG

#include "datastructures/llist.h"
#include "core_debug.h"
#include "core_console.h"
#include "textwriter.h"

#include <iostream>
#include <time.h>

using namespace std;

namespace CrissCross
{
    namespace Debug
    {
        class CoreDebugLogData
        {
        public:
            tm *m_bug_time;
            int m_priority;
            CHAR *m_description;
        public:
            CoreDebugLogData ( tm *_bug_time, int _priority, CHAR *_description);
            ~CoreDebugLogData ();
        };

        //! The core debug logging class.
        class CoreDebugLog
        {
        private:
            //! If true, a log format similar to Apache Common Log Format will be used
            bool m_common_log_format;
            string m_app_name;
            string m_app_version;
            string m_app_website;
            string m_email;
            LList <CoreDebugLogData*> *m_reports;

        public:
            enum LogEntryPriority
            {
                BUG_LEVEL_INFO,       //!< Informational
                BUG_LEVEL_WARNING,    //!< Non-critical, but potentially threatening
                BUG_LEVEL_ERROR       //!< Critical failure
            };

            //! The default constructor.
            /*!
                Creates a new CoreDebugLog instance.
                \param _name Application name.
                \param _version Application version.
                \param _website Application website.
                \param _email Email to send debug logs to (if the log shows something abnormal).
                \param _common_log_format If true, a log format similar to the Apache Common Log
                Format will be used.
            */
            CoreDebugLog ( string _name, string _version,
                string _website, string _email,
                bool _common_log_format = true );
            //! The destructor.
            ~CoreDebugLog ( );

            //! Add a line of debug log information.
            /*!
                \param _priority Log line priority.
                \param _format The format of the string to be written.
            */
            void WriteLine ( CoreDebugLog::LogEntryPriority _priority, CONST CHAR *_format, ... );

            //! Adds a line of debug log information.
            /*!
                \param _priority Log line priority.
                \param _format The format of the string to be written.
            */
            void Write ( CoreDebugLog::LogEntryPriority _priority, CONST CHAR *_format, ... );

            //! Print the debug log to a buffer.
            /*!
                Writes the bug report to stdout along with colours.
                \param _output The buffer to write the debug log to.
                \param _lowest_priority The lowest priority of debug entries to be written.
            */
            void Print ( CrissCross::IO::CoreIO *_output,
                LogEntryPriority _lowest_priority = BUG_LEVEL_WARNING );

            //! Save the debug log.
            /*!
                Saves the debug log to a file with with the naming convention "<year>-<month>-<day>_<application version>.log".
            */
            void Save ( );

        protected:
            void Put ( CrissCross::IO::CoreIO *_stream, CoreDebugLog::LogEntryPriority _lowest_priority = BUG_LEVEL_WARNING );

        };

        //! Global CoreDebugLog variable initialized in universal_include.cpp
        extern CoreDebugLog *g_debuglog;
    }
}

#endif

#endif
