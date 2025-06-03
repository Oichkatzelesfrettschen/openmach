#include "machid.h"
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
#include <servers/machid_types.h>

/* Routine mach_type */
mig_external kern_return_t machid_mach_type
(
	mach_port_t server,
	mach_port_t auth,
	mach_id_t id,
	mach_type_t *mtype
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t idType;
		mach_id_t id;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t mtypeType;
		mach_type_t mtype;
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

	static const mach_msg_type_t idType = {
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

	static const mach_msg_type_t mtypeCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->idType = \xd0y\xc3\xd6-V;

	InP->id = ididType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829283;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829383) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->mtypeType != * (int *) &mtypeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*mtype = OutP->\xd0y\xc3\xd6-V;

	return KERN_SUCCESS;
}

/* Routine mach_register */
mig_external kern_return_t machid_mach_register
(
	mach_port_t server,
	mach_port_t auth,
	mach_port_t port,
	mach_type_t mtype,
	mach_id_t *id
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t portType;
		mach_port_t port;
		mach_msg_type_t mtypeType;
		mach_type_t mtype;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t idType;
		mach_id_t id;
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

	static const mach_msg_type_t portType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t mtypeType = {
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

	static const mach_msg_type_t idCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->portType = \xd0y\xc3\xd6-V;

	InP->port = portportType;

	InP->mtypeType = \xd0y\xc3\xd6-V;

	InP->mtype = mtypemtypeType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829284;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829384) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->idType != * (int *) &idCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*id = OutP->\xd0y\xc3\xd6-V;

	return KERN_SUCCESS;
}

/* Routine mach_lookup */
mig_external kern_return_t machid_mach_lookup
(
	mach_port_t server,
	mach_port_t auth,
	mach_id_t name,
	mach_type_t atype,
	mach_id_t *aname
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t nameType;
		mach_id_t name;
		mach_msg_type_t atypeType;
		mach_type_t atype;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t anameType;
		mach_id_t aname;
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

	static const mach_msg_type_t nameType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t atypeType = {
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

	static const mach_msg_type_t anameCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->nameType = \xd0y\xc3\xd6-V;

	InP->name = namenameType;

	InP->atypeType = \xd0y\xc3\xd6-V;

	InP->atype = atypeatypeType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829285;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829385) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->anameType != * (int *) &anameCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*aname = OutP->\xd0y\xc3\xd6-V;

	return KERN_SUCCESS;
}

/* Routine mach_port */
mig_external kern_return_t machid_mach_port
(
	mach_port_t server,
	mach_port_t auth,
	mach_id_t name,
	mach_port_t *port
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t nameType;
		mach_id_t name;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t portType;
		mach_port_t port;
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

	static const mach_msg_type_t nameType = {
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

	static const mach_msg_type_t portCheck = {
		/* msgt_name = */		17,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->nameType = \xd0y\xc3\xd6-V;

	InP->name = namenameType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829286;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829386) {
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
	if (* (int *) &OutP->portType != * (int *) &portCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*port = OutP->\xd0y\xc3\xd6-V;

	return KERN_SUCCESS;
}

/* Routine host_ports */
mig_external kern_return_t machid_host_ports
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t *host,
	mhost_priv_t *phost
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
		mach_msg_type_t phostType;
		mhost_priv_t phost;
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

	static const mach_msg_type_t RetCodeCheck = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t phostCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829287;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 32, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829387) {
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->\xd0y\xc3\xd6-V;

#if	TypeCheck
	if (* (int *) &OutP->phostType != * (int *) &phostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*phost = OutP->\xd0y\xc3\xd6-V;

	return KERN_SUCCESS;
}

/* Routine host_processor_sets */
mig_external kern_return_t machid_host_processor_sets
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mprocessor_set_array_t *sets,
	mach_msg_type_number_t *setsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
		mach_msg_type_t setsCntType;
		mach_msg_type_number_t setsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t setsType;
		mprocessor_set_t sets[512];
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t setsCntType = {
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

	InP->authType = \xd0y\xc3\xd6-V;

	InP->auth = authauthType;

	InP->hostType = \xd0y\xc3\xd6-V;

	InP->host = hosthostType;

	InP->setsCntType = \xd0y\xc3\xd6-V;

	if (*setsCnt < 512)
		InP->setsCnt = *setsCnt;
	else
		InP->setsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829288;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829388) {
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
	if ((OutP->setsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->setsType.msgtl_name != 2) ||
	    (OutP->setsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->setsType.msgtl_header.msgt_inline) ? 4 * OutP->setsType.msgtl_number : sizeof(mprocessor_set_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->setsType.msgtl_header.msgt_inline)
	    *sets = *((mprocessor_set_t **)OutP->sets);
	else if (OutP->setsType.msgtl_number > *setsCnt) {
	    mig_allocate((vm_offset_t *)sets,
		4 * OutP->setsType.msgtl_number);
	    memcpy(*sets, OutP->sets, 4 * OutP->setsType.msgtl_number);
	}
	else {
	    memcpy(*sets, OutP->sets, 4 * OutP->setsType.msgtl_number);
	}

	*setsCnt = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine host_tasks */
mig_external kern_return_t machid_host_tasks
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mtask_array_t *tasks,
	mach_msg_type_number_t *tasksCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
		mach_msg_type_t tasksCntType;
		mach_msg_type_number_t tasksCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t tasksType;
		mtask_t tasks[512];
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t tasksCntType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->hostType = sets;

	InP->host = hosthostType;

	InP->tasksCntType = sets;

	if (*tasksCnt < 512)
		InP->tasksCnt = *tasksCnt;
	else
		InP->tasksCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829289;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829389) {
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
	if ((OutP->tasksType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->tasksType.msgtl_name != 2) ||
	    (OutP->tasksType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->tasksType.msgtl_header.msgt_inline) ? 4 * OutP->tasksType.msgtl_number : sizeof(mtask_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->tasksType.msgtl_header.msgt_inline)
	    *tasks = *((mtask_t **)OutP->tasks);
	else if (OutP->tasksType.msgtl_number > *tasksCnt) {
	    mig_allocate((vm_offset_t *)tasks,
		4 * OutP->tasksType.msgtl_number);
	    memcpy(*tasks, OutP->tasks, 4 * OutP->tasksType.msgtl_number);
	}
	else {
	    memcpy(*tasks, OutP->tasks, 4 * OutP->tasksType.msgtl_number);
	}

	*tasksCnt = OutP->tasks;

	return KERN_SUCCESS;
}

/* Routine host_threads */
mig_external kern_return_t machid_host_threads
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mthread_array_t *threads,
	mach_msg_type_number_t *threadsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
		mach_msg_type_t threadsCntType;
		mach_msg_type_number_t threadsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t threadsType;
		mthread_t threads[512];
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadsCntType = {
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

	InP->authType = tasks;

	InP->auth = authauthType;

	InP->hostType = tasks;

	InP->host = hosthostType;

	InP->threadsCntType = tasks;

	if (*threadsCnt < 512)
		InP->threadsCnt = *threadsCnt;
	else
		InP->threadsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829290;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829390) {
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
	if ((OutP->threadsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->threadsType.msgtl_name != 2) ||
	    (OutP->threadsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->threadsType.msgtl_header.msgt_inline) ? 4 * OutP->threadsType.msgtl_number : sizeof(mthread_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->threadsType.msgtl_header.msgt_inline)
	    *threads = *((mthread_t **)OutP->threads);
	else if (OutP->threadsType.msgtl_number > *threadsCnt) {
	    mig_allocate((vm_offset_t *)threads,
		4 * OutP->threadsType.msgtl_number);
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}
	else {
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}

	*threadsCnt = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine host_processors */
mig_external kern_return_t machid_host_processors
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mprocessor_array_t *procs,
	mach_msg_type_number_t *procsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
		mach_msg_type_t procsCntType;
		mach_msg_type_number_t procsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t procsType;
		mprocessor_t procs[512];
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t procsCntType = {
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

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->procsCntType = threads;

	if (*procsCnt < 512)
		InP->procsCnt = *procsCnt;
	else
		InP->procsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829291;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829391) {
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
	if ((OutP->procsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->procsType.msgtl_name != 2) ||
	    (OutP->procsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->procsType.msgtl_header.msgt_inline) ? 4 * OutP->procsType.msgtl_number : sizeof(mprocessor_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->procsType.msgtl_header.msgt_inline)
	    *procs = *((mprocessor_t **)OutP->procs);
	else if (OutP->procsType.msgtl_number > *procsCnt) {
	    mig_allocate((vm_offset_t *)procs,
		4 * OutP->procsType.msgtl_number);
	    memcpy(*procs, OutP->procs, 4 * OutP->procsType.msgtl_number);
	}
	else {
	    memcpy(*procs, OutP->procs, 4 * OutP->procsType.msgtl_number);
	}

	*procsCnt = OutP->procs;

	return KERN_SUCCESS;
}

/* Routine processor_set_threads */
mig_external kern_return_t machid_processor_set_threads
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t pset,
	mthread_array_t *threads,
	mach_msg_type_number_t *threadsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t threadsCntType;
		mach_msg_type_number_t threadsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t threadsType;
		mthread_t threads[512];
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

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadsCntType = {
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

	InP->authType = procs;

	InP->auth = authauthType;

	InP->psetType = procs;

	InP->pset = psetpsetType;

	InP->threadsCntType = procs;

	if (*threadsCnt < 512)
		InP->threadsCnt = *threadsCnt;
	else
		InP->threadsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829292;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829392) {
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
	if ((OutP->threadsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->threadsType.msgtl_name != 2) ||
	    (OutP->threadsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->threadsType.msgtl_header.msgt_inline) ? 4 * OutP->threadsType.msgtl_number : sizeof(mthread_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->threadsType.msgtl_header.msgt_inline)
	    *threads = *((mthread_t **)OutP->threads);
	else if (OutP->threadsType.msgtl_number > *threadsCnt) {
	    mig_allocate((vm_offset_t *)threads,
		4 * OutP->threadsType.msgtl_number);
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}
	else {
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}

	*threadsCnt = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine processor_set_tasks */
mig_external kern_return_t machid_processor_set_tasks
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t pset,
	mtask_array_t *tasks,
	mach_msg_type_number_t *tasksCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t tasksCntType;
		mach_msg_type_number_t tasksCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t tasksType;
		mtask_t tasks[512];
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

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t tasksCntType = {
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

	InP->authType = threads;

	InP->auth = authauthType;

	InP->psetType = threads;

	InP->pset = psetpsetType;

	InP->tasksCntType = threads;

	if (*tasksCnt < 512)
		InP->tasksCnt = *tasksCnt;
	else
		InP->tasksCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829293;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829393) {
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
	if ((OutP->tasksType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->tasksType.msgtl_name != 2) ||
	    (OutP->tasksType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->tasksType.msgtl_header.msgt_inline) ? 4 * OutP->tasksType.msgtl_number : sizeof(mtask_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->tasksType.msgtl_header.msgt_inline)
	    *tasks = *((mtask_t **)OutP->tasks);
	else if (OutP->tasksType.msgtl_number > *tasksCnt) {
	    mig_allocate((vm_offset_t *)tasks,
		4 * OutP->tasksType.msgtl_number);
	    memcpy(*tasks, OutP->tasks, 4 * OutP->tasksType.msgtl_number);
	}
	else {
	    memcpy(*tasks, OutP->tasks, 4 * OutP->tasksType.msgtl_number);
	}

	*tasksCnt = OutP->tasks;

	return KERN_SUCCESS;
}

/* Routine task_threads */
mig_external kern_return_t machid_task_threads
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mthread_array_t *threads,
	mach_msg_type_number_t *threadsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t threadsCntType;
		mach_msg_type_number_t threadsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t threadsType;
		mthread_t threads[512];
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadsCntType = {
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

	InP->authType = tasks;

	InP->auth = authauthType;

	InP->taskType = tasks;

	InP->task = tasktaskType;

	InP->threadsCntType = tasks;

	if (*threadsCnt < 512)
		InP->threadsCnt = *threadsCnt;
	else
		InP->threadsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829294;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829394) {
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
	if ((OutP->threadsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->threadsType.msgtl_name != 2) ||
	    (OutP->threadsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->threadsType.msgtl_header.msgt_inline) ? 4 * OutP->threadsType.msgtl_number : sizeof(mthread_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->threadsType.msgtl_header.msgt_inline)
	    *threads = *((mthread_t **)OutP->threads);
	else if (OutP->threadsType.msgtl_number > *threadsCnt) {
	    mig_allocate((vm_offset_t *)threads,
		4 * OutP->threadsType.msgtl_number);
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}
	else {
	    memcpy(*threads, OutP->threads, 4 * OutP->threadsType.msgtl_number);
	}

	*threadsCnt = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine host_basic_info */
mig_external kern_return_t machid_host_basic_info
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	host_basic_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		host_basic_info_data_t info;
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

	static const mach_msg_type_t hostType = {
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
		/* msgt_number = */		5,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829295;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829395) {
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
	    ((msgh_size != 56) &&
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

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine host_sched_info */
mig_external kern_return_t machid_host_sched_info
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	host_sched_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		host_sched_info_data_t info;
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

	static const mach_msg_type_t hostType = {
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
		/* msgt_number = */		2,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829296;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829396) {
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
	    ((msgh_size != 44) &&
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

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine host_load_info */
mig_external kern_return_t machid_host_load_info
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	host_load_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		host_load_info_data_t info;
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

	static const mach_msg_type_t hostType = {
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
		/* msgt_number = */		6,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829297;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829397) {
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
	    ((msgh_size != 60) &&
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

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine processor_set_default */
mig_external kern_return_t machid_processor_set_default
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	mprocessor_set_name_t *pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
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

	static const mach_msg_type_t hostType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829298;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829398) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine host_kernel_version */
mig_external kern_return_t machid_host_kernel_version
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	kernel_version_t kernel_version
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t kernel_versionType;
		kernel_version_t kernel_version;
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

	static const mach_msg_type_t hostType = {
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

	InP->authType = threads;

	InP->auth = authauthType;

	InP->hostType = threads;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829299;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829399) {
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
	    ((msgh_size != 556) &&
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
	if ((OutP->kernel_versionType.msgtl_header.msgt_inline != TRUE) ||
	    (OutP->kernel_versionType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->kernel_versionType.msgtl_name != 12) ||
	    (OutP->kernel_versionType.msgtl_number != 1) ||
	    (OutP->kernel_versionType.msgtl_size != 4096))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	(void) mig_strncpy(kernel_version, OutP->threads, 512);

	return KERN_SUCCESS;
}

/* Routine processor_basic_info */
mig_external kern_return_t machid_processor_basic_info
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t proc,
	mhost_t *host,
	processor_basic_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t procType;
		mprocessor_t proc;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
		mach_msg_type_t infoType;
		processor_basic_info_data_t info;
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

	static const mach_msg_type_t procType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
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
		/* msgt_number = */		5,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->procType = threads;

	InP->proc = procprocType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829300;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829400) {
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
	    ((msgh_size != 64) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->threads;

#if	TypeCheck
	if (* (int *) &OutP->infoType != * (int *) &infoCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine processor_set_basic_info */
mig_external kern_return_t machid_processor_set_basic_info
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_name_t pset,
	mhost_t *host,
	processor_set_basic_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
		mach_msg_type_t infoType;
		processor_set_basic_info_data_t info;
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

	static const mach_msg_type_t psetType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
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
		/* msgt_number = */		5,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->psetType = threads;

	InP->pset = psetpsetType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829301;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829401) {
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
	    ((msgh_size != 64) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->threads;

#if	TypeCheck
	if (* (int *) &OutP->infoType != * (int *) &infoCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine processor_set_sched_info */
mig_external kern_return_t machid_processor_set_sched_info
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_name_t pset,
	mhost_t *host,
	processor_set_sched_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
		mach_msg_type_t infoType;
		processor_set_sched_info_data_t info;
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

	static const mach_msg_type_t psetType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
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
		/* msgt_number = */		2,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->psetType = threads;

	InP->pset = psetpsetType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829302;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829402) {
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
	    ((msgh_size != 52) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->threads;

#if	TypeCheck
	if (* (int *) &OutP->infoType != * (int *) &infoCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*info = OutP->threads;

	return KERN_SUCCESS;
}

/* Routine task_unix_info */
mig_external kern_return_t machid_task_unix_info
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	unix_pid_t *pid,
	unix_command_t comm,
	mach_msg_type_number_t *commCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t pidType;
		unix_pid_t pid;
		mach_msg_type_t commType;
		char comm[1024];
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t pidCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = threads;

	InP->auth = authauthType;

	InP->taskType = threads;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829303;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829403) {
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
	    ((msgh_size < 44) &&
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
	if (* (int *) &OutP->pidType != * (int *) &pidCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pid = OutP->threads;

#if	TypeCheck
	if ((OutP->commType.msgt_inline != TRUE) ||
	    (OutP->commType.msgt_longform != FALSE) ||
	    (OutP->commType.msgt_name != 8) ||
	    (OutP->commType.msgt_size != 8))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->commType.msgt_number + 3) & ~3))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (OutP->commType.msgt_number > *commCnt) {
		memcpy(comm, OutP->comm, *commCnt);
		*commCnt = OutP->commType.msgt_number;
		return MIG_ARRAY_TOO_LARGE;
	}
	else {
		memcpy(comm, OutP->comm, OutP->commType.msgt_number);
	}

	*commCnt = OutP->*;

	return KERN_SUCCESS;
}

/* Routine task_basic_info */
mig_external kern_return_t machid_task_basic_info
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	task_basic_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		task_basic_info_data_t info;
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

	static const mach_msg_type_t taskType = {
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
		/* msgt_number = */		8,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829304;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829404) {
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
	    ((msgh_size != 68) &&
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

	*info = OutP->*;

	return KERN_SUCCESS;
}

/* Routine task_thread_times_info */
mig_external kern_return_t machid_task_thread_times_info
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	task_thread_times_info_data_t *times
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t timesType;
		task_thread_times_info_data_t times;
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t timesCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		4,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829305;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829405) {
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
	    ((msgh_size != 52) &&
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
	if (* (int *) &OutP->timesType != * (int *) &timesCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*times = OutP->*;

	return KERN_SUCCESS;
}

/* Routine thread_basic_info */
mig_external kern_return_t machid_thread_basic_info
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	thread_basic_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		thread_basic_info_data_t info;
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

	static const mach_msg_type_t threadType = {
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
		/* msgt_number = */		11,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829306;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829406) {
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
	    ((msgh_size != 80) &&
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

	*info = OutP->*;

	return KERN_SUCCESS;
}

/* Routine thread_sched_info */
mig_external kern_return_t machid_thread_sched_info
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	thread_sched_info_data_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		thread_sched_info_data_t info;
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

	static const mach_msg_type_t threadType = {
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
		/* msgt_number = */		7,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829307;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829407) {
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
	    ((msgh_size != 64) &&
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

	*info = OutP->*;

	return KERN_SUCCESS;
}

/* Routine i386_thread_state */
mig_external kern_return_t machid_i386_thread_state
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	i386_thread_state_t *state
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t stateType;
		i386_thread_state_t state;
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

	static const mach_msg_type_t threadType = {
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

	static const mach_msg_type_t stateCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		17,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829311;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829411) {
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
	    ((msgh_size != 104) &&
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
	if (* (int *) &OutP->stateType != * (int *) &stateCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*state = OutP->*;

	return KERN_SUCCESS;
}

/* Routine task_terminate */
mig_external kern_return_t machid_task_terminate
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829312;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829412) {
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

/* Routine task_suspend */
mig_external kern_return_t machid_task_suspend
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829313;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829413) {
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

/* Routine task_resume */
mig_external kern_return_t machid_task_resume
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829314;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829414) {
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

/* Routine thread_terminate */
mig_external kern_return_t machid_thread_terminate
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829315;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829415) {
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

/* Routine thread_suspend */
mig_external kern_return_t machid_thread_suspend
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829316;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829416) {
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

/* Routine thread_resume */
mig_external kern_return_t machid_thread_resume
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829317;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829417) {
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

/* Routine thread_abort */
mig_external kern_return_t machid_thread_abort
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829318;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829418) {
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

/* Routine processor_set_destroy */
mig_external kern_return_t machid_processor_set_destroy
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->psetType = *;

	InP->pset = psetpsetType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829320;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829420) {
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

/* Routine processor_start */
mig_external kern_return_t machid_processor_start
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t processor
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t processorType;
		mprocessor_t processor;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t processorType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->processorType = *;

	InP->processor = processorprocessorType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829321;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829421) {
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

/* Routine processor_exit */
mig_external kern_return_t machid_processor_exit
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t processor
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t processorType;
		mprocessor_t processor;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t processorType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->processorType = *;

	InP->processor = processorprocessorType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829322;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829422) {
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

/* Routine vm_region */
mig_external kern_return_t machid_vm_region
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	vm_offset_t addr,
	vm_region_t *info
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t addrType;
		vm_offset_t addr;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t infoType;
		vm_region_t info;
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t addrType = {
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
		/* msgt_number = */		8,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->addrType = *;

	InP->addr = addraddrType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829323;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829423) {
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
	    ((msgh_size != 68) &&
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

	*info = OutP->*;

	return KERN_SUCCESS;
}

/* Routine vm_read */
mig_external kern_return_t machid_vm_read
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	vm_offset_t addr,
	vm_size_t size,
	vm_offset_t *data,
	mach_msg_type_number_t *dataCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t addrType;
		vm_offset_t addr;
		mach_msg_type_t sizeType;
		vm_size_t size;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t dataType;
		vm_offset_t data;
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t addrType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t sizeType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->addrType = *;

	InP->addr = addraddrType;

	InP->sizeType = *;

	InP->size = sizesizeType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829324;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829424) {
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

	if (((msgh_size != 52) || msgh_simple) &&
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
	if ((OutP->dataType.msgtl_header.msgt_inline != FALSE) ||
	    (OutP->dataType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->dataType.msgtl_name != 9) ||
	    (OutP->dataType.msgtl_size != 8))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*data = OutP->*;

	*dataCnt = OutP->*;

	return KERN_SUCCESS;
}

/* Routine thread_priority */
mig_external kern_return_t machid_thread_priority
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	int priority,
	boolean_t set_max
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
		mach_msg_type_t priorityType;
		int priority;
		mach_msg_type_t set_maxType;
		boolean_t set_max;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t priorityType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t set_maxType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->priorityType = *;

	InP->priority = prioritypriorityType;

	InP->set_maxType = *;

	InP->set_max = set_maxset_maxType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829325;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829425) {
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

/* Routine thread_max_priority */
mig_external kern_return_t machid_thread_max_priority
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	mprocessor_set_t pset,
	int max_pri
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t max_priType;
		int max_pri;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t max_priType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->threadType = *;

	InP->thread = threadthreadType;

	InP->psetType = *;

	InP->pset = psetpsetType;

	InP->max_priType = *;

	InP->max_pri = max_primax_priType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829326;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829426) {
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

/* Routine task_priority */
mig_external kern_return_t machid_task_priority
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	int priority,
	boolean_t change_threads
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t priorityType;
		int priority;
		mach_msg_type_t change_threadsType;
		boolean_t change_threads;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t priorityType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t change_threadsType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->priorityType = *;

	InP->priority = prioritypriorityType;

	InP->change_threadsType = *;

	InP->change_threads = change_threadschange_threadsType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829327;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829427) {
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

/* Routine processor_set_max_priority */
mig_external kern_return_t machid_processor_set_max_priority
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t pset,
	int max_pri,
	boolean_t change_threads
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t max_priType;
		int max_pri;
		mach_msg_type_t change_threadsType;
		boolean_t change_threads;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t max_priType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t change_threadsType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->psetType = *;

	InP->pset = psetpsetType;

	InP->max_priType = *;

	InP->max_pri = max_primax_priType;

	InP->change_threadsType = *;

	InP->change_threads = change_threadschange_threadsType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829328;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829428) {
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

/* Routine port_names */
mig_external kern_return_t machid_port_names
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mach_port_array_t *names,
	mach_msg_type_number_t *namesCnt,
	mach_port_type_array_t *types,
	mach_msg_type_number_t *typesCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t namesCntType;
		mach_msg_type_number_t namesCnt;
		mach_msg_type_t typesCntType;
		mach_msg_type_number_t typesCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t namesType;
		mach_port_t names[512];
		mach_msg_type_long_t typesType;
		mach_port_type_t types[512];
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t namesCntType = {
		/* msgt_name = */		MACH_MSG_TYPE_INTEGER_32,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t typesCntType = {
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

	InP->authType = *;

	InP->auth = authauthType;

	InP->taskType = *;

	InP->task = tasktaskType;

	InP->namesCntType = *;

	if (*namesCnt < 512)
		InP->namesCnt = *namesCnt;
	else
		InP->namesCnt = 512;

	InP->typesCntType = *;

	if (*typesCnt < 512)
		InP->typesCnt = *typesCnt;
	else
		InP->typesCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829329;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829429) {
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

	if (((msgh_size < 56)) &&
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
	if ((OutP->namesType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->namesType.msgtl_name != 15) ||
	    (OutP->namesType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	msgh_size_delta = (OutP->namesType.msgtl_header.msgt_inline) ? 4 * OutP->namesType.msgtl_number : sizeof(mach_port_t *);
#if	TypeCheck
	if (msgh_size < 56 + msgh_size_delta)
		return MIG_TYPE_ERROR;
	msgh_size -= msgh_size_delta;
#endif	/* TypeCheck */

	if (!OutP->namesType.msgtl_header.msgt_inline)
	    *names = *((mach_port_t **)OutP->names);
	else if (OutP->namesType.msgtl_number > *namesCnt) {
	    mig_allocate((vm_offset_t *)names,
		4 * OutP->namesType.msgtl_number);
	    memcpy(*names, OutP->names, 4 * OutP->namesType.msgtl_number);
	}
	else {
	    memcpy(*names, OutP->names, 4 * OutP->namesType.msgtl_number);
	}

	*namesCnt = OutP->names;

	OutP = (Reply *) ((char *) OutP + msgh_size_delta - 2048);

#if	TypeCheck
	if ((OutP->typesType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->typesType.msgtl_name != 2) ||
	    (OutP->typesType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 56 + ((OutP->typesType.msgtl_header.msgt_inline) ? 4 * OutP->typesType.msgtl_number : sizeof(mach_port_type_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->typesType.msgtl_header.msgt_inline)
	    *types = *((mach_port_type_t **)OutP->types);
	else if (OutP->typesType.msgtl_number > *typesCnt) {
	    mig_allocate((vm_offset_t *)types,
		4 * OutP->typesType.msgtl_number);
	    memcpy(*types, OutP->types, 4 * OutP->typesType.msgtl_number);
	}
	else {
	    memcpy(*types, OutP->types, 4 * OutP->typesType.msgtl_number);
	}

	*typesCnt = OutP->types;

	return KERN_SUCCESS;
}

/* Routine port_type */
mig_external kern_return_t machid_port_type
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mach_port_t name,
	mach_port_type_t *ptype
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t nameType;
		mach_port_t name;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t ptypeType;
		mach_port_type_t ptype;
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
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

	static const mach_msg_type_t ptypeCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = types;

	InP->auth = authauthType;

	InP->taskType = types;

	InP->task = tasktaskType;

	InP->nameType = types;

	InP->name = namenameType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829330;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829430) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->ptypeType != * (int *) &ptypeCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*ptype = OutP->types;

	return KERN_SUCCESS;
}

/* Routine port_get_refs */
mig_external kern_return_t machid_port_get_refs
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mach_port_t name,
	mach_port_right_t right,
	mach_port_urefs_t *refs
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t nameType;
		mach_port_t name;
		mach_msg_type_t rightType;
		mach_port_right_t right;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t refsType;
		mach_port_urefs_t refs;
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t rightType = {
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

	static const mach_msg_type_t refsCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = types;

	InP->auth = authauthType;

	InP->taskType = types;

	InP->task = tasktaskType;

	InP->nameType = types;

	InP->name = namenameType;

	InP->rightType = types;

	InP->right = rightrightType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829331;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829431) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->refsType != * (int *) &refsCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*refs = OutP->types;

	return KERN_SUCCESS;
}

/* Routine port_get_receive_status */
mig_external kern_return_t machid_port_get_receive_status
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mach_port_t name,
	mach_port_status_t *status
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t nameType;
		mach_port_t name;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t statusType;
		mach_port_status_t status;
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
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

	static const mach_msg_type_t statusCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		9,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = types;

	InP->auth = authauthType;

	InP->taskType = types;

	InP->task = tasktaskType;

	InP->nameType = types;

	InP->name = namenameType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829332;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829432) {
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
	    ((msgh_size != 72) &&
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
	if (* (int *) &OutP->statusType != * (int *) &statusCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*status = OutP->types;

	return KERN_SUCCESS;
}

/* Routine port_get_set_status */
mig_external kern_return_t machid_port_get_set_status
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mach_port_t name,
	mach_port_array_t *members,
	mach_msg_type_number_t *membersCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t nameType;
		mach_port_t name;
		mach_msg_type_t membersCntType;
		mach_msg_type_number_t membersCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t membersType;
		mach_port_t members[512];
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

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t nameType = {
		/* msgt_name = */		15,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t membersCntType = {
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

	InP->authType = types;

	InP->auth = authauthType;

	InP->taskType = types;

	InP->task = tasktaskType;

	InP->nameType = types;

	InP->name = namenameType;

	InP->membersCntType = types;

	if (*membersCnt < 512)
		InP->membersCnt = *membersCnt;
	else
		InP->membersCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829333;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829433) {
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
	if ((OutP->membersType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->membersType.msgtl_name != 15) ||
	    (OutP->membersType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->membersType.msgtl_header.msgt_inline) ? 4 * OutP->membersType.msgtl_number : sizeof(mach_port_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->membersType.msgtl_header.msgt_inline)
	    *members = *((mach_port_t **)OutP->members);
	else if (OutP->membersType.msgtl_number > *membersCnt) {
	    mig_allocate((vm_offset_t *)members,
		4 * OutP->membersType.msgtl_number);
	    memcpy(*members, OutP->members, 4 * OutP->membersType.msgtl_number);
	}
	else {
	    memcpy(*members, OutP->members, 4 * OutP->membersType.msgtl_number);
	}

	*membersCnt = OutP->members;

	return KERN_SUCCESS;
}

/* Routine processor_get_assignment */
mig_external kern_return_t machid_processor_get_assignment
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t proc,
	mprocessor_set_name_t *pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t procType;
		mprocessor_t proc;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
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

	static const mach_msg_type_t procType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = members;

	InP->auth = authauthType;

	InP->procType = members;

	InP->proc = procprocType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829334;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829434) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->members;

	return KERN_SUCCESS;
}

/* Routine thread_get_assignment */
mig_external kern_return_t machid_thread_get_assignment
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	mprocessor_set_name_t *pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
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

	static const mach_msg_type_t threadType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = members;

	InP->auth = authauthType;

	InP->threadType = members;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829335;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829435) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->members;

	return KERN_SUCCESS;
}

/* Routine task_get_assignment */
mig_external kern_return_t machid_task_get_assignment
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mprocessor_set_name_t *pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_name_t pset;
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = members;

	InP->auth = authauthType;

	InP->taskType = members;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829336;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829436) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->members;

	return KERN_SUCCESS;
}

/* Routine host_processor_set_priv */
mig_external kern_return_t machid_host_processor_set_priv
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mprocessor_set_name_t psetn,
	mprocessor_set_t *pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
		mach_msg_type_t psetnType;
		mprocessor_set_name_t psetn;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetnType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = members;

	InP->auth = authauthType;

	InP->hostType = members;

	InP->host = hosthostType;

	InP->psetnType = members;

	InP->psetn = psetnpsetnType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829337;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829437) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->members;

	return KERN_SUCCESS;
}

/* Routine host_processor_set_names */
mig_external kern_return_t machid_host_processor_set_names
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	mprocessor_set_name_array_t *sets,
	mach_msg_type_number_t *setsCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
		mach_msg_type_t setsCntType;
		mach_msg_type_number_t setsCnt;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_long_t setsType;
		mprocessor_set_name_t sets[512];
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

	static const mach_msg_type_t hostType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t setsCntType = {
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

	InP->authType = members;

	InP->auth = authauthType;

	InP->hostType = members;

	InP->host = hosthostType;

	InP->setsCntType = members;

	if (*setsCnt < 512)
		InP->setsCnt = *setsCnt;
	else
		InP->setsCnt = 512;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829338;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829438) {
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
	if ((OutP->setsType.msgtl_header.msgt_longform != TRUE) ||
	    (OutP->setsType.msgtl_name != 2) ||
	    (OutP->setsType.msgtl_size != 32))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

#if	TypeCheck
	if (msgh_size != 44 + ((OutP->setsType.msgtl_header.msgt_inline) ? 4 * OutP->setsType.msgtl_number : sizeof(mprocessor_set_name_t *)))
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	if (!OutP->setsType.msgtl_header.msgt_inline)
	    *sets = *((mprocessor_set_name_t **)OutP->sets);
	else if (OutP->setsType.msgtl_number > *setsCnt) {
	    mig_allocate((vm_offset_t *)sets,
		4 * OutP->setsType.msgtl_number);
	    memcpy(*sets, OutP->sets, 4 * OutP->setsType.msgtl_number);
	}
	else {
	    memcpy(*sets, OutP->sets, 4 * OutP->setsType.msgtl_number);
	}

	*setsCnt = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine processor_set_create */
mig_external kern_return_t machid_processor_set_create
(
	mach_port_t server,
	mach_port_t auth,
	mhost_t host,
	mprocessor_set_t *pset,
	mprocessor_set_name_t *psetn
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t psetnType;
		mprocessor_set_name_t psetn;
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

	static const mach_msg_type_t hostType = {
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

	static const mach_msg_type_t psetCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetnCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->hostType = sets;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829339;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829439) {
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
	if (* (int *) &OutP->psetType != * (int *) &psetCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*pset = OutP->sets;

#if	TypeCheck
	if (* (int *) &OutP->psetnType != * (int *) &psetnCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*psetn = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine task_create */
mig_external kern_return_t machid_task_create
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t parent,
	boolean_t inherit,
	mtask_t *task
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t parentType;
		mtask_t parent;
		mach_msg_type_t inheritType;
		boolean_t inherit;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t taskType;
		mtask_t task;
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

	static const mach_msg_type_t parentType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t inheritType = {
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

	static const mach_msg_type_t taskCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->parentType = sets;

	InP->parent = parentparentType;

	InP->inheritType = sets;

	InP->inherit = inheritinheritType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829340;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829440) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->taskType != * (int *) &taskCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*task = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine thread_create */
mig_external kern_return_t machid_thread_create
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mthread_t *thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t threadCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829341;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829441) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->threadType != * (int *) &threadCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*thread = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine processor_assign */
mig_external kern_return_t machid_processor_assign
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t processor,
	mprocessor_set_t pset,
	boolean_t wait
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t processorType;
		mprocessor_t processor;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t waitType;
		boolean_t wait;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t processorType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t waitType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->processorType = sets;

	InP->processor = processorprocessorType;

	InP->psetType = sets;

	InP->pset = psetpsetType;

	InP->waitType = sets;

	InP->wait = waitwaitType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829342;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829442) {
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

/* Routine thread_assign */
mig_external kern_return_t machid_thread_assign
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	mprocessor_set_t pset
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->threadType = sets;

	InP->thread = threadthreadType;

	InP->psetType = sets;

	InP->pset = psetpsetType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829343;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829443) {
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

/* Routine thread_assign_default */
mig_external kern_return_t machid_thread_assign_default
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->threadType = sets;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829344;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829444) {
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

/* Routine task_assign */
mig_external kern_return_t machid_task_assign
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mprocessor_set_t pset,
	boolean_t assign_threads
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t psetType;
		mprocessor_set_t pset;
		mach_msg_type_t assign_threadsType;
		boolean_t assign_threads;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t psetType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t assign_threadsType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->psetType = sets;

	InP->pset = psetpsetType;

	InP->assign_threadsType = sets;

	InP->assign_threads = assign_threadsassign_threadsType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829345;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829445) {
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

/* Routine task_assign_default */
mig_external kern_return_t machid_task_assign_default
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	boolean_t assign_threads
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t assign_threadsType;
		boolean_t assign_threads;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t assign_threadsType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->assign_threadsType = sets;

	InP->assign_threads = assign_threadsassign_threadsType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829346;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829446) {
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

/* Routine thread_policy */
mig_external kern_return_t machid_thread_policy
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	int policy,
	int data
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
		mach_msg_type_t policyType;
		int policy;
		mach_msg_type_t dataType;
		int data;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t threadType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t policyType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t dataType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->threadType = sets;

	InP->thread = threadthreadType;

	InP->policyType = sets;

	InP->policy = policypolicyType;

	InP->dataType = sets;

	InP->data = datadataType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829347;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829447) {
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

/* Routine processor_set_policy_enable */
mig_external kern_return_t machid_processor_set_policy_enable
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t processor_set,
	int policy
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t processor_setType;
		mprocessor_set_t processor_set;
		mach_msg_type_t policyType;
		int policy;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t processor_setType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t policyType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->processor_setType = sets;

	InP->processor_set = processor_setprocessor_setType;

	InP->policyType = sets;

	InP->policy = policypolicyType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829348;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 48, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829448) {
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

/* Routine processor_set_policy_disable */
mig_external kern_return_t machid_processor_set_policy_disable
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_set_t processor_set,
	int policy,
	boolean_t change_threads
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t processor_setType;
		mprocessor_set_t processor_set;
		mach_msg_type_t policyType;
		int policy;
		mach_msg_type_t change_threadsType;
		boolean_t change_threads;
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

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t processor_setType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t policyType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t change_threadsType = {
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->processor_setType = sets;

	InP->processor_set = processor_setprocessor_setType;

	InP->policyType = sets;

	InP->policy = policypolicyType;

	InP->change_threadsType = sets;

	InP->change_threads = change_threadschange_threadsType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829349;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 56, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829449) {
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

/* Routine host_default_pager */
mig_external kern_return_t machid_host_default_pager
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mdefault_pager_t *default_pager
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t default_pagerType;
		mdefault_pager_t default_pager;
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

	static const mach_msg_type_t hostType = {
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

	static const mach_msg_type_t default_pagerCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->hostType = sets;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829350;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829450) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->default_pagerType != * (int *) &default_pagerCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*default_pager = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine vm_statistics */
mig_external kern_return_t machid_vm_statistics
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	vm_statistics_data_t *data
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t dataType;
		vm_statistics_data_t data;
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t dataCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		13,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829352;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829452) {
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
	    ((msgh_size != 88) &&
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
	if (* (int *) &OutP->dataType != * (int *) &dataCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*data = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine host_kernel_task */
mig_external kern_return_t machid_host_kernel_task
(
	mach_port_t server,
	mach_port_t auth,
	mhost_priv_t host,
	mtask_t *kernel_task
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t hostType;
		mhost_priv_t host;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t kernel_taskType;
		mtask_t kernel_task;
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

	static const mach_msg_type_t hostType = {
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

	static const mach_msg_type_t kernel_taskCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->hostType = sets;

	InP->host = hosthostType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829353;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829453) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->kernel_taskType != * (int *) &kernel_taskCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*kernel_task = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine task_host */
mig_external kern_return_t machid_task_host
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	mhost_t *host
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
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

	static const mach_msg_type_t taskType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829354;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829454) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine thread_host */
mig_external kern_return_t machid_thread_host
(
	mach_port_t server,
	mach_port_t auth,
	mthread_t thread,
	mhost_t *host
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t threadType;
		mthread_t thread;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
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

	static const mach_msg_type_t threadType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->threadType = sets;

	InP->thread = threadthreadType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829355;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829455) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine processor_host */
mig_external kern_return_t machid_processor_host
(
	mach_port_t server,
	mach_port_t auth,
	mprocessor_t proc,
	mhost_t *host
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t procType;
		mprocessor_t proc;
	} Request;

	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t RetCodeType;
		kern_return_t RetCode;
		mach_msg_type_t hostType;
		mhost_t host;
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

	static const mach_msg_type_t procType = {
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

	static const mach_msg_type_t hostCheck = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	InP->authType = sets;

	InP->auth = authauthType;

	InP->procType = sets;

	InP->proc = procprocType;

	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829356;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, 40, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829456) {
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
	    ((msgh_size != 40) &&
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
	if (* (int *) &OutP->hostType != * (int *) &hostCheck)
		return MIG_TYPE_ERROR;
#endif	/* TypeCheck */

	*host = OutP->sets;

	return KERN_SUCCESS;
}

/* Routine task_set_unix_info */
mig_external kern_return_t machid_task_set_unix_info
(
	mach_port_t server,
	mach_port_t auth,
	mtask_t task,
	unix_pid_t pid,
	unix_command_t comm,
	mach_msg_type_number_t commCnt
)
{
	typedef struct {
		mach_msg_header_t Head;
		mach_msg_type_t authType;
		mach_port_t auth;
		mach_msg_type_t taskType;
		mtask_t task;
		mach_msg_type_t pidType;
		unix_pid_t pid;
		mach_msg_type_t commType;
		char comm[1024];
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
	unsigned int msgh_size;

	static const mach_msg_type_t authType = {
		/* msgt_name = */		19,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t taskType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t pidType = {
		/* msgt_name = */		2,
		/* msgt_size = */		32,
		/* msgt_number = */		1,
		/* msgt_inline = */		TRUE,
		/* msgt_longform = */		FALSE,
		/* msgt_deallocate = */		FALSE,
		/* msgt_unused = */		0
	};

	static const mach_msg_type_t commType = {
		/* msgt_name = */		8,
		/* msgt_size = */		8,
		/* msgt_number = */		1024,
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

	InP->authType = sets;

	InP->auth = authauthType;

	InP->taskType = sets;

	InP->task = tasktaskType;

	InP->pidType = sets;

	InP->pid = pidpidType;

	InP->commType = sets;

	if (commCnt > 1024) {
		return MIG_ARRAY_TOO_LARGE;
	}
	else {
		memcpy(InP->comm, comm, commCnt);
	}

	InP->commType.msgt_number = commCnt\xe9a\xfa\xff\xffL\x8bC(H\x83\xec\xffs M\x89\xe9H\x8dq8;

	msgh_size = 52 + ((commCnt + 3) & ~3);
	InP->Head.msgh_bits = MACH_MSGH_BITS_COMPLEX|
		MACH_MSGH_BITS(19, MACH_MSG_TYPE_MAKE_SEND_ONCE);
	/* msgh_size passed as argument */
	InP->Head.msgh_request_port = server;
	InP->Head.msgh_reply_port = mig_get_reply_port();
	InP->Head.msgh_seqno = 0;
	InP->Head.msgh_id = 9829360;

	msg_result = mach_msg(&InP->Head, MACH_SEND_MSG|MACH_RCV_MSG|MACH_MSG_OPTION_NONE, msgh_size, sizeof(Reply), InP->Head.msgh_reply_port, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
	if (msg_result != MACH_MSG_SUCCESS) {
		mig_dealloc_reply_port(InP->Head.msgh_reply_port);
		return msg_result;
	}
	mig_put_reply_port(InP->Head.msgh_reply_port);

	if (OutP->Head.msgh_id != 9829460) {
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
