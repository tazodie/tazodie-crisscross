/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                              formerly Codename "Technetium"
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006, Steven Noonan <steven@uplinklabs.net>, Rudolf Olah <omouse@gmail.com>,
 * and Miah Clayton <miah@io-in.com>. All rights reserved.
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

using namespace CrissCross::IO;
using namespace CrissCross::Debug;

CoreDebugLogData::CoreDebugLogData ( tm *_bug_time, int _priority, char *_description)
    : m_bug_time ( _bug_time ),
      m_priority ( _priority ),
      m_description ( new char[strlen(_description) + 1] )
{
    strcpy ( m_description, _description );
}

CoreDebugLogData::~CoreDebugLogData ()
{
    delete [] m_description;
}

CoreDebugLog::CoreDebugLog ( string _name, string _version,
                             string _website, string _email,
                             bool _common_log_format )
    : m_common_log_format ( _common_log_format ),
      m_app_name ( _name ), m_app_version ( _version ),
      m_app_website ( _website ), m_email ( _email ),
      m_reports ( new LList <CoreDebugLogData*> )
{

}

CoreDebugLog::~CoreDebugLog ( )
{
    while ( m_reports->Size() )
    {
        delete m_reports->GetData ( 0 );
        m_reports->RemoveData ( 0 );
    }
    delete m_reports;
}

void
CoreDebugLog::Write ( CoreDebugLog::LogEntryPriority _priority, const char *_format, ... )
{
    CoreAssert ( this != NULL );

    if ( _format == NULL )
        return;
    char buffer[10240];
    va_list args;
    va_start ( args , _format );
    vsprintf ( buffer, _format, args );
    va_end ( args );
    time_t temp;
    time ( &temp );
    CoreDebugLogData *report = new CoreDebugLogData ( localtime ( &temp ), _priority, buffer );
    m_reports->PutDataAtEnd ( report );

}

void
CoreDebugLog::WriteLine ( CoreDebugLog::LogEntryPriority _priority, const char *_format, ... )
{
    /* TODO: Write a way to make this non-redundant with Write(). */
    CoreAssert ( this != NULL );

    if ( _format == NULL )
        return;
    char buffer[10240];
    va_list args;
    va_start ( args , _format );
    vsprintf ( buffer, _format, args );
    va_end ( args );
    time_t temp;
    time ( &temp );
    CoreDebugLogData *report = new CoreDebugLogData ( localtime ( &temp ), _priority, buffer );
    m_reports->PutDataAtEnd ( report );

}

void
CoreDebugLog::Put ( CoreIO *_stream, CoreDebugLog::LogEntryPriority _lowest_priority )
{
    CoreAssert ( this != NULL );
    CoreDebugLogData *current;
    char buffer[50];
    _stream->Write ( "%s %s - Website at <%s>\nEmail <%s> with any bug reports\n",
    m_app_name.c_str ( ), m_app_version.c_str ( ),
    m_app_website.c_str ( ), m_email.c_str ( ) );
    for (int i = 0; m_reports->ValidIndex ( i ) ; i++)
    {
        current = m_reports->GetData ( i );
        if ( current->m_priority < _lowest_priority )
            continue;
        if (m_common_log_format)
        {
            // Slightly modified Apache Common Log Format
            // Host ip and hostname are replaced by priority level
            sprintf ( buffer, "%i", current->m_priority );
            _stream->Write ( buffer );
            strftime ( buffer, 50, " - [%d/%b/%Y:%H:%M:%S ", current->m_bug_time );
            _stream->Write ( buffer );
            sprintf ( buffer, "%+i00", (int)( -1 * (int)timezone / 60 / 60 ) );
            _stream->Write ( "%s] ", buffer );
        }
        else
        {
            switch ( current->m_priority )
            {
                case BUG_LEVEL_ERROR:
                    _stream->Write ( "(EE)" ); break;
                case BUG_LEVEL_WARNING:
                    _stream->Write ( "(WW)" ); break;
                case BUG_LEVEL_INFO:
                    _stream->Write ( "(II)" ); break;
                default:
                    _stream->Write ( "(--)" ); break;
            }
            strftime ( buffer, 50, "%Y-%m-%d, %H:%M:%S", current->m_bug_time );
            _stream->Write ( " %s: ", buffer ); 
        }
        _stream->WriteLine ( current->m_description );
    }
}

void
CoreDebugLog::Print ( CoreIO *_output, CoreDebugLog::LogEntryPriority _lowest_priority )
{
    CoreAssert ( this != NULL );
    Put ( _output, _lowest_priority );
}

void
CoreDebugLog::Save ( )
{
    CoreAssert ( this != NULL );
    string filename;
    char buffer[50];

    time_t temp;
    time ( &temp );

    strftime ( buffer, 50, "%Y-%m-%d", localtime ( &temp ) );
    filename = buffer;
    filename += "_" + m_app_name + "_" + m_app_version;
    filename += ".log";
    TextWriter *writer = new TextWriter ( filename.c_str () );
    
    Put ( writer, this->BUG_LEVEL_INFO );

    delete writer;
}
#endif
