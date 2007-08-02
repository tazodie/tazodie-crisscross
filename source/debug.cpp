/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/debug.h>
#include <crisscross/textwriter.h>

using namespace CrissCross::IO;

#ifndef ENABLE_SYMBOL_ENGINE
#    ifdef TARGET_OS_WINDOWS
#        pragma warning (disable: 4311)
#    endif
#else
#    pragma warning (disable: 4312)
#    pragma comment( lib, "dbghelp" )

class SymbolEngine
{
  public:
    static SymbolEngine & instance ();
      std::string addressToString ( DWORD address );
    void StackTrace ( PCONTEXT _pContext, CoreIOWriter * _outputBuffer );
  private:
      SymbolEngine ( SymbolEngine const & );
      SymbolEngine & operator= ( SymbolEngine const & );
      SymbolEngine ();
    HANDLE hProcess;
  public:
     ~SymbolEngine ();
  private:
};

SymbolEngine & SymbolEngine::instance ()
{
    static SymbolEngine
        theEngine;

    return theEngine;
}

SymbolEngine::SymbolEngine ()
{
    hProcess = GetCurrentProcess ();

    DWORD dwOpts = SymGetOptions ();

    dwOpts |= SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS;
    SymSetOptions ( dwOpts );

    ::SymInitialize ( hProcess, 0, true );
}

SymbolEngine::~SymbolEngine ()
{
    ::SymCleanup ( hProcess );
}

std::string SymbolEngine::addressToString ( DWORD address )
{
    std::ostringstream oss;

    // First the raw address
    oss << "0x" << ( PVOID ) address;

    // Then any name for the symbol
    struct tagSymInfo
    {
        IMAGEHLP_SYMBOL symInfo;
        char nameBuffer[4 * 256];
    } SymInfo = { { sizeof ( IMAGEHLP_SYMBOL ) } };

    IMAGEHLP_SYMBOL *
        pSym = &SymInfo.symInfo;

    pSym->MaxNameLength =
        sizeof ( SymInfo ) - offsetof ( tagSymInfo, symInfo.Name );

    DWORD
        dwDisplacement;

    if ( SymGetSymFromAddr
         ( GetCurrentProcess (), ( DWORD ) address, &dwDisplacement,
           pSym ) )
    {
        oss << " " << pSym->Name;
        /*if ( dwDisplacement != 0 )
           oss << "+0x" << std::hex << dwDisplacement << std::dec; */
    }

    // Finally any file/line number
    IMAGEHLP_LINE
    lineInfo = { sizeof ( IMAGEHLP_LINE ) };
    if ( SymGetLineFromAddr
         ( GetCurrentProcess (), ( DWORD ) address, &dwDisplacement,
           &lineInfo ) )
    {
        const char *pDelim = strrchr ( lineInfo.FileName, '\\' );

        oss << " at " << ( pDelim ? pDelim +
                           1 : lineInfo.FileName ) << "(" << lineInfo.
            LineNumber << ")";
    }
    return oss.str ();
}

void
SymbolEngine::StackTrace ( PCONTEXT _pContext, CoreIOWriter * _outputBuffer )
{
    _outputBuffer->WriteLine ( "  Frame       Address   Code" );

    STACKFRAME stackFrame = { 0 };

    stackFrame.AddrPC.Offset = _pContext->Eip;
    stackFrame.AddrPC.Mode = AddrModeFlat;

    stackFrame.AddrFrame.Offset = _pContext->Ebp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;

    stackFrame.AddrStack.Offset = _pContext->Esp;
    stackFrame.AddrStack.Mode = AddrModeFlat;

    while ( ::StackWalk ( IMAGE_FILE_MACHINE_I386, hProcess, GetCurrentThread (),    // this value doesn't matter much if previous one is a real handle
                          &stackFrame,
                          _pContext,
                          NULL,::SymFunctionTableAccess,::SymGetModuleBase,
                          NULL ) )
    {
        _outputBuffer->WriteLine ( " 0x%xd %s", stackFrame.AddrFrame.Offset,
                                   addressToString ( stackFrame.AddrPC.
                                                     Offset ).c_str () );
    }
}
#endif

void
PrintStackTrace ( CoreIOWriter * _outputBuffer )
{
#if !defined ( TARGET_OS_MACOSX ) && !defined ( TARGET_OS_NETBSD ) && !defined ( TARGET_OS_FREEBSD ) && !defined ( TARGET_OS_OPENBSD )

#    ifdef ENABLE_SYMBOL_ENGINE

    CONTEXT context = { CONTEXT_FULL };
    ::GetThreadContext ( GetCurrentThread (), &context );
    _asm call $ + 5;
    _asm pop eax;
    _asm mov context.Eip, eax;
    _asm mov eax, esp;
    _asm mov context.Esp, eax;
    _asm mov context.Ebp, ebp;
    SymbolEngine::instance ().StackTrace ( &context, _outputBuffer );

#    elif defined ( ENABLE_BACKTRACE )

    void *array[20];
    int size;
    char **strings;
    int i;

    //use -rdynamic flag when compiling
    size = backtrace (array, 20);
    strings = backtrace_symbols (array, size);
  
    _outputBuffer->WriteLine ( "Obtained %d stack frames.", size );

    std::string bt = "";

    for ( i = 0; i < size; i++ )
      {
#if 1
    bt += strings[i];
    int status;
    // extract the identifier from strings[i].  It's inside of parens.
    char* firstparen = ::strchr(strings[i], '(');
    char* lastparen = ::strchr(strings[i], '+');
    if (firstparen != 0 && lastparen != 0 && firstparen < lastparen)
      {
        bt += ": ";
        *lastparen = '\0';
        char* realname = abi::__cxa_demangle(firstparen+1, 0, 0, &status);
        if ( realname != NULL )
          {
        bt += realname;
          }
        free(realname);
      }
#else
        bt += "  ";
        bt += strings[i];
#endif
        bt += "\n";
    }

    _outputBuffer->WriteLine ( "%s\n", bt.c_str() );
  
    free(strings);

#   else
    _outputBuffer->WriteLine ( "FAIL: backtrace() function not available." );
#   endif
#endif // TARGET_OS_MACOSX
}

#ifndef USE_FAST_ASSERT
void
Assert ( bool _condition, const char *_testcase, const char *_file,
         int _line )
{
    if ( !_condition )
    {
        char buffer[10240];
        sprintf ( buffer, "Assertion failed : '%s'\nFile: %s\nLine: %d\n\n",
        _testcase, _file, _line );
        fprintf ( stderr, "%s", buffer );
        fprintf ( stderr, "=== STACK TRACE ===\n" );
        CoreIOWriter *stderror = new CoreIOWriter ( stderr, false, CC_LN_LF );
        PrintStackTrace ( stderror );
        delete stderror;
        #ifndef _DEBUG
            abort();
        #else
            _ASSERT ( _condition );
        #endif
    }
}
#endif
