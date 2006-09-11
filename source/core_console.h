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

#ifndef __included_core_console_h
#define __included_core_console_h

#    include "core_io.h"

namespace CrissCross
{
    namespace IO
    {
        //! The core console input/output class.
        class CoreConsole:public CoreIO
        {
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
        #    if !defined ( ANSI_COLOUR ) && defined ( TARGET_OS_WINDOWS )
                FG_BROWN = 0x0000,                                      /*!< Brown Foreground (POSIX only) */
                FG_MAGENTA = FG_BLUE | FG_RED,                          /*!< Magenta Foreground */
                FG_CYAN = FG_BLUE | FG_GREEN,                           /*!< Cyan Foreground */
                BG_BROWN = 0x0000,                                      /*!< Brown Background (POSIX only) */
                BG_MAGENTA = BG_BLUE | BG_RED,                          /*!< Magenta Background */
                BG_CYAN = BG_GREEN | BG_BLUE,                           /*!< Cyan Background */
                FG_GRAY = FG_BLUE | FG_GREEN | FG_RED,                  /*!< Gray Foreground */
                FG_WHITE = FG_BLUE | FG_GREEN | FG_RED | FG_INTENSITY,  /*!< White Foreground */
                BG_GRAY = BG_BLUE | BG_GREEN | BG_RED,                  /*!< Gray Background */
                BG_WHITE = BG_BLUE | BG_GREEN | BG_RED | BG_INTENSITY   /*!< White Background */
        #    elif defined ( ANSI_COLOUR )
                FG_BROWN = 0x0100,          /*!< Brown Foreground (POSIX only) */
                FG_MAGENTA = 0x0200,        /*!< Magenta Foreground */
                FG_CYAN = 0x0400,           /*!< Cyan Foreground */
                BG_BROWN = 0x0800,          /*!< Brown Background (POSIX only) */
                BG_MAGENTA = 0x1000,        /*!< Magenta Background */
                BG_CYAN = 0x2000,           /*!< Cyan Background */
                FG_GRAY = 0x4000,           /*!< Gray Foreground */
                FG_WHITE = 0x8000,          /*!< White Foreground */
                BG_GRAY = 0x10000,          /*!< Gray Background */
                BG_WHITE = 0x20000          /*!< White Background */
        #    endif
            } ColourTypes;

          public:

            //! The default constructor.
            /*! Allocates a new console (in Windows) for stdout and stderr output. */
            CoreConsole ();

            //! The alternate constructor
            /*!
               Does not allocate a new console, and instead uses the specified FILE * for output.
               \param _outputBuffer The destination buffer for CoreConsole output.
               \sa CoreConsole()
             */
            CoreConsole ( FILE * _outputBuffer );

            //! The destructor.
             ~CoreConsole ();

            //! Sets the console output colour.
            /*!
               Sets the console output colour using the flags specified in _flags.
               \param _flags A bitmask created by OR-ing CoreConsole::ColourTypes flags.
             */
            void SetColour ( short _flags );

            //! Clears the console.
            /*!
               Clears the console output (similar to commands 'cls' on Windows and 'clear' on Linux).
             */
            void Clear ();

            //! Move up a line.
            /*!
               Permits you to overwrite the previous line. Good for a status display.
             */
            void MoveUp ( int _lines );

            //! Does nothing.
            /*!
               To get input from the console, use std::cin.
             */
            char Read ();

            //! Does nothing.
            /*!
               To get input from the console, use std::cin.
             */
            std::string ReadLine ();

        private:
            bool EndOfFile ();
            int Forward ( int _position );
            int Seek ( int _position );
            size_t Length ();
            size_t Read ( char *_buffer, int _bufferLength, int _bufferIndex,
                          int _count );
        };
    }
}

#endif
