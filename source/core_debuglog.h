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

#ifndef __included_core_debuglog_h
#define __included_core_debuglog_h

#ifdef ENABLE_DEBUGLOG

#include "datastructures/llist.h"
#include "core_debug.h"
#include "core_exception.h"
#include "core_console.h"
#include "textwriter.h"

#include <iostream>
#include <time.h>

using namespace std;

class CoreDebugLogData
{
    public:
    tm *bug_time;
    int priority;
    string description;
    CoreDebugLogData () { bug_time = 0; };
    ~CoreDebugLogData () { description.clear (); }
};

    //! The core debug logging class.
class CoreDebugLog
{
private:
    //! If true, a log format similar to Apache Common Log Format will be used
    bool common_log_format;
    string app_name;
    string app_version;
    string app_website;
    string email;
    LList <CoreDebugLogData*> *reports;

public:
    enum BugReportPriority
    {
        BUG_LEVEL_INFO,       //!< Informational
        BUG_LEVEL_WARNING,    //!< Non-critical, but potentially threatening
        BUG_LEVEL_ERROR       //!< Critical failure
    };

    //! The default constructor.
    /*! Creates a new bug report object.
        \param name Application name.
        \param version Application version.
        \param website Application website.
        \param email Email to send bug reports to.
        \param common_log_format If true, a log format similar to the Apache Common Log
        Format will be used.
    */
    CoreDebugLog ( string name, string version,
        string website, string email,
        bool common_log_format = true );
    //! The destructor.
    ~CoreDebugLog ( );

    //! Adds a line of bug report information.
    /*! Adds a line of bug report information.
        \param line Bug report line.
        \param priority Bug priority.
    */
    void AddInfo ( string line, CoreDebugLog::BugReportPriority priority = BUG_LEVEL_WARNING );

    //! Print the bug report.
    /*! Prints the bug report to stdout along with colours.
        \param lowest_priority The lowest priority of bug information that will be printed.
    */
    void PrintLog ( CoreDebugLog::BugReportPriority lowest_priority = BUG_LEVEL_WARNING );

    //! Save the bug report.
    /*! Saves the bug report to a file named "year-month-day_application_version.log".
        Returns true if successful.
    */
    void SaveLog ( );
};

//! Global CoreDebugLog variable defined in universal_include.cpp
extern CoreDebugLog *debuglog;

#endif

#endif
