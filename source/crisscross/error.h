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

#ifndef __included_cc_error_h
#define __included_cc_error_h

namespace CrissCross
{
	//! The error types.
	/*!
	 *  These errors are used throughout the entire project.
	 *  If you get an error while calling a function, find that
	 *  error number in this list.
	 */
	enum Errors
	{
		CC_ERR_BADPARAMETER = -1000,                  //!< One of the parameters passed to the function was not valid.
		CC_ERR_NOT_IMPLEMENTED,
		CC_ERR_FILE_OPEN,                             //!< The specified file could not be opened.
		CC_ERR_WRITE,                                 //!< The buffer could not be written to.
		CC_ERR_INTERNAL,                              //!< A call inside the function failed.
		CC_ERR_INVALID_CALL = -500,                   //!< The function call was invalid.
		CC_ERR_INVALID_BUFFER = -499,                 //!< The buffer was NULL (file not opened?)
		CC_ERR_INCOMPATIBLE_BUFFER = -498,            //!< The buffer was incompatible (i.e. reading unicode data on a non-unicode buffer).
		CC_ERR_EPERM,
		CC_ERR_ENOENT,
		CC_ERR_ESRCH,
		CC_ERR_EINTR,
		CC_ERR_EIO,
		CC_ERR_ENXIO,
		CC_ERR_E2BIG,
		CC_ERR_ENOEXEC,
		CC_ERR_EBADF,
		CC_ERR_ECHILD,
		CC_ERR_EAGAIN,
		CC_ERR_ENOMEM,
		CC_ERR_EACCES,
		CC_ERR_EFAULT,
		CC_ERR_ENOTBLK,
		CC_ERR_EBUSY,
		CC_ERR_EEXIST,
		CC_ERR_EXDEV,
		CC_ERR_ENODEV,
		CC_ERR_ENOTDIR,
		CC_ERR_EISDIR,
		CC_ERR_EINVAL,
		CC_ERR_ENFILE,
		CC_ERR_EMFILE,
		CC_ERR_ENOTTY,
		CC_ERR_ETXTBSY,
		CC_ERR_EFBIG,
		CC_ERR_ENOSPC,
		CC_ERR_ESPIPE,
		CC_ERR_EROFS,
		CC_ERR_EMLINK,
		CC_ERR_EPIPE,
		CC_ERR_EDOM,
		CC_ERR_ERANGE,
		CC_ERR_EDEADLK,
		CC_ERR_ENAMETOOLONG,
		CC_ERR_ENOLCK,
		CC_ERR_ENOSYS,
		CC_ERR_ENOTEMPTY,
		CC_ERR_ELOOP,
		CC_ERR_EWOULDBLOCK,
		CC_ERR_ENOMSG,
		CC_ERR_EIDRM,
		CC_ERR_ECHRNG,
		CC_ERR_EL2NSYNC,
		CC_ERR_EL3HLT,
		CC_ERR_EL3RST,
		CC_ERR_ELNRNG,
		CC_ERR_EUNATCH,
		CC_ERR_ENOCSI,
		CC_ERR_EL2HLT,
		CC_ERR_EBADE,
		CC_ERR_EBADR,
		CC_ERR_EXFULL,
		CC_ERR_ENOANO,
		CC_ERR_EBADRQC,
		CC_ERR_EBADSLT,
		CC_ERR_EDEADLOCK = CC_ERR_EDEADLK,
		CC_ERR_EBFONT,
		CC_ERR_ENOSTR,
		CC_ERR_ENODATA,
		CC_ERR_ETIME,
		CC_ERR_ENOSR,
		CC_ERR_ENONET,
		CC_ERR_ENOPKG,
		CC_ERR_EREMOTE,
		CC_ERR_ENOLINK,
		CC_ERR_EADV,
		CC_ERR_ESRMNT,
		CC_ERR_ECOMM,
		CC_ERR_EPROTO,
		CC_ERR_EMULTIHOP,
		CC_ERR_EDOTDOT,
		CC_ERR_EBADMSG,
		CC_ERR_EOVERFLOW,
		CC_ERR_ENOTUNIQ,
		CC_ERR_EBADFD,
		CC_ERR_EREMCHG,
		CC_ERR_ELIBACC,
		CC_ERR_ELIBBAD,
		CC_ERR_ELIBSCN,
		CC_ERR_ELIBMAX,
		CC_ERR_ELIBEXEC,
		CC_ERR_EILSEQ,
		CC_ERR_ERESTART,
		CC_ERR_ESTRPIPE,
		CC_ERR_EUSERS,
		CC_ERR_ENOTSOCK,
		CC_ERR_EDESTADDRREQ,
		CC_ERR_EMSGSIZE,
		CC_ERR_EPROTOTYPE,
		CC_ERR_ENOPROTOOPT,
		CC_ERR_EPROTONOSUPPORT,
		CC_ERR_ESOCKTNOSUPPORT,
		CC_ERR_EOPNOTSUPP,
		CC_ERR_EPFNOSUPPORT,
		CC_ERR_EAFNOSUPPORT,
		CC_ERR_EADDRINUSE,
		CC_ERR_EADDRNOTAVAIL,
		CC_ERR_ENETDOWN,
		CC_ERR_ENETUNREACH,
		CC_ERR_ENETRESET,
		CC_ERR_ECONNABORTED,
		CC_ERR_ECONNRESET,
		CC_ERR_ENOBUFS,
		CC_ERR_EISCONN,
		CC_ERR_ENOTCONN,
		CC_ERR_ESHUTDOWN,
		CC_ERR_ETOOMANYREFS,
		CC_ERR_ETIMEDOUT,
		CC_ERR_ECONNREFUSED,
		CC_ERR_EHOSTDOWN,
		CC_ERR_EHOSTUNREACH,
		CC_ERR_EALREADY,
		CC_ERR_EINPROGRESS,
		CC_ERR_ESTALE,
		CC_ERR_EUCLEAN,
		CC_ERR_ENOTNAM,
		CC_ERR_ENAVAIL,
		CC_ERR_EISNAM,
		CC_ERR_EREMOTEIO,
		CC_ERR_EDQUOT,
		CC_ERR_ENOMEDIUM,
		CC_ERR_EMEDIUMTYPE,
		CC_ERR_ECANCELED,
		CC_ERR_ENOKEY,
		CC_ERR_EKEYEXPIRED,
		CC_ERR_EKEYREVOKED,
		CC_ERR_EKEYREJECTED,
		CC_ERR_EOWNERDEAD,
		CC_ERR_ENOTRECOVERABLE,
		CC_ERR_NO_RECOVERY,
		CC_ERR_HOST_NOT_FOUND,
		CC_ERR_TRY_AGAIN,
		CC_ERR_NO_DATA,
		CC_ERR_NO_SOCK,
		CC_ERR_SOCK_BUSY,
		CC_ERR_NONE = 0                               //!< Everything is fine, nothing is ruined.
	};

	//! Converts an errno number to a CrissCross::Errors value.
	CrissCross::Errors GetErrorNumber ( int why );

	//! Gets the name of the CrissCross::Errors value.
	const char *GetErrorDescription ( CrissCross::Errors why );
}

#endif
