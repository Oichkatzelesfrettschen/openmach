#include "memory_object_user.h"
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

/* SimpleRoutine memory_object_init */
mig_external kern_return_t memory_object_init
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	mach_port_t memory_object_name,
	vm_size_t memory_object_page_size
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t memory_object_nameType;
		mach_port_t memory_object_name;
		mach_msg_type_t memory_object_page_sizeType;
		vm_size_t memory_object_page_size;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
		/* msgt_name = */		20,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t memory_object_nameType = {
		/* msgt_name = */		20,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t memory_object_page_sizeType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->memory_object_nameType = \x90L\xd52V;

	InP->memory_object_name = memory_object_namememory_object_nameType;

	InP->memory_object_page_sizeType = \x90L\xd52V;

	InP->memory_object_page_size = memory_object_page_sizememory_object_page_sizeType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2200;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 48, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_terminate */
mig_external kern_return_t memory_object_terminate
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	mach_port_t memory_object_name
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t memory_object_nameType;
		mach_port_t memory_object_name;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
		/* msgt_name = */		16,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t memory_object_nameType = {
		/* msgt_name = */		16,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->memory_object_nameType = \x90L\xd52V;

	InP->memory_object_name = memory_object_namememory_object_nameType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(17, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2201;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 40, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_copy */
mig_external kern_return_t memory_object_copy
(
	mach_port_t old_memory_object,
	mach_port_t old_memory_control,
	vm_offset_t offset,
	vm_size_t length,
	mach_port_t new_memory_object
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t old_memory_controlType;
		mach_port_t old_memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_t lengthType;
		vm_size_t length;
		mach_msg_type_t new_memory_objectType;
		mach_port_t new_memory_object;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t old_memory_controlType = {
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

	static const mach_msg_type_t lengthType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t new_memory_objectType = {
		/* msgt_name = */		16,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->old_memory_controlType = \x90L\xd52V;

	InP->old_memory_control = old_memory_controlold_memory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->lengthType = \x90L\xd52V;

	InP->length = lengthlengthType;

	InP->new_memory_objectType = \x90L\xd52V;

	InP->new_memory_object = new_memory_objectnew_memory_objectType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = old_memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2202;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 56, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_data_request */
mig_external kern_return_t memory_object_data_request
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_size_t length,
	vm_prot_t desired_access
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_t lengthType;
		vm_size_t length;
		mach_msg_type_t desired_accessType;
		vm_prot_t desired_access;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	static const mach_msg_type_t lengthType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t desired_accessType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->lengthType = \x90L\xd52V;

	InP->length = lengthlengthType;

	InP->desired_accessType = \x90L\xd52V;

	InP->desired_access = desired_accessdesired_accessType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2203;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 56, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_data_unlock */
mig_external kern_return_t memory_object_data_unlock
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_size_t length,
	vm_prot_t desired_access
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_t lengthType;
		vm_size_t length;
		mach_msg_type_t desired_accessType;
		vm_prot_t desired_access;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	static const mach_msg_type_t lengthType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t desired_accessType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->lengthType = \x90L\xd52V;

	InP->length = lengthlengthType;

	InP->desired_accessType = \x90L\xd52V;

	InP->desired_access = desired_accessdesired_accessType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2204;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 56, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_data_write */
mig_external kern_return_t memory_object_data_write
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_offset_t data,
	mach_msg_type_number_t dataCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_long_t dataType;
		vm_offset_t data;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->dataType = \x90L\xd52V;

	InP->data = datadataType;

	InP->dataType.msgtl_number = dataCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2205;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 60, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_lock_completed */
mig_external kern_return_t memory_object_lock_completed
(
	mach_port_t memory_object,
	mach_msg_type_name_t memory_objectPoly,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_size_t length
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_t lengthType;
		vm_size_t length;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	static const mach_msg_type_t lengthType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->lengthType = \x90L\xd52V;

	InP->length = lengthlengthType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(memory_objectPoly, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2206;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 48, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_supply_completed */
mig_external kern_return_t memory_object_supply_completed
(
	mach_port_t memory_object,
	mach_msg_type_name_t memory_objectPoly,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_size_t length,
	kern_return_t result,
	vm_offset_t error_offset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_t lengthType;
		vm_size_t length;
		mach_msg_type_t resultType;
		kern_return_t result;
		mach_msg_type_t error_offsetType;
		vm_offset_t error_offset;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	static const mach_msg_type_t lengthType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t resultType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t error_offsetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->lengthType = \x90L\xd52V;

	InP->length = lengthlengthType;

	InP->resultType = \x90L\xd52V;

	InP->result = resultresultType;

	InP->error_offsetType = \x90L\xd52V;

	InP->error_offset = error_offseterror_offsetType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(memory_objectPoly, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2207;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 64, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_data_return */
mig_external kern_return_t memory_object_data_return
(
	mach_port_t memory_object,
	mach_port_t memory_control,
	vm_offset_t offset,
	vm_offset_t data,
	mach_msg_type_number_t dataCnt,
	boolean_t dirty,
	boolean_t kernel_copy
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t memory_controlType;
		mach_port_t memory_control;
		mach_msg_type_t offsetType;
		vm_offset_t offset;
		mach_msg_type_long_t dataType;
		vm_offset_t data;
		mach_msg_type_t dirtyType;
		boolean_t dirty;
		mach_msg_type_t kernel_copyType;
		boolean_t kernel_copy;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t memory_controlType = {
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

	static const mach_msg_type_t dirtyType = {
		/* msgt_name = */		0,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t kernel_copyType = {
		/* msgt_name = */		0,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->memory_controlType = \x90L\xd52V;

	InP->memory_control = memory_controlmemory_controlType;

	InP->offsetType = \x90L\xd52V;

	InP->offset = offsetoffsetType;

	InP->dataType = \x90L\xd52V;

	InP->data = datadataType;

	InP->dataType.msgtl_number = dataCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	InP->dirtyType = \x90L\xd52V;

	InP->dirty = dirtydirtyType;

	InP->kernel_copyType = \x90L\xd52V;

	InP->kernel_copy = kernel_copykernel_copyType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2208;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 76, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}

/* SimpleRoutine memory_object_change_completed */
mig_external kern_return_t memory_object_change_completed
(
	mach_port_t memory_object,
	mach_msg_type_name_t memory_objectPoly,
	boolean_t may_cache,
	memory_object_copy_strategy_t copy_strategy
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t may_cacheType;
		boolean_t may_cache;
		mach_msg_type_t copy_strategyType;
		memory_object_copy_strategy_t copy_strategy;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t may_cacheType = {
		/* msgt_name = */		0,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t copy_strategyType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->may_cacheType = \x90L\xd52V;

	InP->may_cache = may_cachemay_cacheType;

	InP->copy_strategyType = \x90L\xd52V;

	InP->copy_strategy = copy_strategycopy_strategyType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(memory_objectPoly, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = memory_object;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 2209;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 40, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
