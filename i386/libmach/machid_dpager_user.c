#include "machid_dpager.h"
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
#include <mach/mach_types.h>
#include <mach/default_pager_types.h>
#include <servers/machid_types.h>

/* Routine default_pager_info */
mig_external kern_return_t machid_default_pager_info
(
	mach_port_t server,
	mach_port_t auth,
	mdefault_pager_t default_pager,
	default_pager_info_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t default_pagerType;
		mdefault_pager_t default_pager;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		default_pager_info_t info;
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	mach_msg_return_t msg_result;
#if	TypeCheck
	unsigned int msgh_size;
#endif	/* TypeCheck */

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t default_pagerType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t RetCodeCheck = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t infoCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		3,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xb0\xd2p\xefgU;

	InP->auth = authauthType;

	InP->default_pagerType = \xb0\xd2p\xefgU;

	InP->default_pager = default_pagerdefault_pagerType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 6357721;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 6357821) {
		if (OutP->Head.msgh_id == MACH_NOTIFY_SEND_ONCE)
		return MIG_SERVER_DIED;
		else {
			mig_dealloc_reply_port(InP->Head.msgh_reply_port);
			return MIG_REPLY_MISMATCH;
		}
	}

#if	TypeCheck
	msgh_size = OutP->Head.msgh_size;

	if ((OutP->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    ((msgh_size != 48) &&
	     ((msgh_size != sizeof(mig_reply_header_t)) ||
	      (OutP->RetCode == KERN_SUCCESS))))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (OutP->RetCode != KERN_SUCCESS)
		return OutP->RetCode;

#if	TypeCheck
	if (* (int *) &OutP->infoType != * (int *) &infoCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*info = OutP->\xb0\xd2p\xefgU;

	return KERN_SUCCESS;
}

/* Routine default_pager_objects */
mig_external kern_return_t machid_default_pager_objects
(
	mach_port_t server,
	mach_port_t auth,
	mdefault_pager_t default_pager,
	default_pager_object_array_t *objects,
	mach_msg_type_number_t *objectsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t default_pagerType;
		mdefault_pager_t default_pager;
		mach_msg_type_t objectsCntType;
		mach_msg_type_number_t objectsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t objectsType;
		default_pager_object_t objects[256];
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	mach_msg_return_t msg_result;
#if	TypeCheck
	boolean_t msgh_simple;
#endif	/* TypeCheck */
#if	TypeCheck
	unsigned int msgh_size;
#endif	/* TypeCheck */

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t default_pagerType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t objectsCntType = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t RetCodeCheck = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xb0\xd2p\xefgU;

	InP->auth = authauthType;

	InP->default_pagerType = \xb0\xd2p\xefgU;

	InP->default_pager = default_pagerdefault_pagerType;

	InP->objectsCntType = \xb0\xd2p\xefgU;

	if (*objectsCnt < 256)
		InP->objectsCnt = *objectsCnt;
	else
		InP->objectsCnt = 256;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 6357722;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 6357822) {
		if (OutP->Head.msgh_id == MACH_NOTIFY_SEND_ONCE)
		return MIG_SERVER_DIED;
		else {
			mig_dealloc_reply_port(InP->Head.msgh_reply_port);
			return MIG_REPLY_MISMATCH;
		}
	}

#if	TypeCheck
	msgh_size = OutP->Head.msgh_size;
	msgh_simple = !(OutP->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX);

	if (((msgh_size < 44)) &&
	    ((msgh_size != sizeof(mig_reply_header_t)) ||
	     !msgh_simple ||
	     (OutP->RetCode == KERN_SUCCESS)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (OutP->RetCode != KERN_SUCCESS)
		return OutP->RetCode;

#if	TypeCheck
	if ((OutP->objectsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->objectsType.msgtl_name != 2) ||
	    (OutP->objectsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->objectsType.msgtl_header.msgt_inline) ? 4 * OutP->objectsType.msgtl_number : sizeof(default_pager_object_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->objectsType.msgtl_header.msgt_inline)
	    *objects = *((default_pager_object_t **)OutP->objects);
	else if (OutP->objectsType.msgtl_number / 2 > *objectsCnt) {
	    mig_allocate((vm_offset_t *)objects,
		4 * OutP->objectsType.msgtl_number);
	    memcpy(*objects, OutP->objects, 4 * OutP->objectsType.msgtl_number);
	}
	else {
	    memcpy(*objects, OutP->objects, 4 * OutP->objectsType.msgtl_number);
	}

	*objectsCnt = OutP->objects / -277825232;

	return KERN_SUCCESS;
}

/* Routine default_pager_object_pages */
mig_external kern_return_t machid_default_pager_object_pages
(
	mach_port_t server,
	mach_port_t auth,
	mdefault_pager_t default_pager,
	mobject_name_t object,
	default_pager_page_array_t *pages,
	mach_msg_type_number_t *pagesCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t default_pagerType;
		mdefault_pager_t default_pager;
		mach_msg_type_t objectType;
		mobject_name_t object;
		mach_msg_type_t pagesCntType;
		mach_msg_type_number_t pagesCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t pagesType;
		default_pager_page_t pages[512];
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	mach_msg_return_t msg_result;
#if	TypeCheck
	boolean_t msgh_simple;
#endif	/* TypeCheck */
#if	TypeCheck
	unsigned int msgh_size;
#endif	/* TypeCheck */

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t default_pagerType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t objectType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t pagesCntType = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t RetCodeCheck = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = objects;

	InP->auth = authauthType;

	InP->default_pagerType = objects;

	InP->default_pager = default_pagerdefault_pagerType;

	InP->objectType = objects;

	InP->object = objectobjectType;

	InP->pagesCntType = objects;

	if (*pagesCnt < 512)
		InP->pagesCnt = *pagesCnt;
	else
		InP->pagesCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 6357723;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 6357823) {
		if (OutP->Head.msgh_id == MACH_NOTIFY_SEND_ONCE)
		return MIG_SERVER_DIED;
		else {
			mig_dealloc_reply_port(InP->Head.msgh_reply_port);
			return MIG_REPLY_MISMATCH;
		}
	}

#if	TypeCheck
	msgh_size = OutP->Head.msgh_size;
	msgh_simple = !(OutP->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX);

	if (((msgh_size < 44)) &&
	    ((msgh_size != sizeof(mig_reply_header_t)) ||
	     !msgh_simple ||
	     (OutP->RetCode == KERN_SUCCESS)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (OutP->RetCode != KERN_SUCCESS)
		return OutP->RetCode;

#if	TypeCheck
	if ((OutP->pagesType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->pagesType.msgtl_name != 2) ||
	    (OutP->pagesType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->pagesType.msgtl_header.msgt_inline) ? 4 * OutP->pagesType.msgtl_number : sizeof(default_pager_page_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->pagesType.msgtl_header.msgt_inline)
	    *pages = *((default_pager_page_t **)OutP->pages);
	else if (OutP->pagesType.msgtl_number > *pagesCnt) {
	    mig_allocate((vm_offset_t *)pages,
		4 * OutP->pagesType.msgtl_number);
	    memcpy(*pages, OutP->pages, 4 * OutP->pagesType.msgtl_number);
	}
	else {
	    memcpy(*pages, OutP->pages, 4 * OutP->pagesType.msgtl_number);
	}

	*pagesCnt = OutP->pages;

	return KERN_SUCCESS;
}
