/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
 *	File:	mach/notify.h
 *
 *	Kernel notification message definitions.
 */
/**
 * @file mach/notify.h
 * @brief Definitions for Mach kernel notification messages.
 *
 * This file defines the structure and types for various asynchronous
 * notification messages sent by the Mach kernel to ports that have
 * registered an interest in certain events. These events often relate
 * to the lifecycle of Mach ports, such as deletion, destruction, or
 * changes in sender counts.
 *
 * An alternative specification of the notification interface (likely the MIG definition)
 * may be found in `mach/notify.defs`.
 */

#ifndef	_MACH_NOTIFY_H_
#define _MACH_NOTIFY_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT */
#endif	/* MACH_KERNEL */

#include <mach/port.h>      /* For mach_port_t and legacy port_t */
#include <mach/message.h>   /* For mach_msg_header_t, mach_msg_type_t, and legacy msg_header_t, msg_type_t */

/*
 *  An alternative specification of the notification interface
 *  may be found in mach/notify.defs.
 */

/** @name Mach Notification Message Identifiers
 * These constants define the `msgh_id` field in the `mach_msg_header_t`
 * of notification messages, indicating the type of event being reported.
 * @{
 */
#define MACH_NOTIFY_FIRST		0100	/**< Base value for Mach notification identifiers. Octal 100 = Decimal 64. */
#define MACH_NOTIFY_PORT_DELETED	(MACH_NOTIFY_FIRST + 001 ) /**< Notification sent when a send or send-once right (named by `not_port`) is deleted from a task's port name space. The port itself may still exist if other rights to it remain. */
#define MACH_NOTIFY_MSG_ACCEPTED	(MACH_NOTIFY_FIRST + 002)  /**< Notification sent to a port when a message sent to it with the `MACH_SEND_NOTIFY` option (now often indicated by `MACH_SEND_WILL_NOTIFY` return from `mach_msg`) has been accepted by the kernel for delivery. `not_port` is the port that was the destination of the original message. */
#define MACH_NOTIFY_PORT_DESTROYED	(MACH_NOTIFY_FIRST + 005)  /**< Notification sent when a receive right (named by `not_port`) is destroyed (deallocated). This means the port itself is gone. */
#define MACH_NOTIFY_NO_SENDERS		(MACH_NOTIFY_FIRST + 006)  /**< Notification sent to a port when its make-send count (number of extant send rights) drops to zero. `not_count` contains the remaining send-once rights count. */
#define MACH_NOTIFY_SEND_ONCE		(MACH_NOTIFY_FIRST + 007)  /**< Notification sent when an extant send-once right for a port is consumed or deallocated. The notification is sent to the port that held the send-once right (if a previous receiver was set). */
#define MACH_NOTIFY_DEAD_NAME		(MACH_NOTIFY_FIRST + 010)  /**< Notification sent when a send or send-once right (named by `not_port`) becomes a dead name because the port it referred to was destroyed. */
#define MACH_NOTIFY_LAST		(MACH_NOTIFY_FIRST + 015)  /**< Marks the end of the currently defined standard Mach notification identifiers. */
/** @} */

/**
 * @struct mach_port_deleted_notification_t
 * @brief Message structure for a `MACH_NOTIFY_PORT_DELETED` notification.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_PORT_DELETED`.
    mach_msg_type_t	not_type;	///< Type descriptor for `not_port`. Typically `MACH_MSG_TYPE_PORT_NAME`.
    mach_port_t		not_port;	///< The name of the send or send-once right that was deleted.
} mach_port_deleted_notification_t;

/**
 * @struct mach_msg_accepted_notification_t
 * @brief Message structure for a `MACH_NOTIFY_MSG_ACCEPTED` notification.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_MSG_ACCEPTED`.
    mach_msg_type_t	not_type;	///< Type descriptor for `not_port`. Typically `MACH_MSG_TYPE_PORT_NAME`.
    mach_port_t		not_port;	///< The port that was the destination of the original message.
} mach_msg_accepted_notification_t;

/**
 * @struct mach_port_destroyed_notification_t
 * @brief Message structure for a `MACH_NOTIFY_PORT_DESTROYED` notification.
 * This notification includes the former receive right itself.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_PORT_DESTROYED`.
    mach_msg_type_t	not_type;	///< Type descriptor for `not_port`. Typically `MACH_MSG_TYPE_PORT_RECEIVE`.
    mach_port_t		not_port;	///< The receive right that was destroyed.
} mach_port_destroyed_notification_t;

/**
 * @struct mach_no_senders_notification_t
 * @brief Message structure for a `MACH_NOTIFY_NO_SENDERS` notification.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_NO_SENDERS`.
    mach_msg_type_t	not_type;	///< Type descriptor for `not_count`. Typically `MACH_MSG_TYPE_INTEGER_32`.
    unsigned int	not_count;	///< The number of remaining send-once rights for the port.
} mach_no_senders_notification_t;

/**
 * @struct mach_send_once_notification_t
 * @brief Message structure for a `MACH_NOTIFY_SEND_ONCE` notification.
 * This notification has no body beyond the header. The port receiving this
 * notification is the one for which a send-once right was registered.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_SEND_ONCE`.
} mach_send_once_notification_t;

/**
 * @struct mach_dead_name_notification_t
 * @brief Message structure for a `MACH_NOTIFY_DEAD_NAME` notification.
 */
typedef struct {
    mach_msg_header_t	not_header;	///< Standard message header. `msgh_id` is `MACH_NOTIFY_DEAD_NAME`.
    mach_msg_type_t	not_type;	///< Type descriptor for `not_port`. Typically `MACH_MSG_TYPE_PORT_NAME`.
    mach_port_t		not_port;	///< The name that has become dead (no longer refers to a live port).
} mach_dead_name_notification_t;


/** @name Legacy Mach IPC Compatibility Notifications
 * @{
 */
#if	MACH_IPC_COMPAT

/** @name Legacy Notification Message Identifiers
 * These constants define the `msg_type` field in the legacy `msg_header_t`
 * of notification messages.
 * @deprecated Use `MACH_NOTIFY_*` constants with `mach_msg_header_t.msgh_id`.
 * @{
 */
#define NOTIFY_FIRST			0100	/**< @deprecated Base value for legacy notification identifiers. */
#define NOTIFY_PORT_DELETED		( NOTIFY_FIRST + 001 ) /**< @deprecated Port deleted notification. */
#define NOTIFY_MSG_ACCEPTED		( NOTIFY_FIRST + 002 ) /**< @deprecated Message accepted notification. */
#define NOTIFY_OWNERSHIP_RIGHTS		( NOTIFY_FIRST + 003 ) /**< @deprecated Obsolete: Related to port ownership. */
#define NOTIFY_RECEIVE_RIGHTS		( NOTIFY_FIRST + 004 ) /**< @deprecated Obsolete: Related to receive rights. */
#define NOTIFY_PORT_DESTROYED		( NOTIFY_FIRST + 005 ) /**< @deprecated Port destroyed notification. */
#define NOTIFY_NO_MORE_SENDERS		( NOTIFY_FIRST + 006 ) /**< @deprecated No more senders notification. */
#define NOTIFY_LAST			( NOTIFY_FIRST + 015 ) /**< @deprecated Marks the end of legacy notification identifiers. */
/** @} */

/**
 * @struct notification_t
 * @brief Generic structure for legacy notification messages.
 * The actual content and interpretation depend on the `notify_header.msg_type`.
 * @deprecated Use specific `mach_*_notification_t` structures.
 */
typedef struct {
	msg_header_t	notify_header;	///< Legacy message header. `msg_type` field holds the notification ID.
	msg_type_t	notify_type;	///< Legacy type descriptor for `notify_port`.
	port_t		notify_port;	///< Port associated with the notification (specific meaning varies).
} notification_t;

#endif	/* MACH_IPC_COMPAT */
/** @} */

#endif	/* _MACH_NOTIFY_H_ */
