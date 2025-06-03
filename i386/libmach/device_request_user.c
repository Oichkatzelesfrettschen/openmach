#include "device_request.h"
#define EXPORT_BOOLEAN
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/message.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/mig_errors.h>
#include <mach/mig_support.h>
#include <mach/msg_type.h>
/* LINTLIBRARY */

#ifndef	mig_internal
#define	mig_internal	static
#endif

#ifndef	mig_external
#define mig_external
#endif

#ifndef	TypeCheck
#define	TypeCheck 1
#endif

#ifndef	UseExternRCSId
#define	UseExternRCSId		1
#endif

#define msgh_request_port	msgh_remote_port
#define msgh_reply_port		msgh_local_port

#include <mach/std_types.h>
#include <device/device_types.h>
#include <device/net_status.h>

/* SimpleRoutine device_open_request */
mig_external kern_return_t device_open_request
(
	mach_port_t device_server_port,
	mach_port_t reply_port,
	dev_mode_t mode,
	dev_name_t name
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t modeType;
		dev_mode_t mode;
		mach_msg_type_long_t nameType;
		dev_name_t name;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t modeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_long_t nameType = {
	{
		/* msgt_name = */		0,
		/* msgt_size = */		0,
		/* msgt_number = */		0,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		TRUE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	},
		/* msgtl_name = */	12,
		/* msgtl_size = */	1024,
		/* msgtl_number = */	1,
	};

	InP->modeType = `\xcd\xf0\xf1qU;

	InP->mode = modemodeType;

	InP->nameType = `\xcd\xf0\xf1qU;

	(void) mig_strncpy(InP->name, namenameType, 128);

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, 21);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = device_server_port;
	InP->Head.msgh_reply_port = reply_port;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2800;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 172, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine device_write_request */
mig_external kern_return_t device_write_request
(
	mach_port_t device,
	mach_port_t reply_port,
	dev_mode_t mode,
	recnum_t recnum,
	io_buf_ptr_t data,
	mach_msg_type_number_t dataCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t modeType;
		dev_mode_t mode;
		mach_msg_type_t recnumType;
		recnum_t recnum;
		mach_msg_type_long_t dataType;
		io_buf_ptr_t data;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t modeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t recnumType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_long_t dataType = {
	{
		/* msgt_name = */		0,
		/* msgt_size = */		0,
		/* msgt_number = */		0,
		/* msgt_inline = */		FALSE,
		/* msgt_longform = */		TRUE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	},
		/* msgtl_name = */	9,
		/* msgtl_size = */	8,
		/* msgtl_number = */	0,
	};

	InP->modeType = `\xcd\xf0\xf1qU;

	InP->mode = modemodeType;

	InP->recnumType = `\xcd\xf0\xf1qU;

	InP->recnum = recnumrecnumType;

	InP->dataType = `\xcd\xf0\xf1qU;

	InP->data = datadataType;

	InP->dataType.msgtl_number = dataCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 21);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = device;
	InP->Head.msgh_reply_port = reply_port;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2802;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 60, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine device_write_request_inband */
mig_external kern_return_t device_write_request_inband
(
	mach_port_t device,
	mach_port_t reply_port,
	dev_mode_t mode,
	recnum_t recnum,
	io_buf_ptr_inband_t data,
	mach_msg_type_number_t dataCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t modeType;
		dev_mode_t mode;
		mach_msg_type_t recnumType;
		recnum_t recnum;
		mach_msg_type_t dataType;
		char data[128];
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;

	unsigned int msgh_size;

	static const mach_msg_type_t modeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t recnumType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t dataType = {
		/* msgt_name = */		8,
		/* msgt_size = */		8,
		/* msgt_number = */		128,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->modeType = `\xcd\xf0\xf1qU;

	InP->mode = modemodeType;

	InP->recnumType = `\xcd\xf0\xf1qU;

	InP->recnum = recnumrecnumType;

	InP->dataType = `\xcd\xf0\xf1qU;

	if (dataCnt > 128) {
		return MIG_ARRAY_TOO_LARGE;
	}
	else {
		memcpy(InP->data, data, dataCnt);
	}

	InP->dataType.msgt_number = dataCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	msgh_size = 44 + ((dataCnt + 3) & ~3);
	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, 21);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = device;
	InP->Head.msgh_reply_port = reply_port;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2803;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, msgh_size, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine device_read_request */
mig_external kern_return_t device_read_request
(
	mach_port_t device,
	mach_port_t reply_port,
	dev_mode_t mode,
	recnum_t recnum,
	int bytes_wanted
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t modeType;
		dev_mode_t mode;
		mach_msg_type_t recnumType;
		recnum_t recnum;
		mach_msg_type_t bytes_wantedType;
		int bytes_wanted;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t modeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t recnumType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t bytes_wantedType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->modeType = ;

	InP->mode = modemodeType;

	InP->recnumType = ;

	InP->recnum = recnumrecnumType;

	InP->bytes_wantedType = ;

	InP->bytes_wanted = bytes_wantedbytes_wantedType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, 21);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = device;
	InP->Head.msgh_reply_port = reply_port;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2804;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 48, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine device_read_request_inband */
mig_external kern_return_t device_read_request_inband
(
	mach_port_t device,
	mach_port_t reply_port,
	dev_mode_t mode,
	recnum_t recnum,
	int bytes_wanted
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t modeType;
		dev_mode_t mode;
		mach_msg_type_t recnumType;
		recnum_t recnum;
		mach_msg_type_t bytes_wantedType;
		int bytes_wanted;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t modeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t recnumType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t bytes_wantedType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->modeType = ;

	InP->mode = modemodeType;

	InP->recnumType = ;

	InP->recnum = recnumrecnumType;

	InP->bytes_wantedType = ;

	InP->bytes_wanted = bytes_wantedbytes_wantedType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, 21);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = device;
	InP->Head.msgh_reply_port = reply_port;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2805;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 48, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
