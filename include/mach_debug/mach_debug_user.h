/* GENERATED STUB HEADER for mach_debug.defs by mig_bypass_advanced.py */
#ifndef _MACH_DEBUG_USER_H_
#define _MACH_DEBUG_USER_H_

#include <mach/mach_types.h> /* For kern_return_t, mach_port_t etc. */
#include <mach/message.h>    /* For mach_msg_header_t */
#include <mach/kern_return.h>
#include "mach_ipc_debug_user.h" /* From import mach_ipc_debug.h */
#include "mach_vm_debug_user.h" /* From import mach_vm_debug.h */
#include "mach_kdb_user.h" /* From import mach_kdb.h */
#include "std_types_user.h" /* From import mach/std_types.defs */
#include "mach_types_user.h" /* From import mach/mach_types.defs */
#include "mach_debug_types_user.h" /* From import mach_debug/mach_debug_types.defs */

/* Message ID Base for subsystem mach_debug */
#ifndef MACH_DEBUG_MSG_ID_BASE
#define MACH_DEBUG_MSG_ID_BASE 1000
#endif

/* Definitions of routines */

/* Routine host_zone_info (routine) - msg_id 1000 */
/* Original arguments: host		: host_t;
	out	names		: zone_name_array_t,
					CountInOut, Dealloc;
	out	info		: zone_info_array_t,
					CountInOut, Dealloc */
extern kern_return_t host_zone_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_zone_info here */
);
#define MSG_ID_MACH_DEBUG_host_zone_info (1000)

/* Routine mach_port_get_srights (routine) - msg_id 1001 */
/* Original arguments: task		: ipc_space_t;
		name		: mach_port_name_t;
	out	srights		: mach_port_rights_t */
extern kern_return_t mach_port_get_srights(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_port_get_srights here */
);
#define MSG_ID_MACH_DEBUG_mach_port_get_srights (1001)

/* Routine host_ipc_hash_info (routine) - msg_id 1002 */
/* Original arguments: host		: host_t;
	out	info		: hash_info_bucket_array_t,
					CountInOut, Dealloc */
extern kern_return_t host_ipc_hash_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_ipc_hash_info here */
);
#define MSG_ID_MACH_DEBUG_host_ipc_hash_info (1002)

/* Routine host_ipc_marequest_info (routine) - msg_id 1003 */
/* Original arguments: host		: host_t;
	out	max_requests	: unsigned;
	out	info		: hash_info_bucket_array_t,
					CountInOut, Dealloc */
extern kern_return_t host_ipc_marequest_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_ipc_marequest_info here */
);
#define MSG_ID_MACH_DEBUG_host_ipc_marequest_info (1003)

/* Routine mach_port_space_info (routine) - msg_id 1004 */
/* Original arguments: task		: ipc_space_t;
	out	info		: ipc_info_space_t;
	out	table_info	: ipc_info_name_array_t,
					CountInOut, Dealloc;
	out	tree_info	: ipc_info_tree_name_array_t,
					CountInOut, Dealloc */
extern kern_return_t mach_port_space_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_port_space_info here */
);
#define MSG_ID_MACH_DEBUG_mach_port_space_info (1004)

/* Routine mach_port_dnrequest_info (routine) - msg_id 1005 */
/* Original arguments: task		: ipc_space_t;
		name		: mach_port_name_t;
	out	total		: unsigned;	/* total size of table */
	out	used		: unsigned */
extern kern_return_t mach_port_dnrequest_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_port_dnrequest_info here */
);
#define MSG_ID_MACH_DEBUG_mach_port_dnrequest_info (1005)

/* Routine host_stack_usage (routine) - msg_id 1006 */
/* Original arguments: host		: host_t;
	out	reserved	: vm_size_t;
	out	total		: unsigned;
	out	space		: vm_size_t;
	out	resident	: vm_size_t;
	out	maxusage	: vm_size_t;
	out	maxstack	: vm_offset_t */
extern kern_return_t host_stack_usage(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_stack_usage here */
);
#define MSG_ID_MACH_DEBUG_host_stack_usage (1006)

/* Routine processor_set_stack_usage (routine) - msg_id 1007 */
/* Original arguments: pset		: processor_set_name_t;
	out	total		: unsigned;
	out	space		: vm_size_t;
	out	resident	: vm_size_t;
	out	maxusage	: vm_size_t;
	out	maxstack	: vm_offset_t */
extern kern_return_t processor_set_stack_usage(
    mach_port_t target_port
    /* TODO: Add parsed arguments for processor_set_stack_usage here */
);
#define MSG_ID_MACH_DEBUG_processor_set_stack_usage (1007)

/* Routine host_virtual_physical_table_info (routine) - msg_id 1008 */
/* Original arguments: host		: host_t;
	out	info		: hash_info_bucket_array_t,
					CountInOut, Dealloc */
extern kern_return_t host_virtual_physical_table_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_virtual_physical_table_info here */
);
#define MSG_ID_MACH_DEBUG_host_virtual_physical_table_info (1008)

/* Routine host_load_symbol_table (routine) - msg_id 1009 */
/* Original arguments: host		: host_priv_t;
		task		: task_t;
		name		: symtab_name_t;
		symtab		: pointer_t */
extern kern_return_t host_load_symbol_table(
    mach_port_t target_port
    /* TODO: Add parsed arguments for host_load_symbol_table here */
);
#define MSG_ID_MACH_DEBUG_host_load_symbol_table (1009)

/* Routine mach_port_kernel_object (routine) - msg_id 1010 */
/* Original arguments: task		: ipc_space_t;
		name		: mach_port_name_t;
	out	object_type	: unsigned;
	out	object_addr	: vm_offset_t */
extern kern_return_t mach_port_kernel_object(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_port_kernel_object here */
);
#define MSG_ID_MACH_DEBUG_mach_port_kernel_object (1010)

/* Routine mach_vm_region_info (routine) - msg_id 1011 */
/* Original arguments: task		: vm_task_t;
		address		: vm_address_t;
	out	region		: vm_region_info_t;
	/* avoid out-translation of the argument */
	out	object		: memory_object_name_t =
					MACH_MSG_TYPE_MOVE_SEND
					ctype: mach_port_t */
extern kern_return_t mach_vm_region_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_vm_region_info here */
);
#define MSG_ID_MACH_DEBUG_mach_vm_region_info (1011)

/* Routine mach_vm_object_info (routine) - msg_id 1012 */
/* Original arguments: object		: memory_object_name_t;
	out	info		: vm_object_info_t;
	/* avoid out-translation of the argument */
	out	shadow		: memory_object_name_t =
					MACH_MSG_TYPE_MOVE_SEND
					ctype: mach_port_t;
	/* avoid out-translation of the argument */
	out	copy		: memory_object_name_t =
					MACH_MSG_TYPE_MOVE_SEND
					ctype: mach_port_t */
extern kern_return_t mach_vm_object_info(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_vm_object_info here */
);
#define MSG_ID_MACH_DEBUG_mach_vm_object_info (1012)

/* Routine mach_vm_object_pages (routine) - msg_id 1013 */
/* Original arguments: object		: memory_object_name_t;
	out	pages		: vm_page_info_array_t,
					CountInOut, Dealloc */
extern kern_return_t mach_vm_object_pages(
    mach_port_t target_port
    /* TODO: Add parsed arguments for mach_vm_object_pages here */
);
#define MSG_ID_MACH_DEBUG_mach_vm_object_pages (1013)

#endif /* _{self.subsystem.upper()}_USER_H_ */
