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
#include "core_exception.h"
#include "core_debug.h"
#include "textwriter.h"

#ifndef ENABLE_SYMBOL_ENGINE
#ifdef TARGET_OS_WINDOWS
#pragma warning (disable: 4311)
#endif
#else
#pragma warning (disable: 4312)
#pragma comment( lib, "dbghelp" )

class SymbolEngine
{
public:
    static SymbolEngine &instance();
	std::string addressToString( DWORD address );
	void StackTrace( PCONTEXT _pContext, CoreIO *_outputBuffer );
private:
    SymbolEngine( SymbolEngine const & );
    SymbolEngine& operator=( SymbolEngine const & );
	SymbolEngine();
    HANDLE hProcess;
public:
    ~SymbolEngine();
private:
};

SymbolEngine& SymbolEngine::instance()
{
	static SymbolEngine theEngine;
    return theEngine;
}

SymbolEngine::SymbolEngine()
{
    hProcess = GetCurrentProcess();

    DWORD dwOpts = SymGetOptions();
    dwOpts |= SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS;
    SymSetOptions ( dwOpts );

    ::SymInitialize( hProcess, 0, true );
}

SymbolEngine::~SymbolEngine()
{
    ::SymCleanup( hProcess );
}

std::string SymbolEngine::addressToString ( DWORD address )
{
    std::ostringstream oss;

    // First the raw address
	oss << "0x" << (PVOID)address;

    // Then any name for the symbol
    struct tagSymInfo
    {
        IMAGEHLP_SYMBOL symInfo;
        char nameBuffer[ 4 * 256 ];
    } SymInfo = { { sizeof( IMAGEHLP_SYMBOL ) } };

    IMAGEHLP_SYMBOL * pSym = &SymInfo.symInfo;
    pSym->MaxNameLength = sizeof( SymInfo ) - offsetof( tagSymInfo, symInfo.Name );

    DWORD dwDisplacement;
    if ( SymGetSymFromAddr( GetCurrentProcess(), (DWORD)address, &dwDisplacement, pSym) )
    {
        oss << " " << pSym->Name;
        /*if ( dwDisplacement != 0 )
            oss << "+0x" << std::hex << dwDisplacement << std::dec;*/
    }
        
    // Finally any file/line number
    IMAGEHLP_LINE lineInfo = { sizeof( IMAGEHLP_LINE ) };
    if ( SymGetLineFromAddr( GetCurrentProcess(), (DWORD)address, &dwDisplacement, &lineInfo ) )
    {
        char const *pDelim = strrchr( lineInfo.FileName, '\\' );
        oss << " at " << ( pDelim ? pDelim + 1 : lineInfo.FileName ) << "(" << lineInfo.LineNumber << ")";
    }
    return oss.str();
}

void SymbolEngine::StackTrace( PCONTEXT _pContext, CoreIO *_outputBuffer )
{
	_outputBuffer->WriteLine ( "  Frame       Address   Code" );

    STACKFRAME stackFrame = {0};

    stackFrame.AddrPC.Offset = _pContext->Eip;
    stackFrame.AddrPC.Mode = AddrModeFlat;

    stackFrame.AddrFrame.Offset = _pContext->Ebp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;

    stackFrame.AddrStack.Offset = _pContext->Esp;
    stackFrame.AddrStack.Mode = AddrModeFlat;

    while ( ::StackWalk(
       IMAGE_FILE_MACHINE_I386,
       hProcess,
       GetCurrentThread(), // this value doesn't matter much if previous one is a real handle
       &stackFrame, 
       _pContext,
       NULL,
       ::SymFunctionTableAccess,
       ::SymGetModuleBase,
       NULL ) )
    {
		_outputBuffer->WriteLine ( " 0x%xd %s", stackFrame.AddrFrame.Offset, addressToString(stackFrame.AddrPC.Offset).c_str() );
    }
}
#endif


unsigned *GetRetAddress ( unsigned *_ebp )
{
#ifdef WIN32
	unsigned *retAddr;

	__asm {
		mov eax, [_ebp]
		mov eax, ss:[eax+4];
		mov [retAddr], eax
	}

	return retAddr;
#else
	unsigned **p = (unsigned **) _ebp;
	return p[1];
#endif
}

void PrintStackTrace ( CoreIO *_outputBuffer )
{
#ifdef ENABLE_SYMBOL_ENGINE

    CONTEXT context = {CONTEXT_FULL};
    ::GetThreadContext( GetCurrentThread(), &context );
    _asm call $+5
    _asm pop eax
    _asm mov context.Eip, eax
    _asm mov eax, esp
    _asm mov context.Esp, eax
    _asm mov context.Ebp, ebp

	SymbolEngine::instance().StackTrace ( &context, _outputBuffer );

#else

	unsigned *framePtr;
    unsigned *previousFramePtr = NULL;
    
#ifdef TARGET_OS_WINDOWS
	__asm { 
		mov [framePtr], ebp
	}
#else
	asm (
	    "movl %%ebp, %0;"
	    :"=r"(framePtr)
	    );
#endif
	while(framePtr) {
		                
		_outputBuffer->WriteLine ( "retAddress = %p", GetRetAddress ( framePtr ) );
		framePtr = *(unsigned **)framePtr;

	    // Frame pointer must be aligned on a
	    // DWORD boundary.  Bail if not so.
	    if ( (unsigned long) framePtr & 3 )   
			break;                    

        if ( framePtr <= previousFramePtr )
            break;

        // Can two DWORDs be read from the supposed frame address?          
#ifdef TARGET_OS_WINDOWS
        if ( IsBadWritePtr(framePtr, sizeof(PVOID)*2) ||
             IsBadReadPtr(framePtr, sizeof(PVOID)*2) )
            break;
#endif

        previousFramePtr = framePtr;
    
    }
#endif
}

void GenerateBlackBox( char *_msg )
{
    TextWriter *_file = new TextWriter ( "blackbox.txt" );

	_file->WriteLine ( "===========================" );
    _file->WriteLine ( "TECHNETIUM BLACK BOX REPORT" );
    _file->WriteLine ( "===========================" );
    _file->WriteLine ();

    _file->WriteLine ( "VERSION : %s", APP_VERSION );

    if( _msg ) _file->WriteLine ( "ERROR   : %s", _msg );
    
    //
    // Print stack trace
	// Get our frame pointer, chain upwards

    _file->WriteLine ();
    _file->WriteLine ( "=========================" );
    _file->WriteLine ( "====== STACKTRACE =======" );
    _file->WriteLine ( "=========================" );
    _file->WriteLine ();

	PrintStackTrace ( _file );
	
    delete _file;
}

void Assert( bool _condition, char *_testcase, char *_file, int _line )
{
	if ( !_condition )
	{
		char buffer[10240];
		sprintf ( buffer, "Assertion failed : '%s'\nFile: %s\nLine: %d\n\n", _testcase, _file, _line );
		GenerateBlackBox ( buffer );
//#ifndef _DEBUG
		throw new AssertionFailureException ( _file, _line ) ;
//#else
//		_ASSERT ( _condition );
//#endif
	}
}
