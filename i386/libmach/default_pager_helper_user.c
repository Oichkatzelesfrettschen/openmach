#include "default_pager_helper.h"
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

/* SimpleRoutine dp_helper_paging_space */
mig_external kern_return_t dp_helper_paging_space
(
	mach_port_t dp_helper,
	boolean_t space_shortage,
	vm_size_t approx_amount
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t space_shortageType;
		boolean_t space_shortage;
		mach_msg_type_t approx_amountType;
		vm_size_t approx_amount;
	} Request;

	union {
		Request In;
	} Mess;

	register Request *InP = &Mess.In;


	static const mach_msg_type_t space_shortageType = {
		/* msgt_name = */		0,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t approx_amountType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->space_shortageType = \xd0KF\x8cU;

	InP->space_shortage = space_shortagespace_shortageType;

	InP->approx_amountType = \xd0KF\x8cU;

	InP->approx_amount = approx_amountapprox_amountType;

	InP->Head.msgh_bits =
		MACH_MSGH_BITS(19, 0);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = dp_helper;
	InP->Head.msgh_reply_port = MACH_PORT_NULL;
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 888888;

	return mach_msg(&InP->Head, MACH_SEND_MSG|MACH_MSG_OPTION_NONE, 40, 0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
