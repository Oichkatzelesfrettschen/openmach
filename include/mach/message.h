/* 
 * Mach Operating System
 * Copyright (c) 1992-1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 *	File:	mach/message.h
 *
 *	Mach IPC message and primitive function definitions.
 */
/**
 * @file mach/message.h
 * @brief Core definitions for Mach Inter-Process Communication (IPC) messages.
 *
 * This file defines the fundamental structures, types, constants, and options
 * used for constructing, sending, receiving, and interpreting Mach messages.
 * It includes the definition of the message header (`mach_msg_header_t`),
 * message type descriptors (`mach_msg_type_t`, `mach_msg_type_long_t`),
 * message timeout types, message option flags, and various return codes
 * specific to message operations.
 */

#ifndef	_MACH_MESSAGE_H_
#define _MACH_MESSAGE_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT definition */
#endif	/* MACH_KERNEL */

#include <mach/kern_return.h> /* For kern_return_t */
#include <mach/port.h>        /* For mach_port_t, mach_port_seqno_t */


/**
 * @name Message Timeouts
 * @{
 */

/**
 * @typedef mach_msg_timeout_t
 * @brief Type for message timeout values.
 *
 * Timeout values are specified in milliseconds. They are used with the
 * `MACH_SEND_TIMEOUT` and `MACH_RCV_TIMEOUT` options in `mach_msg`.
 */
typedef natural_t mach_msg_timeout_t;

/**
 * @def MACH_MSG_TIMEOUT_NONE
 * @brief A special value indicating no timeout.
 *
 * When this value is used, and no `MACH_SEND_TIMEOUT` or `MACH_RCV_TIMEOUT`
 * option is specified, the `mach_msg` call will block indefinitely until
 * the operation can be completed or an error occurs.
 */
#define MACH_MSG_TIMEOUT_NONE		((mach_msg_timeout_t) 0)
/** @} */

/**
 * @name Message Header Bits (`msgh_bits`)
 *
 * The `msgh_bits` field in `mach_msg_header_t` provides information about
 * the message's contents and the types of port rights being transferred.
 *
 * - **`MACH_MSGH_BITS_COMPLEX`**: A hint to the kernel. If not set, the kernel
 *   assumes the message body does not contain port rights or out-of-line (OOL) data.
 *   This bit is set by the kernel in received messages if they contain complex types.
 *   User tasks should be cautious if this bit is not set but type descriptors
 *   indicate complex data, as behavior is undefined.
 *
 * - **Remote and Local Port Bits**: The lower 16 bits of `msgh_bits` encode the
 *   disposition of the `msgh_remote_port` and `msgh_local_port`. These are
 *   `MACH_MSG_TYPE_*` values indicating how port rights are transferred (e.g.,
 *   move send, copy send, make send-once).
 *   - `MACH_MSGH_BITS_REMOTE_MASK` (lower 8 bits) for `msgh_remote_port`.
 *   - `MACH_MSGH_BITS_LOCAL_MASK` (next 8 bits) for `msgh_local_port`.
 *
 * - **Internal Kernel Bits**: `MACH_MSGH_BITS_CIRCULAR`, `MACH_MSGH_BITS_COMPLEX_PORTS`,
 *   `MACH_MSGH_BITS_COMPLEX_DATA`, `MACH_MSGH_BITS_MIGRATED` are for internal kernel use
 *   and should be zero in messages sent by user tasks.
 *
 * - **Unused Bits**: `MACH_MSGH_BITS_UNUSED` should be zero.
 * @{
 */
typedef unsigned int mach_msg_bits_t; ///< Type for `msgh_bits`.

#define MACH_MSGH_BITS_ZERO		0x00000000	/**< Represents zeroed msgh_bits. */
#define MACH_MSGH_BITS_REMOTE_MASK	0x000000ff	/**< Mask for the remote port's disposition bits. */
#define MACH_MSGH_BITS_LOCAL_MASK	0x0000ff00	/**< Mask for the local port's disposition bits. */
#define MACH_MSGH_BITS_COMPLEX		0x80000000U	/**< Indicates message may contain port rights or OOL data in the body. */
#define	MACH_MSGH_BITS_CIRCULAR		0x40000000	/**< Internal kernel use only (related to circular message dependencies). */
#define	MACH_MSGH_BITS_COMPLEX_PORTS	0x20000000	/**< Internal kernel use only (indicates ports in body). */
#define	MACH_MSGH_BITS_COMPLEX_DATA	0x10000000	/**< Internal kernel use only (indicates OOL data in body). */
#define	MACH_MSGH_BITS_MIGRATED		0x08000000	/**< Internal kernel use only (related to task migration). */
#define	MACH_MSGH_BITS_UNUSED		0x07ff0000	/**< Mask for unused bits in `msgh_bits`; should be zero. */

/**< Combined mask for both remote and local port disposition bits. */
#define	MACH_MSGH_BITS_PORTS_MASK				\
		(MACH_MSGH_BITS_REMOTE_MASK|MACH_MSGH_BITS_LOCAL_MASK)

/**
 * @brief Combines remote and local port dispositions into a `mach_msg_bits_t` value.
 * @param remote The `MACH_MSG_TYPE_*` value for `msgh_remote_port`.
 * @param local The `MACH_MSG_TYPE_*` value for `msgh_local_port`.
 * @return The combined `mach_msg_bits_t` value.
 */
#define MACH_MSGH_BITS(remote, local)				\
		((unsigned int)(remote) | ((unsigned int)(local) << 8))
/**
 * @brief Extracts the remote port disposition from `msgh_bits`.
 * @param bits The `msgh_bits` value.
 * @return The `MACH_MSG_TYPE_*` value for the remote port.
 */
#define	MACH_MSGH_BITS_REMOTE(bits)				\
		((bits) & MACH_MSGH_BITS_REMOTE_MASK)
/**
 * @brief Extracts the local port disposition from `msgh_bits`.
 * @param bits The `msgh_bits` value.
 * @return The `MACH_MSG_TYPE_*` value for the local port.
 */
#define	MACH_MSGH_BITS_LOCAL(bits)				\
		(((bits) & MACH_MSGH_BITS_LOCAL_MASK) >> 8)
/**
 * @brief Extracts the combined port disposition bits (remote and local) from `msgh_bits`.
 * @param bits The `msgh_bits` value.
 * @return The combined port disposition bits.
 */
#define	MACH_MSGH_BITS_PORTS(bits)				\
		((bits) & MACH_MSGH_BITS_PORTS_MASK)
/**
 * @brief Extracts all bits from `msgh_bits` other than the port disposition bits.
 * This typically includes `MACH_MSGH_BITS_COMPLEX` and internal/unused bits.
 * @param bits The `msgh_bits` value.
 * @return The non-port-disposition bits.
 */
#define	MACH_MSGH_BITS_OTHER(bits)				\
		((bits) &~ MACH_MSGH_BITS_PORTS_MASK)
/** @} */

/**
 * @name Mach Message Header Structure
 * @{
 */

/** @typedef mach_msg_size_t
 *  @brief Type for message sizes, in bytes. */
typedef	unsigned int mach_msg_size_t;
/** @typedef mach_msg_seqno_t
 *  @brief Type for message sequence numbers. Replaces `msgh_kind`. */
typedef natural_t mach_msg_seqno_t; /* Actually uses mach_port_seqno_t for msgh_seqno */
/** @typedef mach_msg_id_t
 *  @brief Type for the user-defined message identifier. */
typedef integer_t mach_msg_id_t;

/**
 * @struct mach_msg_header_t
 * @brief The standard header for every Mach message.
 *
 * The message header contains essential information for message delivery and
 * interpretation, including destination and reply ports, message size,
 * and a user-defined identifier.
 */
typedef	struct {
    mach_msg_bits_t	msgh_bits;	/**< Encodes disposition of local/remote ports and message complexity. See @ref MACH_MSGH_BITS. */
    mach_msg_size_t	msgh_size;	/**< Total size of the message in bytes, including this header and all inline data. */
    mach_port_t		msgh_remote_port; /**< Destination port (must be a send or send-once right). */
    mach_port_t		msgh_local_port;  /**< Reply port (often a send-once right). Can be `MACH_PORT_NULL` or `MACH_PORT_DEAD`. */
    mach_port_seqno_t	msgh_seqno;	/**< Sequence number from the source port (for received messages, ignored for sent messages). */
    mach_msg_id_t	msgh_id;	/**< User-defined message identifier, uninterpreted by the kernel. Often specifies the operation or RPC method. */
} mach_msg_header_t;
/** @} */

/**
 * @def MACH_MSG_SIZE_MAX
 * @brief Theoretical maximum size of a Mach message.
 * In practice, limited by available memory and kernel-imposed limits.
 */
#define	MACH_MSG_SIZE_MAX	((mach_msg_size_t) ~0)

/**
 * @name Legacy Message Header Definitions
 * @{
 */
#define MACH_MSGH_KIND_NORMAL		0x00000000 /**< @deprecated Legacy: Normal message kind. */
#if	0
/* code using this is likely to break, so better not to have it defined */
#define MACH_MSGH_KIND_NOTIFICATION	0x00000001 /**< @deprecated Legacy: Notification message kind. */
#endif
/** @brief @deprecated `msgh_kind` is replaced by `msgh_seqno`. This macro provides backward compatibility. */
#define	msgh_kind			msgh_seqno
/** @brief @deprecated `mach_msg_kind_t` is replaced by `mach_port_seqno_t`. */
#define mach_msg_kind_t			mach_port_seqno_t
/** @} */

/**
 * @name Mach Message Type Descriptors
 *
 * Following the `mach_msg_header_t` in a message, there can be zero or more
 * pairs of type descriptors and data values. These descriptors tell the kernel
 * and the receiving application how to interpret the subsequent data, especially
 * regarding port rights and out-of-line memory.
 *
 * - **`msgt_number`**: Number of data elements described by this descriptor.
 * - **`msgt_size`**: Size of each data element in bits.
 * - **`msgt_name`**: Type of each data element (e.g., integer, port right). See `MACH_MSG_TYPE_*` constants.
 * - **`msgt_inline`**: If TRUE, the data follows the descriptor inline in the message.
 *   If FALSE, a pointer to the out-of-line data follows the descriptor.
 * - **`msgt_deallocate`**: If TRUE and data is out-of-line, the kernel will deallocate
 *   the out-of-line data region after the message is sent (effectively moving the data).
 *   For inline port rights, this should be FALSE.
 * - **`msgt_longform`**: If TRUE, this `mach_msg_type_t` is actually the header of
 *   a `mach_msg_type_long_t`, which provides larger fields for name, size, and number.
 * - **Padding**: Inline data is padded to ensure subsequent descriptors are word-aligned.
 * - **Port Rights**: For port rights, `msgt_size` must be `8 * sizeof(mach_port_t)`.
 * - **Unused Bit**: `msgt_unused` should be zero.
 * - **Longform Zeroes**: In `mach_msg_type_long_t`, the `msgtl_header`'s `msgt_name`,
 *   `msgt_size`, and `msgt_number` fields should be zero, as the actual values are in
 *   the `msgtl_name`, `msgtl_size`, and `msgtl_number` fields of the long descriptor.
 * @{
 */
typedef unsigned int mach_msg_type_name_t;	/**< Type for `msgt_name` and `msgtl_name`, identifying the data type. */
typedef unsigned int mach_msg_type_size_t;	/**< Type for `msgt_size` and `msgtl_size`, size of each element in bits. */
typedef natural_t  mach_msg_type_number_t;/**< Type for `msgt_number` and `msgtl_number`, count of elements. */

/**
 * @struct mach_msg_type_t
 * @brief Standard descriptor for typed data within a Mach message body.
 *
 * This structure uses bitfields to pack information about the data type,
 * size, count, and handling (inline/OOL, deallocate).
 */
typedef struct  {
    unsigned int	msgt_name : 8;		/**< Type of data (e.g., `MACH_MSG_TYPE_INTEGER_32`, `MACH_MSG_TYPE_PORT_SEND`). */
    unsigned int	msgt_size : 8;		/**< Size of each data element, in bits. */
    unsigned int	msgt_number : 12;	/**< Number of data elements. */
    unsigned int	msgt_inline : 1;	/**< If TRUE, data is inline; FALSE for out-of-line. */
    unsigned int	msgt_longform : 1;	/**< If TRUE, this is a `mach_msg_type_long_t`. */
    unsigned int	msgt_deallocate : 1;	/**< If TRUE, deallocate OOL memory or port right after send. */
    unsigned int	msgt_unused : 1;	/**< Unused, should be zero. */
} mach_msg_type_t;

/**
 * @struct mach_msg_type_long_t
 * @brief Long-form descriptor for typed data, allowing larger counts/sizes if needed.
 *
 * Used when the `msgt_longform` bit is set in the initial `mach_msg_type_t`.
 * The `msgtl_header`'s size, number, and name fields should be zero.
 */
typedef	struct	{
    mach_msg_type_t	msgtl_header;		/**< Standard type descriptor header (`msgt_longform` must be TRUE). Its name, size, number fields should be 0. */
    unsigned short	msgtl_name;		/**< Actual type name if too large for `msgt_name`. */
    unsigned short	msgtl_size;		/**< Actual size in bits if too large for `msgt_size`. */
    natural_t		msgtl_number;		/**< Actual number of items if too large for `msgt_number`. */
} mach_msg_type_long_t;
/** @} */


/** @name Mach Message Data Type Names (`msgt_name` / `msgtl_name`)
 *
 * These constants define the type of data elements described by
 * `mach_msg_type_t` or `mach_msg_type_long_t`. The kernel primarily
 * understands port types and basic integer/unstructured types for RPC.
 * @{
 */
#define MACH_MSG_TYPE_UNSTRUCTURED	0	/**< Raw, uninterpreted bytes. Often used for byte arrays or complex C structs. */
#define MACH_MSG_TYPE_BIT		0	/**< Single bit (equivalent to BOOLEAN or UNSTRUCTURED for size purposes). */
#define MACH_MSG_TYPE_BOOLEAN		0	/**< Boolean value (typically transmitted as a standard integer size like 32-bit). */
#define MACH_MSG_TYPE_INTEGER_16	1	/**< 16-bit integer. */
#define MACH_MSG_TYPE_INTEGER_32	2	/**< 32-bit integer. */
#define MACH_MSG_TYPE_CHAR		8	/**< Character (typically 8-bit). */
#define MACH_MSG_TYPE_BYTE		9	/**< Byte (8-bit integer). */
#define MACH_MSG_TYPE_INTEGER_8		9	/**< 8-bit integer. */
#define MACH_MSG_TYPE_REAL		10	/**< Floating-point number (specific size depends on `msgt_size`). */
#define MACH_MSG_TYPE_INTEGER_64	11	/**< 64-bit integer. */
#define MACH_MSG_TYPE_STRING		12	/**< Generic string of bytes (often used with `msgt_number` as length). */
#define MACH_MSG_TYPE_STRING_C		12	/**< C-style null-terminated string. */

/** @name Port Right Type Names (for sending)
 * These specify the type of port right being sent and how its reference counts are affected.
 * @{
 */
#define MACH_MSG_TYPE_MOVE_RECEIVE	16	/**< Move a receive right. The sender loses the receive right. */
#define MACH_MSG_TYPE_MOVE_SEND		17	/**< Move a send right. The sender loses one send right. */
#define MACH_MSG_TYPE_MOVE_SEND_ONCE	18	/**< Move a send-once right. The sender loses the send-once right. */
#define MACH_MSG_TYPE_COPY_SEND		19	/**< Copy a send right. The sender retains the send right, receiver gets a new one. */
#define MACH_MSG_TYPE_MAKE_SEND		20	/**< Make a new send right from a receive right. Sender must hold receive rights. */
#define MACH_MSG_TYPE_MAKE_SEND_ONCE	21	/**< Make a new send-once right from a receive right. Sender must hold receive rights. */
/** @} */

/** @name Port Right Type Names (for receiving/carrying in messages)
 * These indicate the type of port right the receiver obtains.
 * @{
 */
#define MACH_MSG_TYPE_PORT_NAME		15	/**< Transfer a port name (integer value) only, without transferring any rights. Kernel does not interpret this as a port right. */
#define MACH_MSG_TYPE_PORT_RECEIVE	MACH_MSG_TYPE_MOVE_RECEIVE /**< Received a receive right. */
#define MACH_MSG_TYPE_PORT_SEND		MACH_MSG_TYPE_MOVE_SEND    /**< Received a send right. */
#define MACH_MSG_TYPE_PORT_SEND_ONCE	MACH_MSG_TYPE_MOVE_SEND_ONCE /**< Received a send-once right. */
/** @} */

#define MACH_MSG_TYPE_LAST		22		/**< Marks the last assigned standard message type name. For extensibility. */
/** @} */

/**
 * @def MACH_MSG_TYPE_POLYMORPHIC
 * @brief A special type name indicating that the actual type will be determined dynamically or is otherwise variable.
 * Often used in MIG-generated stubs where the type might be resolved at runtime.
 */
#define MACH_MSG_TYPE_POLYMORPHIC	((mach_msg_type_name_t) -1)

/** @name Port Type Predicate Macros
 * @{
 */
/**
 * @brief Checks if a message type name represents any kind of port right being transferred
 * (move receive, move send, move send-once, copy send, make send, make send-once).
 * @param x The `mach_msg_type_name_t` value.
 * @return True if `x` is any port right transfer type, false otherwise.
 */
#define MACH_MSG_TYPE_PORT_ANY(x)			\
	(((x) >= MACH_MSG_TYPE_MOVE_RECEIVE) &&		\
	 ((x) <= MACH_MSG_TYPE_MAKE_SEND_ONCE))

/**
 * @brief Checks if a message type name represents any kind of send or send-once right being transferred
 * (move send, move send-once, copy send, make send, make send-once).
 * @param x The `mach_msg_type_name_t` value.
 * @return True if `x` is any send or send-once port right transfer type, false otherwise.
 */
#define	MACH_MSG_TYPE_PORT_ANY_SEND(x)			\
	(((x) >= MACH_MSG_TYPE_MOVE_SEND) &&		\
	 ((x) <= MACH_MSG_TYPE_MAKE_SEND_ONCE))

/**
 * @brief Checks if a message type name represents a port right that is moved
 * (move receive, move send, move send-once).
 * @param x The `mach_msg_type_name_t` value.
 * @return True if `x` is a "move" type for a port right, false otherwise.
 */
#define	MACH_MSG_TYPE_PORT_ANY_RIGHT(x)			\
	(((x) >= MACH_MSG_TYPE_MOVE_RECEIVE) &&		\
	 ((x) <= MACH_MSG_TYPE_MOVE_SEND_ONCE))
/** @} */

/**
 * @typedef mach_msg_option_t
 * @brief Type for options passed to `mach_msg`.
 * Options control various aspects of message send and receive operations.
 */
typedef integer_t mach_msg_option_t;

/** @name Mach Message Options
 * These flags can be combined (OR'ed) and passed as the `option`
 * parameter to the `mach_msg` function.
 * @{
 */
#define MACH_MSG_OPTION_NONE	0x00000000	/**< No options specified. */

#define	MACH_SEND_MSG		0x00000001	/**< Perform a send operation. */
#define	MACH_RCV_MSG		0x00000002	/**< Perform a receive operation. `mach_msg` can perform both send and receive (RPC). */

#define MACH_SEND_TIMEOUT	0x00000010	/**< Apply timeout to send operation. If message cannot be queued before timeout, `MACH_SEND_TIMED_OUT` is returned. */
#define MACH_SEND_NOTIFY	0x00000020	/**< Request a msg-accepted notification (deprecated; use `MACH_SEND_WILL_NOTIFY` error code). */
#define MACH_SEND_INTERRUPT	0x00000040	/**< Allow send operation to be interrupted by signals (typically handled by libmach). */
#define MACH_SEND_CANCEL	0x00000080	/**< Used internally by kernel for message forwarding. */
#define MACH_RCV_TIMEOUT	0x00000100	/**< Apply timeout to receive operation. If no message arrives before timeout, `MACH_RCV_TIMED_OUT` is returned. */
#define MACH_RCV_NOTIFY		0x00000200	/**< Request a notification if receive is cancelled (related to `mach_port_request_notification`). */
#define MACH_RCV_INTERRUPT	0x00000400	/**< Allow receive operation to be interrupted by signals (typically handled by libmach). */
#define MACH_RCV_LARGE		0x00000800	/**< Allow receiving large messages that might not fit in the initial buffer (kernel may use a larger internal buffer). */

#define MACH_SEND_ALWAYS	0x00010000	/**< Internal kernel use only. Force message to be sent even under some error conditions. */
/** @} */


/**
 * @name Mach Message Return Codes
 *
 * `mach_msg_return_t` is typedef'd to `kern_return_t`. These codes indicate
 * the status of `mach_msg` operations.
 *
 * See `<mach/error.h>` for the general format of error codes.
 * Mach IPC errors belong to system `0x4`.
 * - Send errors: subsystem `0`.
 * - Receive errors: subsystem `1`.
 * The `code` field (lower bits) is always non-zero for errors.
 * Some error codes use higher bits within the code field (masked by `MACH_MSG_MASK`)
 * to convey additional information (e.g., resource shortages).
 * @{
 */
typedef kern_return_t mach_msg_return_t;

#define MACH_MSG_SUCCESS		0x00000000	/**< Message operation successful. */

/**
 * @def MACH_MSG_MASK
 * @brief Masks special informational bits within the code part of an IPC error.
 * These bits provide more details about resource shortages.
 */
#define	MACH_MSG_MASK			0x00003c00
#define	MACH_MSG_IPC_SPACE		0x00002000	/**< Indicates no room in IPC name space for a new capability. */
#define	MACH_MSG_VM_SPACE		0x00001000	/**< Indicates no room in VM address space for out-of-line memory. */
#define	MACH_MSG_IPC_KERNEL		0x00000800	/**< Indicates kernel resource shortage related to an IPC capability. */
#define	MACH_MSG_VM_KERNEL		0x00000400	/**< Indicates kernel resource shortage related to out-of-line memory. */

/** @name Send Errors (System 0x4, Subsystem 0) */
/**@{*/
#define MACH_SEND_IN_PROGRESS		0x10000001	/**< Internal use: Thread is waiting to send. */
#define MACH_SEND_INVALID_DATA		0x10000002	/**< Invalid inline data in the message. */
#define MACH_SEND_INVALID_DEST		0x10000003	/**< `msgh_remote_port` was not a valid send or send-once right. */
#define MACH_SEND_TIMED_OUT		0x10000004	/**< Message not sent before timeout expired (if `MACH_SEND_TIMEOUT` was used). */
#define MACH_SEND_WILL_NOTIFY		0x10000005	/**< Message was accepted. A msg-accepted notification (if requested via `mach_port_request_notification`) will be generated from the destination. */
#define MACH_SEND_NOTIFY_IN_PROGRESS	0x10000006	/**< A msg-accepted notification is already pending for this port. */
#define MACH_SEND_INTERRUPTED		0x10000007	/**< Send operation interrupted (e.g., by a signal, if `MACH_SEND_INTERRUPT` was used). */
#define MACH_SEND_MSG_TOO_SMALL		0x10000008	/**< `msgh_size` is too small for the specified message components. */
#define MACH_SEND_INVALID_REPLY		0x10000009	/**< `msgh_local_port` was invalid for the specified `msgh_bits` disposition. */
#define MACH_SEND_INVALID_RIGHT		0x1000000a	/**< Invalid port right encountered in the message body during complex type processing. */
#define MACH_SEND_INVALID_NOTIFY	0x1000000b	/**< The notify port argument to `mach_msg` was invalid. */
#define MACH_SEND_INVALID_MEMORY	0x1000000c	/**< Invalid out-of-line memory pointer or descriptor. */
#define MACH_SEND_NO_BUFFER		0x1000000d	/**< Kernel could not allocate a message buffer (temporary resource shortage). */
#define MACH_SEND_NO_NOTIFY		0x1000000e	/**< Kernel resource shortage prevented queuing a msg-accepted notification request. */
#define MACH_SEND_INVALID_TYPE		0x1000000f	/**< An invalid `mach_msg_type_t` descriptor was encountered in the message body. */
#define MACH_SEND_INVALID_HEADER	0x10000010	/**< A field in `mach_msg_header_t` had an invalid value (e.g., inconsistent `msgh_bits`). */
/**@}*/

/** @name Receive Errors (System 0x4, Subsystem 1) */
/**@{*/
#define MACH_RCV_IN_PROGRESS		0x10004001	/**< Internal use: Thread is waiting for receive. */
#define MACH_RCV_INVALID_NAME		0x10004002	/**< `rcv_name` argument to `mach_msg` was not a valid receive right or port set. */
#define MACH_RCV_TIMED_OUT		0x10004003	/**< No message arrived before timeout expired (if `MACH_RCV_TIMEOUT` was used). */
#define MACH_RCV_TOO_LARGE		0x10004004	/**< Received message's inline data is larger than `rcv_size` specified. */
#define MACH_RCV_INTERRUPTED		0x10004005	/**< Receive operation interrupted (e.g., by a signal, if `MACH_RCV_INTERRUPT` was used). */
#define MACH_RCV_PORT_CHANGED		0x10004006	/**< Port was added to or removed from a port set during receive from the set. */
#define MACH_RCV_INVALID_NOTIFY		0x10004007	/**< The notify port argument to `mach_msg` was invalid (for receive notifications). */
#define MACH_RCV_INVALID_DATA		0x10004008	/**< The receive buffer (`msg` argument to `mach_msg`) was invalid. */
#define MACH_RCV_PORT_DIED		0x10004009	/**< The port or port set being received from was destroyed or deallocated. */
#define	MACH_RCV_IN_SET			0x1000400a	/**< When receiving on a port, indicates the port is a member of a set (obsolete or informational). */
#define	MACH_RCV_HEADER_ERROR		0x1000400b	/**< Error receiving message header. Special bits in `MACH_MSG_MASK` may provide more info. */
#define	MACH_RCV_BODY_ERROR		0x1000400c	/**< Error receiving message body (e.g., for OOL data). Special bits in `MACH_MSG_MASK` may provide more info. */
/**@}*/
/** @} */


/**
 * @brief Raw Mach message system trap.
 *
 * This is the direct system call interface for sending and/or receiving Mach messages.
 * The `mach_msg()` function is typically a wrapper around this trap.
 *
 * @param msg Pointer to the `mach_msg_header_t` to be sent and/or buffer to receive into.
 * @param option A bitwise OR of `MACH_SEND_*` and `MACH_RCV_*` options.
 * @param send_size Size of the message to send (if `MACH_SEND_MSG` is in `option`).
 * @param rcv_size Size of the buffer allocated for receiving a message (if `MACH_RCV_MSG` is in `option`).
 * @param rcv_name Port or port set to receive from (if `MACH_RCV_MSG` is in `option`).
 * @param timeout Timeout value in milliseconds, used if `MACH_SEND_TIMEOUT` or `MACH_RCV_TIMEOUT` is in `option`.
 * @param notify Port for notifications (e.g., msg-accepted, dead-name), usage depends on options.
 * @return A `mach_msg_return_t` code indicating success or failure.
 */
extern mach_msg_return_t
mach_msg_trap
#if	defined(c_plusplus) || defined(__STDC__)
   (mach_msg_header_t *msg,
    mach_msg_option_t option,
    mach_msg_size_t send_size,
    mach_msg_size_t rcv_size,
    mach_port_t rcv_name,
    mach_msg_timeout_t timeout,
    mach_port_t notify);
#else	/* c_plusplus || __STDC__ */
#ifdef	LINTLIBRARY
   (msg, option, send_size, rcv_size, rcv_name, timeout, notify)
    mach_msg_header_t *msg;
    mach_msg_option_t option;
    mach_msg_size_t send_size;
    mach_msg_size_t rcv_size; /* Corrected: semicolon was missing */
    mach_port_t rcv_name;
    mach_msg_timeout_t timeout;
    mach_port_t notify;
{ return MACH_MSG_SUCCESS; } /* Corrected: MACH_RCV_SUCCESS to MACH_MSG_SUCCESS for generic case */
#else	/* LINTLIBRARY */
   ();
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/**
 * @brief Primary Mach message interface function.
 *
 * This function is used for sending and/or receiving Mach messages. It typically
 * wraps the `mach_msg_trap`.
 *
 * @param msg Pointer to the `mach_msg_header_t` to be sent and/or buffer to receive into.
 *            On receive, `msg->msgh_size` will be updated to the actual received size.
 * @param option A bitwise OR of `MACH_SEND_*` and `MACH_RCV_*` options.
 * @param send_size Size of the message to send (if `MACH_SEND_MSG` is in `option`).
 * @param rcv_size Size of the buffer allocated for receiving a message (if `MACH_RCV_MSG` is in `option`).
 * @param rcv_name Port or port set to receive from (if `MACH_RCV_MSG` is in `option`).
 * @param timeout Timeout value in milliseconds, used if `MACH_SEND_TIMEOUT` or `MACH_RCV_TIMEOUT` is in `option`.
 * @param notify Port for notifications, usage depends on options.
 * @return A `mach_msg_return_t` code indicating success or failure.
 */
extern mach_msg_return_t
mach_msg
#if	defined(c_plusplus) || defined(__STDC__)
   (mach_msg_header_t *msg,
    mach_msg_option_t option,
    mach_msg_size_t send_size,
    mach_msg_size_t rcv_size,
    mach_port_t rcv_name,
    mach_msg_timeout_t timeout,
    mach_port_t notify);
#else	/* c_plusplus || __STDC__ */
#ifdef	LINTLIBRARY
   (msg, option, send_size, rcv_size, rcv_name, timeout, notify)
    mach_msg_header_t *msg;
    mach_msg_option_t option;
    mach_msg_size_t send_size;
    mach_msg_size_t rcv_size; /* Corrected: semicolon was missing */
    mach_port_t rcv_name;
    mach_msg_timeout_t timeout;
    mach_port_t notify;
{ return MACH_MSG_SUCCESS; } /* Corrected: MACH_RCV_SUCCESS to MACH_MSG_SUCCESS for generic case */
#else	/* LINTLIBRARY */
   ();
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @name Legacy Mach IPC Interface (MACH_IPC_COMPAT)
 *  The following definitions are part of an older Mach IPC interface,
 *  primarily for compatibility with Accent. These are generally considered
 *  obsolete and should not be used in new code. They are compiled only
 *  if `MACH_IPC_COMPAT` is defined.
 * @{
 */
#if	MACH_IPC_COMPAT

/**
 * @typedef msg_size_t
 * @brief Type for message size in the legacy IPC interface.
 * @deprecated Use `mach_msg_size_t`.
 */
typedef	unsigned int	msg_size_t;

/**
 * @struct msg_header_t
 * @brief Message header for the legacy IPC interface.
 * @deprecated Use `mach_msg_header_t`.
 */
typedef	struct {
		unsigned int	msg_unused : 24;	///< Unused bits.
		unsigned int	msg_simple : 8;		///< If TRUE, message contains no complex types (ports/OOL data).
		msg_size_t	msg_size;		///< Total size of the message in bytes.
		integer_t	msg_type;		///< Message type (e.g., normal, emergency). See `MSG_TYPE_*`.
		port_t		msg_local_port;		///< Reply port.
		port_t		msg_remote_port;	///< Destination port.
		integer_t	msg_id;			///< User-defined message identifier.
} msg_header_t;

/**
 * @def MSG_SIZE_MAX
 * @brief Maximum message size in the legacy IPC interface.
 * @deprecated Modern Mach IPC (`mach_msg`) does not have a fixed upper limit like this.
 */
#define MSG_SIZE_MAX	8192

/** @name Legacy Message Types (`msg_header_t.msg_type`)
 *  These are Accent holdovers. Only one bit (`MSG_TYPE_EMERGENCY`) was
 *  meaningful to the kernel.
 * @{
 */
#define MSG_TYPE_NORMAL		0	/**< @deprecated Normal message type. */
#define MSG_TYPE_EMERGENCY	1	/**< @deprecated Emergency message type. Kernel might prioritize these. */
/** @} */

/**
 * @struct msg_type_t
 * @brief Type descriptor for data items in the legacy IPC message body.
 * @deprecated Use `mach_msg_type_t`.
 */
typedef struct  {
	unsigned int	msg_type_name : 8;	/**< @deprecated Kind of data. See legacy `MSG_TYPE_*` constants. */
	unsigned int	msg_type_size : 8;	/**< @deprecated Size of each item in bits. */
	unsigned int	msg_type_number : 12;	/**< @deprecated Number of items. */
	unsigned int	msg_type_inline : 1;	/**< @deprecated If TRUE, data follows; else a pointer. */
	unsigned int	msg_type_longform : 1;	/**< @deprecated If TRUE, `msg_type_long_name`, `_size`, `_number` follow. */
	unsigned int	msg_type_deallocate : 1;/**< @deprecated Deallocate port rights or OOL memory. */
	unsigned int	msg_type_unused : 1;	/**< @deprecated Unused bit. */
} msg_type_t;

/**
 * @struct msg_type_long_t
 * @brief Long-form type descriptor for legacy IPC.
 * @deprecated Use `mach_msg_type_long_t`.
 */
typedef	struct	{
	msg_type_t	msg_type_header;	/**< @deprecated Standard legacy type header. */
	unsigned short	msg_type_long_name;	/**< @deprecated Actual type name. */
	unsigned short	msg_type_long_size;	/**< @deprecated Actual size in bits. */
	natural_t	msg_type_long_number;	/**< @deprecated Actual number of items. */
} msg_type_long_t;

/** @name Legacy Message Data Type Names (`msg_type_name`)
 * @deprecated Use `MACH_MSG_TYPE_*` constants.
 * @{
 */
#define MSG_TYPE_UNSTRUCTURED	0
#define MSG_TYPE_BIT		0
#define MSG_TYPE_BOOLEAN	0
#define MSG_TYPE_INTEGER_16	1
#define MSG_TYPE_INTEGER_32	2
#define MSG_TYPE_PORT_OWNERSHIP	3	/**< Obsolete. */
#define MSG_TYPE_PORT_RECEIVE	4	/**< Obsolete. */
#define MSG_TYPE_PORT_ALL	5	/**< Represents all rights to a port (send and receive). */
#define MSG_TYPE_PORT		6	/**< Represents a send right to a port. */
#define MSG_TYPE_CHAR		8
#define MSG_TYPE_BYTE		9
#define MSG_TYPE_INTEGER_8	9
#define MSG_TYPE_REAL		10
#define MSG_TYPE_STRING		12
#define MSG_TYPE_STRING_C	12
/*	MSG_TYPE_INVALID	13	unused */
#define MSG_TYPE_INTERNAL_MEMORY MSG_TYPE_INTEGER_8 /**< Used internally for memory. */
#define MSG_TYPE_PORT_NAME	15		/**< A capability name (integer value), not a right. */
#define MSG_TYPE_LAST		16		/**< Last assigned legacy type. */
#define MSG_TYPE_POLYMORPHIC	((unsigned int) -1) /**< Type to be determined dynamically. */
/** @} */

/**
 * @def MSG_TYPE_PORT_ANY(x)
 * @brief Checks if a legacy message type name represents any kind of port right.
 * @param x The `msg_type_name` value.
 * @return True if `x` is `MSG_TYPE_PORT` or `MSG_TYPE_PORT_ALL`.
 * @deprecated
 */
#define MSG_TYPE_PORT_ANY(x)	\
	(((x) == MSG_TYPE_PORT) || ((x) == MSG_TYPE_PORT_ALL))

/**
 * @typedef msg_timeout_t
 * @brief Type for timeout values in legacy IPC.
 * @deprecated Use `mach_msg_timeout_t`.
 */
typedef natural_t	msg_timeout_t;

/**
 * @typedef msg_option_t
 * @brief Type for options in legacy IPC calls.
 * @deprecated Use `mach_msg_option_t`.
 */
typedef	integer_t		msg_option_t;

/** @name Legacy IPC Options
 * @deprecated Use `MACH_MSG_OPTION_NONE` and `MACH_SEND_*/RCV_*` options.
 * @{
 */
#define MSG_OPTION_NONE	0x0000	/**< No options. */
#define SEND_TIMEOUT	0x0001	/**< Terminate send on timeout. */
#define SEND_NOTIFY	0x0002	/**< Request reply notification for send. */
#define SEND_INTERRUPT	0x0004	/**< Allow send to be software interrupted. */
#define RCV_TIMEOUT	0x0100	/**< Terminate receive on timeout. */
#define RCV_NO_SENDERS	0x0200	/**< Terminate receive if no senders exist for the port. */
#define RCV_INTERRUPT	0x0400	/**< Allow receive to be software interrupted. */
/** @} */

/**
 * @typedef msg_return_t
 * @brief Return type for legacy IPC functions.
 * @deprecated Use `mach_msg_return_t`.
 */
typedef	int		msg_return_t;

/** @name Legacy IPC Return Codes
 * @deprecated Use `MACH_MSG_SUCCESS` and `MACH_SEND_*/RCV_*` error codes.
 * @{
 */
#define SEND_SUCCESS		0	/**< Send successful. */
#define SEND_ERRORS_START	-100	/**< Start of send error codes. */
#define SEND_INVALID_MEMORY	-101	/**< Message or OOL data invalid. */
#define SEND_INVALID_PORT	-102	/**< Reference to inaccessible port. */
#define SEND_TIMED_OUT		-103	/**< Send terminated due to timeout. */
#define SEND_WILL_NOTIFY	-105	/**< Message accepted provisionally, notification will follow. */
#define SEND_NOTIFY_IN_PROGRESS	-106	/**< Notification already in progress for this port. */
#define SEND_KERNEL_REFUSED	-107	/**< Message to the kernel was refused. */
#define SEND_INTERRUPTED	-108	/**< Send operation interrupted. */
#define SEND_MSG_TOO_LARGE	-109	/**< Message specified was too large for internal buffers. */
#define SEND_MSG_TOO_SMALL	-110	/**< Data specified exceeds `msg_size` in header. */
/*	SEND_MSG_SIZE_CHANGE	-111	   Msg size changed during copy (obsolete) */
#define SEND_ERRORS_END		-111	/**< End of send error codes. */

/** @brief Checks if a return code is a legacy send error. @deprecated */
#define msg_return_send(x)	((x) <= SEND_ERRORS_START && (x) >= SEND_ERRORS_END) /* Corrected logic */

#define RCV_SUCCESS		0	/**< Receive successful. */
#define RCV_ERRORS_START	-200	/**< Start of receive error codes. */
#define RCV_INVALID_MEMORY	-201	/**< Invalid receive buffer. */
#define RCV_INVALID_PORT	-202	/**< Invalid receive port. */
#define RCV_TIMED_OUT		-203	/**< Receive terminated due to timeout. */
#define RCV_TOO_LARGE		-204	/**< Message structure too small for received data. */
#define RCV_NOT_ENOUGH_MEMORY	-205	/**< Cannot find space for OOL data. */
#define RCV_ONLY_SENDER		-206	/**< Receiver is the only sender to the reply port (can't RPC self). */
#define RCV_INTERRUPTED		-207	/**< Receive operation interrupted. */
#define RCV_PORT_CHANGE		-208	/**< Port was moved into a port set during receive. */
#define RCV_ERRORS_END		-209	/**< End of receive error codes. */

/** @brief Checks if a return code is a legacy receive error. @deprecated */
#define msg_return_rcv(x)	((x) <= RCV_ERRORS_START && (x) >= RCV_ERRORS_END) /* Corrected logic */

#define RPC_SUCCESS		0	/**< RPC successful (used by `msg_rpc`). */
/** @} */

/** @name Legacy IPC Primitive Functions
 *  These are the trap-based functions for the old IPC interface.
 * @deprecated Use `mach_msg()` and `mach_msg_trap()`.
 * @{
 */
/** @brief Legacy send message. @deprecated */
msg_return_t	msg_send(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,
	msg_option_t	option,
	msg_timeout_t	timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, timeout)
	msg_header_t	*header;
	msg_option_t	option;
	msg_timeout_t	timeout;
	{ return(SEND_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @brief Legacy receive message. @deprecated */
msg_return_t	msg_receive(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,
	msg_option_t	option,
	msg_timeout_t	timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, timeout)
	msg_header_t	*header;
	msg_option_t	option;
	msg_timeout_t	timeout;
	{ return(RCV_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @brief Legacy RPC (send then receive). @deprecated */
msg_return_t	msg_rpc(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,	/* in/out */
	msg_option_t	option,
	msg_size_t	rcv_size,
	msg_timeout_t	send_timeout,
	msg_timeout_t	rcv_timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, rcv_size,
			send_timeout, rcv_timeout)
	msg_header_t	*header;	/* in/out */
	msg_option_t	option;
	msg_size_t	rcv_size;
	msg_timeout_t	send_timeout;
	msg_timeout_t	rcv_timeout;
	{ return(RPC_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @brief Legacy send message trap. @deprecated */
msg_return_t	msg_send_trap(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,
	msg_option_t	option,
	msg_size_t	send_size,
	msg_timeout_t	timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, send_size, timeout)
	msg_header_t	*header;
	msg_option_t	option;
	msg_size_t	send_size;
	msg_timeout_t	timeout;
	{ return(SEND_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @brief Legacy receive message trap. @deprecated */
msg_return_t	msg_receive_trap(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,
	msg_option_t	option,
	msg_size_t	rcv_size,
	port_name_t	rcv_name,
	msg_timeout_t	timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, rcv_size, rcv_name, timeout)
	msg_header_t	*header;
	msg_option_t	option;
	msg_size_t	rcv_size;
	port_name_t	rcv_name;
	msg_timeout_t	timeout;
	{ return(RCV_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */

/** @brief Legacy RPC trap. @deprecated */
msg_return_t	msg_rpc_trap(
#if	defined(c_plusplus) || defined(__STDC__)
	msg_header_t	*header,	/* in/out */
	msg_option_t	option,
	msg_size_t	send_size,
	msg_size_t	rcv_size,
	msg_timeout_t	send_timeout,
	msg_timeout_t	rcv_timeout);
#else	/* c_plusplus || __STDC__ */
#if	LINTLIBRARY
			header, option, send_size, rcv_size,
			send_timeout, rcv_timeout)
	msg_header_t	*header;	/* in/out */
	msg_option_t	option;
	msg_size_t	send_size;
	msg_size_t	rcv_size;
	msg_timeout_t	send_timeout;
	msg_timeout_t	rcv_timeout;
	{ return(RPC_SUCCESS); }
#else	/* LINTLIBRARY */
		);
#endif	/* LINTLIBRARY */
#endif	/* c_plusplus || __STDC__ */
/** @} */

#endif	/* MACH_IPC_COMPAT */
/** @} */ /* End of Legacy Mach IPC Interface group */

#endif	/* _MACH_MESSAGE_H_ */
