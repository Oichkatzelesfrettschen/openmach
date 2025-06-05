/* GENERATED SERVER STUB for mach_debug.defs by mig_bypass_advanced.py */
#include "mach_debug_user.h"
/* #include <mach/mach.h> */
/* #include <stdio.h> // for printf */

/* Generic server dispatch function */
boolean_t mach_debug_server(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{
    typedef struct {
        mach_msg_header_t Head;
        /* NDR_record_t NDR; */
        kern_return_t RetCode;
    } ServerReplyMsg;
    ServerReplyMsg *ReplyP = (ServerReplyMsg *)OutHeadP;

    /* Minimal reply */
    ReplyP->Head.msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REMOTE(InHeadP->msgh_bits), MACH_MSG_TYPE_MOVE_SEND_ONCE);
    ReplyP->Head.msgh_size = sizeof(ServerReplyMsg);
    ReplyP->Head.msgh_remote_port = InHeadP->msgh_remote_port;
    ReplyP->Head.msgh_local_port = MACH_PORT_NULL;
    ReplyP->Head.msgh_id = InHeadP->msgh_id + 100; /* MIG reply ID convention */
    ReplyP->RetCode = KERN_SUCCESS; /* Assume success for all stubbed routines */

    /* printf("DEBUG STUB: mach_debug_server handling msg_id %d, returning KERN_SUCCESS\n", InHeadP->msgh_id); */

    return TRUE; /* Indicates message was handled and reply is ready */
}
