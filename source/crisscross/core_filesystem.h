/*
 *
 *                                   C R I S S C R O S S
 *                          A multi purpose cross platform library.
 *                             project started August 14, 2006
 *
 * Copyright (c) 2006-2007 IO.IN Research
 *
 * Licensed under the New BSD License.
 *
 */

#ifndef __included_core_filesystem_h
#define __included_core_filesystem_h

/*============================================*/
/*|MAINTAINER: Rudolf Olah <omouse@gmail.com>|*/
/*============================================*/

namespace CrissCross
{
    namespace FileSystem
    {
        //! Tests whether or not the give path references an existing file.
        /*!
            \param _path The path to probe.
            \return Boolean indicating whether or not the file exists.
         */
        bool FileExists ( std::string _path );

        //! Tests whether or not the give path references a file.
        /*!
            \param _path The path to probe.
            \return Boolean indicating whether or not the path references a file.
         */
        bool IsFile ( std::string _path );

        //! Tests whether or not the give path references a directory.
        /*!
            \param _path The path to probe.
            \return Boolean indicating whether or not the path references a directory.
         */
        bool IsDir ( std::string _path );

        //! Tests whether or not the give path references a symbolic link.
        /*!
            \param _path The path to probe.
            \return Boolean indicating whether or not the path references a symbolic link.
         */
        bool IsLink ( std::string _path );

        const char *NativePath ( std::string _path, char _device = 'c' );
        const char *WindowsPath ( std::string _path, char _device = 'c' );
        const char *PosixPath ( std::string _path );
        const char *NativePath ( const char *_path, char _device = 'c' );
        const char *WindowsPath ( const char *_path, char _device = 'c' );
        const char *PosixPath ( const char *_path );
        const char *DefaultHomePath ();
    }
}

#endif
