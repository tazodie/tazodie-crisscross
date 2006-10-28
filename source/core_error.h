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

#ifndef __included_core_CC_ERR_SOCK_h
#define __included_core_CC_ERR_SOCK_h

namespace CrissCross
{
    //! The error types.
    /*!
        These errors are used throughout the entire project.
        If you get an error while calling a function, find that
        error number in this list.
     */
    enum Errors
    {
        CC_ERR_BADPARAMETER = -1000,                  //!< One of the parameters passed to the function was not valid.
        CC_ERR_FILE_OPEN = -999,                      //!< The specified file could not be opened.
        CC_ERR_WRITE = -998,                          //!< The buffer could not be written to.
        CC_ERR_INTERNAL = -997,                       //!< A call inside the function failed.
        CC_ERR_SOCK_CONNECTIONLOST = -996,            //!< The connection was lost.
        CC_ERR_SOCK_CONNECT = -995,                   //!< The connect() call failed.
        CC_ERR_SOCK_LISTEN = -994,                    //!< The listen() call failed.
        CC_ERR_SOCK_BIND = -993,                      //!< The bind() call failed.
        CC_ERR_SOCK_DNS = -992,                       //!< The host couldn't be resolved via DNS.
        CC_ERR_SOCK_CREATE_SOCKET = -991,             //!< The socket() call failed.
        CC_ERR_SOCK_SOCKET_IN_USE = -990,             //!< The socket is in use. The call being attempted is invalid for the current socketState.
        CC_ERR_SOCK_SOCKET_NOT_INITIALISED = -989,    //!< The socket has not yet been initialised.
        CC_ERR_SOCK_NOT_IMPLEMENTED = -988,           //!< The call has not yet been implemented or will not be implemented in the abstract class.
        CC_ERR_SOCK_BAD_PARAMETER = -987,             //!< One of the parameters given was invalid.
        CC_ERR_SOCK_DATA_NOTAVAIL = -986,             //!< A read call received no data.
        CC_ERR_SOCK_DATA_TIMEOUT = -985,              //!< Timeout waiting for data.
        CC_ERR_INVALID_CALL = -500,                   //!< The function call was invalid.
        CC_ERR_NONE = 0                               //!< Everything is fine, nothing is ruined.
    };
}

#endif
