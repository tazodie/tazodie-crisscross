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

#include <crisscross/universal_include.h>
#include <crisscross/core_debug.h>
#include <crisscross/core_console.h>

using namespace CrissCross::IO;

CoreConsole::CoreConsole ():
CoreIOWriter ( stdout, false, CC_LN_LF ),
CoreIOReader ( stdin, false, CC_LN_LF )
{
#ifdef TARGET_OS_WINDOWS
    if ( AllocConsole () == TRUE )
    {
        int hCrt = _open_osfhandle ( ( intptr_t ) GetStdHandle ( STD_OUTPUT_HANDLE ), _O_TEXT );
        FILE *hf = _fdopen ( hCrt, "w" );

        *stdout = *hf;
        int i = setvbuf ( stdout, NULL, _IONBF, 0 );

        hCrt =
            _open_osfhandle ( ( intptr_t ) GetStdHandle ( STD_ERROR_HANDLE ),
                              _O_TEXT );
        hf = _fdopen ( hCrt, "w" );
        *stderr = *hf;
        i = setvbuf ( stdout, NULL, _IONBF, 0 );
    }

    SetConsoleTitleA ( APP_NAME " " APP_VERSION " (Codename " APP_CODENAME ")" );
#endif
}

CoreConsole::CoreConsole ( FILE * _outputBuffer, FILE *_inputBuffer ):
CoreIOWriter ( _outputBuffer, false, CC_LN_LF ),
CoreIOReader ( _inputBuffer, false, CC_LN_LF )
{
}

CoreConsole::~CoreConsole ()
{
    SetColour ( 0 );
#ifdef TARGET_OS_WINDOWS
    FreeConsole ();
#endif
}

void
CoreConsole::SetColour ( short _flags )
{
    CoreAssert ( this != NULL );

#if !defined ( ANSI_COLOUR ) && defined ( TARGET_OS_WINDOWS )
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

    if ( _flags == 0 )
        SetConsoleTextAttribute ( hConsole, FG_GRAY );
    else
        SetConsoleTextAttribute ( hConsole, _flags );
#elif defined ( ANSI_COLOUR )
    // Reset colours to defaults.
    char codes[16];

    sprintf ( codes, "\033[" );
    Write ( "\033[0m" );

    if ( _flags == 0 )
        return;

    if ( _flags & FG_INTENSITY )
        strcat ( codes, "1;" );
    if ( _flags & FG_RED )
        strcat ( codes, "31;" );
    if ( _flags & FG_GREEN )
        strcat ( codes, "32;" );
    if ( _flags & FG_BROWN )
        strcat ( codes, "33;" );
    if ( _flags & FG_BLUE )
        strcat ( codes, "34;" );
    if ( _flags & FG_MAGENTA )
        strcat ( codes, "35;" );
    if ( _flags & FG_CYAN )
        strcat ( codes, "36;" );
    if ( _flags & FG_GRAY )
        strcat ( codes, "37;" );
    if ( _flags & FG_WHITE )
        strcat ( codes, "39;" );

    /*
       TODO: Determine if there is an ANSI code for background color intensity.
       if ( _flags & BG_INTENSITY )
       strcat ( codes, "???????" );
     */
    if ( _flags & BG_RED )
        strcat ( codes, "41;" );
    if ( _flags & BG_GREEN )
        strcat ( codes, "42;" );
    if ( _flags & BG_BROWN )
        strcat ( codes, "43;" );
    if ( _flags & BG_BLUE )
        strcat ( codes, "44;" );
    if ( _flags & BG_MAGENTA )
        strcat ( codes, "45;" );
    if ( _flags & BG_CYAN )
        strcat ( codes, "46;" );
    if ( _flags & BG_WHITE )
        strcat ( codes, "47;" );

    codes[strlen ( codes ) - 1] = 'm';

    Write ( "%s", codes );
#endif
}

void
CoreConsole::Clear ()
{
    CoreAssert ( this != NULL );

#if defined ( TARGET_OS_WINDOWS )
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

    GetConsoleScreenBufferInfo ( hConsole, &csbi );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( hConsole, TEXT ( ' ' ), dwConSize,
                                 coordScreen, &cCharsWritten );
    GetConsoleScreenBufferInfo ( hConsole, &csbi );
    FillConsoleOutputAttribute ( hConsole, csbi.wAttributes, dwConSize,
                                 coordScreen, &cCharsWritten );
    SetConsoleCursorPosition ( hConsole, coordScreen );
#elif defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_LINUX )
    Write ( "%s", "\033[0;0H\033[2J" );
#endif
}

void
CoreConsole::MoveUp ( int _lines )
{
#if defined ( TARGET_OS_WINDOWS )
    COORD coordScreen = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

    GetConsoleScreenBufferInfo ( hConsole, &csbi );
    coordScreen = csbi.dwCursorPosition;
    coordScreen.Y -= (short)_lines;
    if ( coordScreen.Y < 0 ) coordScreen.Y = 0;
    SetConsoleCursorPosition ( hConsole, coordScreen );
#elif defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_LINUX )
    Write ( "%s%d%s", "\033[", _lines, "A" );
#endif
}

char CoreConsole::ReadChar ( char _min, char _max )
{
    char _result = 0;
    fscanf ( m_fileInputPointer, "%c", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

int CoreConsole::ReadInt ( int _min, int _max )
{
    int _result = 0;
    fscanf ( m_fileInputPointer, "%d", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

long CoreConsole::ReadLong ( long _min, long _max )
{
    long _result = 0;
    fscanf ( m_fileInputPointer, "%ld", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

float CoreConsole::ReadFloat ( float _min, float _max )
{
    float _result = 0;
    fscanf ( m_fileInputPointer, "%f", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

double CoreConsole::ReadDouble ( double _min, double _max )
{
    double _result = 0;
    fscanf ( m_fileInputPointer, "%lf", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

long double CoreConsole::ReadLongDouble ( long double _min, long double _max )
{
    long double _result = 0;
    fscanf ( m_fileInputPointer, "%llf", &_result );
    CoreIOReader::Flush();
    if ( ( _min && _max ) && ( _min < _max ) )
    {
        if ( _result < _min )
            _result = _min;
        if ( _result > _max )
            _result = _max;
    }
    return _result;
}

int CoreConsole::Seek ( int _position ) { return 0; }
int CoreConsole::Forward ( int _position ) { return 0; }
int CoreConsole::Length() { return 0; }
int CoreConsole::Read ( char *_buffer, int _bufferLength, int _bufferIndex, int _count ) { return 0; };
bool CoreConsole::EndOfFile () { return false; };
