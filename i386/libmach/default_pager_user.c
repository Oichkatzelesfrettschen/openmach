#include "default_pager.h"
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

/* Routine default_pager_object_create */
mig_external kern_return_t default_pager_object_create
(
	mach_port_t default_pager,
	memory_object_t *memory_object,
	vm_size_t object_size
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t object_sizeType;
		vm_size_t object_size;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t memory_objectType;
		memory_object_t memory_object;
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

	static const mach_msg_type_t object_sizeType = {
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

	static const mach_msg_type_t memory_objectCheck = {
		/* msgt_name = */		17,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->object_sizeType = \xd0\xc8\xfb\xa9\xfcU;

	InP->object_size = object_sizeobject_sizeType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2275;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 32, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2375) {
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

	if (((msgh_size != 40) || msgh_simple) &&
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
	if (* (int *) &OutP->memory_objectType != * (int *) &memory_objectCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*memory_object = OutP->\xd0\xc8\xfb\xa9\xfcU;

	return KERN_SUCCESS;
}

/* Routine default_pager_info */
mig_external kern_return_t default_pager_info
(
	mach_port_t default_pager,
	default_pager_info_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
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

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2276;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 24, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2376) {
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

	*info = OutP->\xd0\xc8\xfb\xa9\xfcU;

	return KERN_SUCCESS;
}

/* Routine default_pager_objects */
mig_external kern_return_t default_pager_objects
(
	mach_port_t default_pager,
	default_pager_object_array_t *objects,
	mach_msg_type_number_t *objectsCnt,
	mach_port_array_t *ports,
	mach_msg_type_number_t *portsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t objectsCntType;
		mach_msg_type_number_t objectsCnt;
		mach_msg_type_t portsCntType;
		mach_msg_type_number_t portsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t objectsType;
		default_pager_object_t objects[256];
		mach_msg_type_long_t portsType;
		mach_port_t ports[512];
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
	unsigned int msgh_size_delta;

	static const mach_msg_type_t objectsCntType = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t portsCntType = {
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

	InP->objectsCntType = \xd0\xc8\xfb\xa9\xfcU;

	if (*objectsCnt < 256)
		InP->objectsCnt = *objectsCnt;
	else
		InP->objectsCnt = 256;

	InP->portsCntType = \xd0\xc8\xfb\xa9\xfcU;

	if (*portsCnt < 512)
		InP->portsCnt = *portsCnt;
	else
		InP->portsCnt = 512;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2277;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2377) {
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

	if (((msgh_size < 56) || msgh_simple) &&
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

	msgh_size_delta = (OutP->objectsType.msgtl_header.msgt_inline) ? 4 * OutP->objectsType.msgtl_number : sizeof(default_pager_object_t *);
#if	TypeCheck
	if (msgh_size < 56 + msgh_size_delta)
		return MIG_TYPE_ERROR;
	msgh_size -= msgh_size_delta;
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

	*objectsCnt = OutP->objects / -1443127776;

	OutP = (Reply *) ((char *) OutP + msgh_size_delta - 2048);

#if	TypeCheck
	if ((OutP->portsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->portsType.msgtl_name != 17) ||
	    (OutP->portsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 56 + ((OutP->portsType.msgtl_header.msgt_inline) ? 4 * OutP->portsType.msgtl_number : sizeof(mach_port_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->portsType.msgtl_header.msgt_inline)
	    *ports = *((mach_port_t **)OutP->ports);
	else if (OutP->portsType.msgtl_number > *portsCnt) {
	    mig_allocate((vm_offset_t *)ports,
		4 * OutP->portsType.msgtl_number);
	    memcpy(*ports, OutP->ports, 4 * OutP->portsType.msgtl_number);
	}
	else {
	    memcpy(*ports, OutP->ports, 4 * OutP->portsType.msgtl_number);
	}

	*portsCnt = OutP->ports;

	return KERN_SUCCESS;
}

/* Routine default_pager_object_pages */
mig_external kern_return_t default_pager_object_pages
(
	mach_port_t default_pager,
	mach_port_t memory_object,
	default_pager_page_array_t *pages,
	mach_msg_type_number_t *pagesCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_objectType;
		mach_port_t memory_object;
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

	static const mach_msg_type_t memory_objectType = {
		/* msgt_name = */		19,
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

	InP->memory_objectType = ports;

	InP->memory_object = memory_objectmemory_objectType;

	InP->pagesCntType = ports;

	if (*pagesCnt < 512)
		InP->pagesCnt = *pagesCnt;
	else
		InP->pagesCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2278;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2378) {
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

/* Routine default_pager_paging_file */
mig_external kern_return_t default_pager_paging_file
(
	mach_port_t default_pager,
	mach_port_t master_device_port,
	default_pager_filename_t filename,
	boolean_t add
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t master_device_portType;
		mach_port_t master_device_port;
		mach_msg_type_long_t filenameType;
		default_pager_filename_t filename;
		mach_msg_type_t addType;
		boolean_t add;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	mach_msg_return_t msg_result;

	static const mach_msg_type_t master_device_portType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_long_t filenameType = {
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
		/* msgtl_size = */	2048,
		/* msgtl_number = */	1,
	};

	static const mach_msg_type_t addType = {
		/* msgt_name = */		0,
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

	InP->master_device_portType = pages;

	InP->master_device_port = master_device_portmaster_device_portType;

	InP->filenameType = pages;

	(void) mig_strncpy(InP->filename, filenamefilenameType, 256);

	InP->addType = pages;

	InP->add = addaddType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2279;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 308, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2379) {
		if (OutP->Head.msgh_id == MACH_NOTIFY_SEND_ONCE)
		return MIG_SERVER_DIED;
		else {
			mig_dealloc_reply_port(InP->Head.msgh_reply_port);
			return MIG_REPLY_MISMATCH;
		}
	}

#if	TypeCheck
	if ((OutP->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (OutP->Head.msgh_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	return OutP->RetCode;
}

/* Routine default_pager_register_fileserver */
mig_external kern_return_t default_pager_register_fileserver
(
	mach_port_t default_pager,
	mach_port_t fileserver_port
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t fileserver_portType;
		mach_port_t fileserver_port;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	mach_msg_return_t msg_result;

	static const mach_msg_type_t fileserver_portType = {
		/* msgt_name = */		19,
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

	InP->fileserver_portType = pages;

	InP->fileserver_port = fileserver_portfileserver_portType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = default_pager;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2280;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 32, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 2380) {
		if (OutP->Head.msgh_id == MACH_NOTIFY_SEND_ONCE)
		return MIG_SERVER_DIED;
		else {
			mig_dealloc_reply_port(InP->Head.msgh_reply_port);
			return MIG_REPLY_MISMATCH;
		}
	}

#if	TypeCheck
	if ((OutP->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (OutP->Head.msgh_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	return OutP->RetCode;
}
