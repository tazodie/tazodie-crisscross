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

#include <crisscross/core_filesystem.h>

/*============================================*/
/*|MAINTAINER: Rudolf Olah <omouse@gmail.com>|*/
/*============================================*/

namespace CrissCross
{
    namespace FileSystem
    {
        bool
        FileExists ( std::string path )
        {
            FILE *file;
            file = fopen ( path.c_str(), "r" );
            if ( file == NULL )
                return false;
            fclose ( file );
            return true;
        }

        bool
        IsFile ( std::string path )
        {
	            struct stat fileInfo;
            if ( stat ( path.c_str (), &fileInfo ) == -1) // Doesn't exist
                return false;
            if ( ( fileInfo.st_mode & S_IFMT ) != S_IFDIR ) // It's a file
                return true;
            return false;
        }

        bool
        IsDir ( std::string path )
        {
            struct stat fileInfo;
            if ( stat ( path.c_str (), &fileInfo ) == -1) // Doesn't exist
                return false;
            if ( ( fileInfo.st_mode & S_IFMT ) == S_IFDIR ) // It's a directory
                return true;
            return false;
        }

        bool
        IsLink ( std::string path )
        {
#ifndef TARGET_OS_WINDOWS
            struct stat fileInfo;
            if ( lstat ( path.c_str (), &fileInfo ) == -1) // Doesn't exist
                return false;
            if ( ( fileInfo.st_mode & S_IFMT ) == S_IFLNK ) // It's a symbolic link
                return true;
#endif
            return false;
        }

        const char *
        NativePath ( std::string path, char device )
        {
            return NativePath ( path.c_str (), device );
        }

        const char *
        NativePath ( const char *path, char device )
        {
#ifdef TARGET_OS_WINDOWS
            return WindowsPath ( path, device );
#else
            return PosixPath ( path );
#endif
        }

        const char *
        WindowsPath ( std::string path, const char device )
        {
            return WindowsPath ( path.c_str (), device );
        }

        const char *
        WindowsPath ( const char *path, char device )
        {
            static char *buffer = NULL;
            if ( path[0] != '/' ) // Relative path
            {
                buffer = new char[strlen ( path ) + 1];
                memset (buffer, 0, sizeof (buffer));
            }
            else
            {
                buffer = new char[strlen ( path ) + 3];
                memset (buffer, 0, sizeof (buffer));
                buffer[0] = device;
                buffer[1] = ':';
            }

            strcat ( buffer, path );
            for ( unsigned int i = 0; i < strlen ( buffer ); i++ )
                if ( buffer[i] == '/' )
                    buffer[i] = '\\';

            return buffer;
        }

        const char *
        PosixPath ( std::string path )
        {
            return PosixPath ( path.c_str () );
        }

        const char *
        PosixPath ( const char *path )
        {
            static char *buffer = NULL;
            if ( path[1] != ':' ) // Relative path
            {
                buffer = new char[strlen ( path ) + 1];
                strncpy ( buffer, path, strlen ( path ));
            }
            else
            {
                buffer = new char[strlen ( path ) + 3];
                strcpy ( buffer, path );
                buffer += 2;
            }

            for ( unsigned int i = 0; i < strlen ( buffer ); i++ )
                if ( buffer[i] == '\\' )
                    buffer[i] = '/';

            return buffer;
        }

        const char *
        DefaultHomePath ()
        {
            int bufsize = 1;
            static char buffer[512];
            memset ( buffer, 0, sizeof ( buffer ) );
#ifdef TARGET_OS_WINDOWS
            char path_buf[MAX_PATH];
            memset ( path_buf, 0, sizeof ( path_buf ) );
            SHGetFolderPathA ( NULL, CSIDL_PERSONAL, NULL, 0, path_buf );
            bufsize += (int)strlen ( path_buf ) + 1;
            sprintf ( buffer, "%s\\", path_buf );
#else
            char *tbuf;
            tbuf = getenv ( "HOME" );
            bufsize = strlen ( tbuf ) + 2;
            sprintf ( buffer, "%s/", tbuf );
#endif

            return buffer;
        }
    }
}
