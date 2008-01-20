/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include <crisscross/universal_include.h>
#include <crisscross/debug.h>
#include <crisscross/console.h>

namespace CrissCross
{
	namespace IO
	{
		Console::Console ( bool _clearOnInit ):
		CoreIOWriter ( stdout, false, CC_LN_LF ),
		CoreIOReader ( stdin, false, CC_LN_LF )
		{
		#ifdef TARGET_OS_WINDOWS
			m_consoleAllocated = false;
			if ( AllocConsole () == TRUE )
			{
				m_consoleAllocated = true;
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

			if ( _clearOnInit ) Clear();

			SetTitle ( CC_LIB_NAME " " CC_LIB_VERSION " (Codename " CC_LIB_CODENAME ")" );
        #elif defined ( TARGET_OS_NDSFIRMWARE )
            irqInit();
            irqEnable(IRQ_VBLANK);
            videoSetMode(0);
            videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
            vramSetBankC(VRAM_C_SUB_BG);
	        SUB_BG0_CR = BG_MAP_BASE(31);
	        BG_PALETTE_SUB[255] = RGB15(31,31,31);
	        consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);
		#endif
		#ifdef ENABLE_CREDITS
			g_stdout->SetColour ( g_stdout->FG_GREEN | g_stdout->FG_INTENSITY );
			g_stdout->WriteLine ( "Powered by " CC_LIB_NAME " " CC_LIB_VERSION " (Codename " CC_LIB_CODENAME ")\n    " CC_LIB_URL );
			g_stdout->SetColour ( 0 );
			g_stdout->WriteLine ( CC_LIB_COPYRIGHT );
			g_stdout->WriteLine ();
		#endif
		}

		Console::Console ( FILE * _outputBuffer, FILE *_inputBuffer ):
		CoreIOWriter ( _outputBuffer, false, CC_LN_LF ),
		CoreIOReader ( _inputBuffer, false, CC_LN_LF )
		{
		}

		Console::~Console ()
		{
			SetColour ( 0 );
		#ifdef TARGET_OS_WINDOWS
			if ( m_consoleAllocated ) FreeConsole ();
		#endif
		}

		void
		Console::SetColour ()
		{
			SetColour ( 0 );
		}

		void
		Console::SetColour ( short _flags )
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
		Console::SetTitle ( const char *_title )
		{
		#ifdef TARGET_OS_WINDOWS
			SetConsoleTitleA ( _title );
		#endif
		}

		void
		Console::SetTitle ( std::string &_title )
		{
			SetTitle ( _title.c_str () );
		}

		void
		Console::Clear ()
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
		Console::Flush ()
		{
			CoreIOReader::Flush();
			CoreIOWriter::Flush();
		}

		void
		Console::MoveUp ( int _lines )
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

		char Console::ReadChar ()
		{
			char _result = 0;
			fscanf ( m_fileInputPointer, "%c", &_result );
			CoreIOReader::Flush();
			return _result;
		}

		int Console::ReadInt ()
		{
			int _result = 0;
			fscanf ( m_fileInputPointer, "%d", &_result );
			CoreIOReader::Flush();
			return _result;
		}

		long Console::ReadLong ()
		{
			long _result = 0;
			fscanf ( m_fileInputPointer, "%ld", &_result );
			CoreIOReader::Flush();
			return _result;
		}

		float Console::ReadFloat ()
		{
			float _result = 0;
			fscanf ( m_fileInputPointer, "%f", &_result );
			CoreIOReader::Flush();
			return _result;
		}

		double Console::ReadDouble ()
		{
			double _result = 0;
			fscanf ( m_fileInputPointer, "%lf", &_result );
			CoreIOReader::Flush();
			return _result;
		}

		char Console::ReadChar ( char _min, char _max )
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

		int Console::ReadInt ( int _min, int _max )
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

		long Console::ReadLong ( long _min, long _max )
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

		float Console::ReadFloat ( float _min, float _max )
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

		double Console::ReadDouble ( double _min, double _max )
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

		int Console::Seek ( cc_int64_t _position ) { return 0; }
		int Console::Forward ( cc_int64_t _position ) { return 0; }
		cc_int64_t Console::Length() { return 0; }
		int Console::Read ( char *_buffer, size_t _bufferLength, size_t _bufferIndex, size_t _count ) { return 0; }
		bool Console::EndOfFile () { return false; }
	}
}
