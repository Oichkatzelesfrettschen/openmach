/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
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
 *	Author: David B. Golub, Carnegie Mellon University
 *	Date:	3/89
 *
 * 	Status information for network interfaces.
 */

#ifndef	_DEVICE_NET_STATUS_H_
#define	_DEVICE_NET_STATUS_H_

#include <device/device_types.h>
#include <mach/message.h>

/*
 * General interface status
 */
/**
 * @brief Structure defining general network interface status.
 */
struct net_status {
	int	min_packet_size;	///< Minimum packet size, including header.
	int	max_packet_size;	///< Maximum packet size, including header.
	int	header_format;		///< Format of the network header (see HDR_* macros).
	int	header_size;		///< Size of the network header in bytes.
	int	address_size;		///< Size of the network address in bytes.
	int	flags;			///< Interface status flags.
	int	mapped_size;		///< If mappable, virtual memory needed.
};
#define	NET_STATUS_COUNT	(sizeof(struct net_status)/sizeof(int)) ///< Number of integers in net_status structure.
#define	NET_STATUS		(('n'<<16) + 1) ///< IOCTL command to get network status.

/** @name Header Formats (for net_status.header_format)
 * As given by RFC 826/1010 for ARP.
 */
/**@{*/
#define	HDR_ETHERNET		1	///< Ethernet hardware address.
#define	HDR_EXP_ETHERNET	2	///< 3Mhz experimental Ethernet hardware address.
#define	HDR_PRO_NET		4	///< Proteon ProNET Token Ring.
#define	HDR_CHAOS		5	///< Chaosnet.
#define	HDR_802			6	///< IEEE 802 networks.
/**@}*/


/**
 * @brief IOCTL command to get the network hardware address.
 * A network address is an array of bytes. In order to return
 * this in an array of (long) integers, it is returned in net order.
 * Use 'ntohl' on each element of the array to retrieve the original
 * ordering.
 */
#define	NET_ADDRESS		(('n'<<16) + 2)

/**
 * @brief IOCTL command to set/get the destination address for point-to-point links.
 */
#define	NET_DSTADDR		(('n'<<16) + 3)


/** @name Input Packet Filter Definitions */
/**@{*/
#define	NET_MAX_FILTER		128 ///< Maximum number of filter words (was 64, bpf programs are big).
#define	NET_FILTER_STACK_DEPTH	32 ///< Depth of the internal stack for filter operations.

/*
 *  We allow specification of up to NET_MAX_FILTER (short) words of a filter
 *  command list to be applied to incoming packets to determine if
 *  those packets should be given to a particular network input filter.
 *
 *  Each network filter specifies the filter command list via net_add_filter.
 *  Each filter command list specifies a sequences of actions which leave a
 *  boolean value on the top of an internal stack.  Each word of the
 *  command list specifies an action from the set {PUSHLIT, PUSHZERO,
 *  PUSHWORD+N} which respectively push the next word of the filter, zero,
 *  or word N of the incoming packet on the stack, and a binary operator
 *  from the set {EQ, LT, LE, GT, GE, AND, OR, XOR} which operates on the
 *  top two elements of the stack and replaces them with its result.  The
 *  special action NOPUSH and the special operator NOP can be used to only
 *  perform the binary operation or to only push a value on the stack.
 *
 *  If the final value of the filter operation is true, then the packet is
 *  accepted for the filter.
 */

typedef	unsigned short	filter_t; ///< Type for a single filter command word.
typedef filter_t	*filter_array_t; ///< Type for an array of filter commands.

#define CSPF_BYTES(n) ((n) * sizeof (filter_t)) ///< Converts number of filter commands to bytes.

/*  these must sum to 16!  */
#define NETF_NBPA	10			///< Number of bits for argument in a filter command.
#define NETF_NBPO	6			///< Number of bits for operator in a filter command.

#define	NETF_ARG(word)	((word) & 0x3ff) ///< Extracts the argument from a filter command word.
#define	NETF_OP(word)	(((word)>>NETF_NBPA)&0x3f) ///< Extracts the operator from a filter command word.

/** @name Binary Operators for Filter Commands (NETF_OP) */
/**@{*/
#define NETF_NOP	(0<<NETF_NBPA)	///< No operation.
#define NETF_EQ		(1<<NETF_NBPA)	///< Equal.
#define NETF_LT		(2<<NETF_NBPA)	///< Less than.
#define NETF_LE		(3<<NETF_NBPA)	///< Less than or equal.
#define NETF_GT		(4<<NETF_NBPA)	///< Greater than.
#define NETF_GE		(5<<NETF_NBPA)	///< Greater than or equal.
#define NETF_AND	(6<<NETF_NBPA)	///< Logical AND.
#define NETF_OR		(7<<NETF_NBPA)	///< Logical OR.
#define NETF_XOR	(8<<NETF_NBPA)	///< Logical XOR.
#define NETF_COR	(9<<NETF_NBPA)	///< Conditional OR.
#define NETF_CAND	(10<<NETF_NBPA)	///< Conditional AND.
#define NETF_CNOR	(11<<NETF_NBPA)	///< Conditional NOR.
#define NETF_CNAND	(12<<NETF_NBPA)	///< Conditional NAND.
#define NETF_NEQ	(13<<NETF_NBPA)	///< Not equal.
#define	NETF_LSH	(14<<NETF_NBPA)	///< Left shift.
#define	NETF_RSH	(15<<NETF_NBPA)	///< Right shift.
#define	NETF_ADD	(16<<NETF_NBPA)	///< Addition.
#define	NETF_SUB	(17<<NETF_NBPA)	///< Subtraction.
#define NETF_BPF	(((1 << NETF_NBPO) - 1) << NETF_NBPA) ///< Berkeley Packet Filter (BPF) extension.
/**@}*/


/** @name Stack Arguments for Filter Commands (NETF_ARG) */
/**@{*/
#define NETF_NOPUSH	0		///< Don't push anything onto the stack.
#define NETF_PUSHLIT	1		///< Push the next word in the filter command list.
#define NETF_PUSHZERO	2		///< Push zero onto the stack.
#define	NETF_PUSHIND	14		///< Push packet word indexed by the value on top of the stack.
#define	NETF_PUSHHDRIND	15		///< Push header word indexed by the value on top of the stack.
#define NETF_PUSHWORD	16		///< Push packet word N (NETF_PUSHWORD + N).
#define	NETF_PUSHHDR	960		///< Push header word N (NETF_PUSHHDR + N).
#define	NETF_PUSHSTK	992		///< Push stack word N (NETF_PUSHSTK + N).
/**@}*/
/**@}*/ /* End of Input Packet Filter Definitions */

/** @name Filter Priorities */
/**@{*/
#define	NET_HI_PRI	100		///< High priority for network filters.
#define	NET_PRI_MAX	255		///< Maximum priority for network filters.
/**@}*/

/*
 * BPF support.
 */
#include <device/bpf.h>

/** @name Network Receive Message Format */
/**@{*/
/*
 * The header and data are packaged separately, since some hardware
 * supports variable-length headers.  We prefix the packet with
 * a packet_hdr structure so that the real data portion begins
 * on a long-word boundary, and so that packet filters can address
 * the type field and packet size uniformly.
 */
#define	NET_RCV_MAX	4095	///< Maximum size of packet data in a receive message.
#define	NET_HDW_HDR_MAX	64	///< Maximum size of hardware header in a receive message.

#define	NET_RCV_MSG_ID	2999	///< Mach message ID for network receive messages (in device.defs reply range).

/**
 * @brief Header prefixed to each packet in a receive message.
 */
struct packet_header {
	unsigned short	length;	///< Length of the packet data (excluding this header).
	unsigned short	type;	///< Network type (e.g., Ethernet type), in network byte order.
};

/**
 * @brief Structure for a network receive message.
 */
struct net_rcv_msg {
	mach_msg_header_t msg_hdr;		///< Standard Mach message header.
	mach_msg_type_t	header_type;	///< Type descriptor for the hardware header.
	char		header[NET_HDW_HDR_MAX]; ///< Hardware header data.
	mach_msg_type_t	packet_type;	///< Type descriptor for the packet data.
	char		packet[NET_RCV_MAX];	///< Packet data.
};
typedef struct net_rcv_msg 	*net_rcv_msg_t; ///< Pointer to a network receive message.
#define	net_rcv_msg_packet_count packet_type.msgt_number ///< Macro to access the packet data count.
/**@}*/


#endif	_DEVICE_NET_STATUS_H_
