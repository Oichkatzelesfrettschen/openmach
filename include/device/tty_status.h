/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
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
 *	Date: 	ll/90
 *
 * 	Status information for tty.
 */

/**
 * @brief Structure defining TTY status information.
 */
struct tty_status {
	int	tt_ispeed;		///< Input speed (see B* speed constants).
	int	tt_ospeed;		///< Output speed (see B* speed constants).
	int	tt_breakc;		///< Character to deliver when break detected on line.
	int	tt_flags;		///< Mode flags (see TF_* flags).
};
#define	TTY_STATUS_COUNT	(sizeof(struct tty_status)/sizeof(int)) ///< Number of integers in tty_status structure.
#define	TTY_STATUS		(dev_flavor_t)(('t'<<16) + 1) ///< IOCTL command to get TTY status.

/** @name TTY Speeds */
/**@{*/
#define B0	0	///< Hang up.
#define B50	1	///< 50 baud.
#define B75	2	///< 75 baud.
#define B110	3	///< 110 baud.
#define B134	4	///< 134.5 baud.
#define B150	5	///< 150 baud.
#define B200	6	///< 200 baud.
#define B300	7	///< 300 baud.
#define B600	8	///< 600 baud.
#define B1200	9	///< 1200 baud.
#define	B1800	10	///< 1800 baud.
#define B2400	11	///< 2400 baud.
#define B4800	12	///< 4800 baud.
#define B9600	13	///< 9600 baud.
#define EXTA	14	///< External A speed (traditionally 19200).
#define EXTB	15	///< External B speed (traditionally 38400).
#define B19200	EXTA	///< 19200 baud.
#define B38400  EXTB	///< 38400 baud.

#define	NSPEEDS	16	///< Number of speed settings.
/**@}*/

/** @name TTY Mode Flags (tty_status.tt_flags) */
/**@{*/
#define	TF_TANDEM	0x00000001	///< Send STOP character when input queue is full (XON/XOFF flow control).
#define	TF_ODDP		0x00000002	///< Get/send odd parity.
#define	TF_EVENP	0x00000004	///< Get/send even parity.
#define	TF_ANYP		(TF_ODDP|TF_EVENP) ///< Get any parity/send none.
#define	TF_LITOUT	0x00000008	///< Output all 8 bits; otherwise, characters >= 0x80 are time delays (XXX).
#define	TF_MDMBUF	0x00000010	///< Start/stop output on carrier interrupt; otherwise, dropping carrier hangs up line.
#define	TF_NOHANG	0x00000020	///< No hangup signal on carrier drop.
#define	TF_HUPCLS	0x00000040	///< Hang up (outgoing) on last close.

/** @name Read-Only TTY Flags (information about device) */
/**@{*/
#define	TF_ECHO		0x00000080	///< Device wants user to echo input.
#define	TF_CRMOD	0x00000100	///< Device wants \\r\\n, not \\n.
#define	TF_XTABS	0x00000200	///< Device does not understand tabs.
/**@}*/
/**@}*/

/** @name TTY Modem Control */
/**@{*/
#define	TTY_MODEM_COUNT		(1)	///< Number of integers for modem control (one integer).
#define	TTY_MODEM		(dev_flavor_t)(('t'<<16) + 2) ///< IOCTL command for modem control.

/** @name Modem Control Bits (for TTY_MODEM IOCTL) */
/**@{*/
#define	TM_LE		0x0001		///< Line enable.
#define	TM_DTR		0x0002		///< Data Terminal Ready.
#define	TM_RTS		0x0004		///< Request To Send.
#define	TM_ST		0x0008		///< Secondary Transmit.
#define	TM_SR		0x0010		///< Secondary Receive.
#define	TM_CTS		0x0020		///< Clear To Send.
#define	TM_CAR		0x0040		///< Carrier Detect.
#define	TM_RNG		0x0080		///< Ring Indicator.
#define	TM_DSR		0x0100		///< Data Set Ready.

#define	TM_BRK		0x0200		///< Set line break (internal).
#define	TM_HUP		0x0000		///< Close line (internal, effectively TM_LE=0).
/**@}*/
/**@}*/

/** @name Other TTY Controls */
/**@{*/
#define	TTY_FLUSH_COUNT		(1)	///< Number of integers for flush control (one integer: D_READ|D_WRITE).
#define	TTY_FLUSH		(dev_flavor_t)(('t'<<16) + 3) ///< IOCTL command to flush input or output queues.
#define	TTY_STOP		(dev_flavor_t)(('t'<<16) + 4) ///< IOCTL command to stop output.
#define	TTY_START		(dev_flavor_t)(('t'<<16) + 5) ///< IOCTL command to start output.
#define	TTY_SET_BREAK		(dev_flavor_t)(('t'<<16) + 6) ///< IOCTL command to set break condition.
#define	TTY_CLEAR_BREAK		(dev_flavor_t)(('t'<<16) + 7) ///< IOCTL command to clear break condition.
#define TTY_SET_TRANSLATION	(dev_flavor_t)(('t'<<16) + 8) ///< IOCTL command to set translation table.
/**@}*/
