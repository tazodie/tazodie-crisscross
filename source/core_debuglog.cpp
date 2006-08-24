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

#include "universal_include.h"
#include "core_debuglog.h"

#ifdef ENABLE_DEBUGLOG

CoreDebugLog::CoreDebugLog ( string name, string version,
                             string website, string email,
                             bool common_log_format )
{
    this->common_log_format = common_log_format;
    app_name = name;
    app_version = version;
    app_website = website;
    this->email = email;
    reports = new LList <CoreDebugLogData*> ( );
}

CoreDebugLog::~CoreDebugLog ( )
{
    for ( int i = 0; reports->ValidIndex ( i ); i++ )
        delete reports->GetData ( i );
    delete reports;
}

void
CoreDebugLog::AddInfo ( string desc, CoreDebugLog::BugReportPriority priority )
{
    CoreAssert ( this );
    CoreDebugLogData *report = new CoreDebugLogData ( );
    time_t temp;
    time ( &temp );
    report->bug_time = localtime ( &temp );
    report->priority = priority;
    report->description = desc;
    reports->PutDataAtEnd ( report );
}

void
CoreDebugLog::PrintLog ( CoreDebugLog::BugReportPriority lowest_priority )
{
    CoreAssert ( this );
    CoreDebugLogData *current;
    g_stdout->Write ( "%s %s - Website at <%s>\nEmail <%s> with Bug Reports\n",
    app_name.c_str ( ), app_version.c_str ( ),
    app_website.c_str ( ), email.c_str ( ) );
    for ( int i = 0; reports->ValidIndex ( i ) ; i++ )
    {
        current = reports->GetData ( i );
        if ( current->priority < lowest_priority )
        continue;
        switch ( current->priority )
        {
            case BUG_LEVEL_ERROR:
                g_stdout->SetColour ( g_stdout->FG_RED | g_stdout->FG_INTENSITY ); break;
            case BUG_LEVEL_WARNING:
                g_stdout->SetColour ( g_stdout->FG_GREEN | g_stdout->FG_INTENSITY ); break;
            case BUG_LEVEL_INFO:
                g_stdout->SetColour ( g_stdout->FG_GREEN ); break;
            default:
                g_stdout->SetColour ( 0 ); break;
        }
        if (common_log_format)
        {
            // Slightly modified Apache Common Log Format
            // Host ip and hostname are replaced by priority level
            char buffer[50];
            sprintf ( buffer, "%i", current->priority );
            g_stdout->Write ( buffer );
            strftime ( buffer, 50, " - [%d/%b/%Y:%H:%M:%S ", current->bug_time );
            g_stdout->Write ( buffer );
            sprintf ( buffer, "%+i00", -1 * timezone/60/60 );
            g_stdout->Write ( buffer );
            g_stdout->Write ( "] " );
        }
        else
            g_stdout->Write ( asctime ( current->bug_time ) );
        g_stdout->WriteLine ( current->description.c_str ( ) );
    }
}

void
CoreDebugLog::SaveLog ( )
{
    CoreAssert ( this );
    CoreDebugLogData *current;
    string filename;
    char buffer[50];

    time_t temp;
    time ( &temp );

    strftime ( buffer, 50, "%Y-%m-%d", localtime ( &temp ) );
    filename = buffer;
    filename += "_" + app_name + "_" + app_version;
    filename += ".log";
    TextWriter *writer = new TextWriter ( filename.c_str () );

    writer->Write ( "%s %s - Website at <%s>\nEmail <%s> with Bug Reports\n",
    app_name.c_str ( ), app_version.c_str ( ),
    app_website.c_str ( ), email.c_str ( ) );
    for (int i = 0; reports->ValidIndex ( i ) ; i++)
    {
        current = reports->GetData ( i );
        if (common_log_format)
        {
            // Slightly modified Apache Common Log Format
            // Host ip and hostname are replaced by priority level
            sprintf ( buffer, "%i", current->priority );
            writer->Write ( buffer );
            strftime ( buffer, 50, " - [%d/%b/%Y:%H:%M:%S ", current->bug_time );
            writer->Write ( buffer );
            sprintf ( buffer, "%+i00", -1 * timezone/60/60 );
            writer->Write ( "%s] ", buffer );
        }
        else
        {
            switch ( current->priority )
            {
                case BUG_LEVEL_ERROR:
                    writer->Write ( "(EE)" ); break;
                case BUG_LEVEL_WARNING:
                    writer->Write ( "(WW)" ); break;
                case BUG_LEVEL_INFO:
                    writer->Write ( "(II)" ); break;
                default:
                    writer->Write ( "(--)" ); break;
            }
            strftime ( buffer, 50, "%Y-%m-%d, %H:%M:%S", current->bug_time );
            writer->Write ( " %s: ", buffer ); 
        }
        writer->WriteLine ( current->description.c_str ( ) );
    }
    delete writer;
}
#endif