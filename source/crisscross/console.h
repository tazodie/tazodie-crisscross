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

#ifndef __included_cc_console_h
#define __included_cc_console_h

#include <crisscross/core_io.h>

namespace CrissCross
{
    namespace IO
    {
        //! The core console input/output class.
        class Console : public CoreIOWriter, public CoreIOReader
        {
protected:
            bool m_consoleAllocated;
#if defined ( TARGET_OS_MACOSX ) || defined ( TARGET_OS_FREEBSD ) || \
      defined ( TARGET_OS_OPENBSD ) || defined ( TARGET_OS_NETBSD )
			int m_ptyfd;
			int m_ttyfd;
			char m_slaveName[32];
			pid_t m_childPID;
#endif
			bool AllocateConsole();
public:

            //! Flags used for describing console colour output.
            typedef enum
            {
                FG_BLUE = 0x0001,               /*!< Blue Foreground */
                FG_GREEN = 0x0002,              /*!< Green Foreground */
                FG_RED = 0x0004,                /*!< Red Foreground */
                FG_INTENSITY = 0x0008,          /*!< Foreground intensity (makes the foreground colour a shade brighter) */
                BG_BLUE = 0x0010,               /*!< Blue Background */
                BG_GREEN = 0x0020,              /*!< Green Background */
                BG_RED = 0x0040,                /*!< Red Background */
                BG_INTENSITY = 0x0080,          /*!< Background intensity (makes the foreground colour a shade brighter) */
        #if !defined ( ANSI_COLOUR ) && defined ( TARGET_OS_WINDOWS )
                FG_BROWN = 0x0000,                                      /*!< Brown Foreground (POSIX only) */
                FG_MAGENTA = FG_BLUE | FG_RED,                          /*!< Magenta Foreground */
                FG_CYAN = FG_BLUE | FG_GREEN,                           /*!< Cyan Foreground */
                FG_GRAY = FG_BLUE | FG_GREEN | FG_RED,                  /*!< Gray Foreground */
                FG_WHITE = FG_BLUE | FG_GREEN | FG_RED | FG_INTENSITY,  /*!< White Foreground */
                FG_YELLOW = FG_GREEN | FG_RED,                          /*!< Yellow Foreground */
                BG_BROWN = 0x0000,                                      /*!< Brown Background (POSIX only) */
                BG_MAGENTA = BG_BLUE | BG_RED,                          /*!< Magenta Background */
                BG_CYAN = BG_GREEN | BG_BLUE,                           /*!< Cyan Background */
                BG_GRAY = BG_BLUE | BG_GREEN | BG_RED,                  /*!< Gray Background */
                BG_WHITE = BG_BLUE | BG_GREEN | BG_RED | BG_INTENSITY,  /*!< White Background */
                BG_YELLOW = BG_GREEN | BG_RED                           /*!< Yellow Background */
        #elif defined ( ANSI_COLOUR )
                FG_BROWN = 0x0100,          /*!< Brown Foreground (POSIX only) */
                FG_MAGENTA = 0x0200,        /*!< Magenta Foreground */
                FG_CYAN = 0x0400,           /*!< Cyan Foreground */
                FG_GRAY = 0x0800,           /*!< Gray Foreground */
                FG_WHITE = 0x1000,          /*!< White Foreground */
                FG_YELLOW = FG_BROWN | BG_INTENSITY, /*!< Yellow Foreground */
                BG_BROWN = 0x4000,          /*!< Brown Background (POSIX only) */
                BG_MAGENTA = 0x8000,        /*!< Magenta Background */
                BG_CYAN = 0x10000,          /*!< Cyan Background */
                BG_GRAY = 0x20000,          /*!< Gray Background */
                BG_WHITE = 0x40000,         /*!< White Background */
                BG_YELLOW = BG_BROWN | FG_INTENSITY /*!< Yellow Background */
        #endif
            } ColourTypes;

public:

            //! The default constructor.
            /*!
             Allocates a new console for stdout and stderr output.
             \param _clearOnInit If true, clears the output console if supported.
             \param _fillScreen This moves the console window to the extreme left and switches to the maximum possible window height.
             */
            Console ( bool _clearOnInit = false, bool _fillScreen = false );

            //! The alternate constructor
            /*!
               Does not allocate a new console, and instead uses the specified FILE* parameters for input/output.
             \param _outputBuffer The buffer for Console output.
             \param _inputBuffer The buffer for Console input.
             \sa Console()
             */
            Console ( FILE * _outputBuffer, FILE *_inputBuffer );

            //! The destructor.
            ~Console ();

            //! Sets the console output colour to the default.
            void SetColour ();

            //! Sets the console output colour.
            /*!
               Sets the console output colour using the flags specified in _flags.
             \param _flags A bitmask created by OR-ing Console::ColourTypes flags.
             */
            void SetColour ( int _flags );

            //! Sets the title of the terminal window.
            /*!
               Sets the console window title using the value in the _title parameter.
             \param _title The title requested for the console window.
             */
            void SetTitle ( const char *_title );

            //! Sets the title of the terminal window.
            /*!
               Sets the console window title using the value in the _title parameter.
             \param _title The title requested for the console window.
             */
            void SetTitle ( std::string &_title );

            //! Clears the console.
            /*!
               Clears the console output (similar to commands 'cls' on Windows and 'clear' on Linux).
             */
            void Clear ();

            //! Move the cursor up a given number of lines.
            /*!
               Permits you to overwrite previous lines. Good for a status display.
             \param _lines Number of lines to move the cursor
             */
            void MoveUp ( int _lines );

            //! Reads a char from the console.
            char ReadChar ();

            //! Reads a char from the console.
            /*!
                If both _min and _max are zero, the input will be returned, no matter what the value is (no bounds checking).
             \param _min The minimum input value.
             \param _max The maximum input value.
             */
            char ReadChar ( char _min, char _max );

            //! Reads an integer from the console.
            int ReadInt ();

            //! Reads an integer from the console.
            /*!
                If both _min and _max are zero, the input will be returned, no matter what the value is (no bounds checking).
             \param _min The minimum input value.
             \param _max The maximum input value.
             */
            int ReadInt ( int _min = 0, int _max = 0 );

            //! Reads a long integer from the console.
            long ReadLong ();

            //! Reads a long integer from the console.
            /*!
                If both _min and _max are zero, the input will be returned, no matter what the value is (no bounds checking).
             \param _min The minimum input value.
             \param _max The maximum input value.
             */
            long ReadLong ( long _min = 0, long _max = 0 );

            //! Reads a float from the console.
            float ReadFloat ();

            //! Reads a float from the console.
            /*!
                If both _min and _max are zero, the input will be returned, no matter what the value is (no bounds checking).
             \param _min The minimum input value.
             \param _max The maximum input value.
             */
            float ReadFloat ( float _min = 0, float _max = 0 );

            //! Reads a double from the console.
            double ReadDouble ();

            //! Reads a double from the console.
            /*!
                If both _min and _max are zero, the input will be returned, no matter what the value is (no bounds checking).
             \param _min The minimum input value.
             \param _max The maximum input value.
             */
            double ReadDouble ( double _min = 0, double _max = 0 );

            //! Flushes the input and output buffers.
            void Flush ();

private:
            bool EndOfFile ();
            int Forward ( cc_int64_t _position );
            int Seek ( cc_int64_t _position );
            cc_int64_t Length ();
            int Read ( char *_buffer, size_t _bufferLength, size_t _bufferIndex, size_t _count );
        };
    }
}

#endif
