#include "notify_user.h"
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

/* SimpleRoutine mach_notify_port_deleted */
mig_external kern_return_t mach_notify_port_deleted
(
	mach_port_t notify,
	mach_port_t name
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t nameType;
		mach_port_t name;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->nameType =  \xaa\xcb\xe6rU;

	InP->name = namenameType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(18, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 65;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 32, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine mach_notify_msg_accepted */
mig_external kern_return_t mach_notify_msg_accepted
(
	mach_port_t notify,
	mach_port_t name
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t nameType;
		mach_port_t name;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->nameType =  \xaa\xcb\xe6rU;

	InP->name = namenameType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(18, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 66;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 32, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine mach_notify_port_destroyed */
mig_external kern_return_t mach_notify_port_destroyed
(
	mach_port_t notify,
	mach_port_t rights,
	mach_msg_type_name_t rightsPoly
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t rightsType;
		mach_port_t rights;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;

	boolean_t msgh_simple = TRUE;

	static const mach_msg_type_t rightsType = {
		/* msgt_name = */		-1,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->rightsType =  \xaa\xcb\xe6rU;

	InP->rights = rightsrightsType;

	if (MACH_MSG_TYPE_PORT_ANY(rightsPoly))
		msgh_simple = FALSE;

	InP->rightsType.msgt_name = rightsPoly\xe9|\xfe\xff\xffH\x8bChH\x8b\x80\x88;

	InP->Head.msgh_bits = msgh_simple ?
		MACH_MSGH_BITS(18, 0) :
		(MACH_MSGH_BITS_COMPLEX|
		 MACH_MSGH_BITS(18, 0));
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 69;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 32, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine mach_notify_no_senders */
mig_external kern_return_t mach_notify_no_senders
(
	mach_port_t notify,
	mach_port_mscount_t mscount
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t mscountType;
		mach_port_mscount_t mscount;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t mscountType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->mscountType =  \xaa\xcb\xe6rU;

	InP->mscount = mscountmscountType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(18, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 70;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 32, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine mach_notify_send_once */
mig_external kern_return_t mach_notify_send_once
(
	mach_port_t notify
)
{
	typedef struct {
		mach_msg_header_t Head;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	InP->Head.msgh_bits =
		MACH_MSGH_BITS(18, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 71;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 24, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine mach_notify_dead_name */
mig_external kern_return_t mach_notify_dead_name
(
	mach_port_t notify,
	mach_port_t name
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t nameType;
		mach_port_t name;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->nameType =  \xaa\xcb\xe6rU;

	InP->name = namenameType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(18, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = notify;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 72;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 32, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
