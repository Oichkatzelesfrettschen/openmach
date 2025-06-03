#include "memory_object_default.h"
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

/* SimpleRoutine memory_object_create */
mig_external kern_return_t memory_object_create
(
	mach_port_t old_memory_object,
	mach_port_t new_memory_object,
	vm_size_t new_object_size,
	mach_port_t new_control_port,
	mach_port_t new_name,
	vm_size_t new_page_size
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t new_memory_objectType;
		mach_port_t new_memory_object;
		mach_msg_type_t new_object_sizeType;
		vm_size_t new_object_size;
		mach_msg_type_t new_control_portType;
		mach_port_t new_control_port;
		mach_msg_type_t new_nameType;
		mach_port_t new_name;
		mach_msg_type_t new_page_sizeType;
		vm_size_t new_page_size;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t new_memory_objectType = {
		/* msgt_name = */		16,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t new_object_sizeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t new_control_portType = {
		/* msgt_name = */		20,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t new_nameType = {
		/* msgt_name = */		20,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t new_page_sizeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->new_memory_objectType = 0\xde![U;

	InP->new_memory_object = new_memory_objectnew_memory_objectType;

	InP->new_object_sizeType = 0\xde![U;

	InP->new_object_size = new_object_sizenew_object_sizeType;

	InP->new_control_portType = 0\xde![U;

	InP->new_control_port = new_control_portnew_control_portType;

	InP->new_nameType = 0\xde![U;

	InP->new_name = new_namenew_nameType;

	InP->new_page_sizeType = 0\xde![U;

	InP->new_page_size = new_page_sizenew_page_sizeType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(17, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = old_memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2250;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 64, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_data_initialize */
mig_external kern_return_t memory_object_data_initialize
(
	mach_port_t memory_object,
	mach_port_t memory_control_port,
	vm_offset_t offset,
	vm_offset_t data,
	mach_msg_type_number_t dataCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_control_portType;
		mach_port_t memory_control_port;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_long_t dataType;
		vm_offset_t data;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_control_portType = {
		/* msgt_name = */		20,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t offsetType = {
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

	InP->memory_control_portType = 0\xde![U;

	InP->memory_control_port = memory_control_portmemory_control_portType;

	InP->offsetType = 0\xde![U;

	InP->offset = offsetoffsetType;

	InP->dataType = 0\xde![U;

	InP->data = datadataType;

	InP->dataType.msgtl_number = dataCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2251;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 60, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
