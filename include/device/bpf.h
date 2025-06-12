/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * Berkeley Packet Filter Definitions from Berkeley
 */

/*-
 * Copyright (c) 1990-1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from the Stanford/CMU enet packet filter,
 * (net/enet.c) distributed as part of 4.3BSD, and code contributed
 * to Berkeley by Steven McCanne and Van Jacobson both of Lawrence 
 * Berkeley Laboratory.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)bpf.h       7.1 (Berkeley) 5/7/91
 *
 */

#ifndef _DEVICE_BPF_H_
#define _DEVICE_BPF_H_

#if 0	/* not used in MK now */
/*
 * Alignment macros.  BPF_WORDALIGN rounds up to the next 
 * even multiple of BPF_ALIGNMENT. 
 */
#define BPF_ALIGNMENT sizeof(int)
#define BPF_WORDALIGN(x) (((x)+(BPF_ALIGNMENT-1))&~(BPF_ALIGNMENT-1))

/*
 * Struct return by BIOCVERSION.  This represents the version number of 
 * the filter language described by the instruction encodings below.
 * bpf understands a program iff kernel_major == filter_major &&
 * kernel_minor >= filter_minor, that is, if the value returned by the
 * running kernel has the same major number and a minor number equal
 * equal to or less than the filter being downloaded.  Otherwise, the
 * results are undefined, meaning an error may be returned or packets
 * may be accepted haphazardly.
 * It has nothing to do with the source code version.
 */
struct bpf_version {
	u_short bv_major;
	u_short bv_minor;
};
/* Current version number. */
#define BPF_MAJOR_VERSION 1
#define BPF_MINOR_VERSION 1

/*
 * Data-link level type codes.
 * Currently, only DLT_EN10MB and DLT_SLIP are supported.
 */
#define DLT_NULL	0	/* no link-layer encapsulation */
#define DLT_EN10MB	1	/* Ethernet (10Mb) */
#define DLT_EN3MB	2	/* Experimental Ethernet (3Mb) */
#define DLT_AX25	3	/* Amateur Radio AX.25 */
#define DLT_PRONET	4	/* Proteon ProNET Token Ring */
#define DLT_CHAOS	5	/* Chaos */
#define DLT_IEEE802	6	/* IEEE 802 Networks */
#define DLT_ARCNET	7	/* ARCNET */
#define DLT_SLIP	8	/* Serial Line IP */
#define DLT_PPP		9	/* Point-to-point Protocol */
#define DLT_FDDI	10	/* FDDI */

#endif /* 0 */

/*
 * The instruction encondings.
 */

/** @name BPF Instruction Classes */
/**@{*/
#define BPF_CLASS(code) ((code) & 0x07) ///< Extracts the class of a BPF instruction.
#define		BPF_LD		0x00	///< Load value into accumulator.
#define		BPF_LDX		0x01	///< Load value into index register.
#define		BPF_ST		0x02	///< Store accumulator into scratch memory.
#define		BPF_STX		0x03	///< Store index register into scratch memory.
#define		BPF_ALU		0x04	///< Arithmetic or logical operation.
#define		BPF_JMP		0x05	///< Jump.
#define		BPF_RET		0x06	///< Return.
#define		BPF_MISC	0x07	///< Miscellaneous.
/**@}*/

/** @name BPF Load/LoadX Fields */
/**@{*/
#define BPF_SIZE(code)	((code) & 0x18) ///< Extracts the size operand of a BPF instruction.
#define		BPF_W		0x00	///< Word (4 bytes).
#define		BPF_H		0x08	///< Half-word (2 bytes).
#define		BPF_B		0x10	///< Byte.
#define BPF_MODE(code)	((code) & 0xe0) ///< Extracts the mode operand of a BPF instruction.
#define		BPF_IMM 	0x00	///< Immediate value.
#define		BPF_ABS		0x20	///< Absolute offset in packet data.
#define		BPF_IND		0x40	///< Indirect offset in packet data.
#define		BPF_MEM		0x60	///< Scratch memory location.
#define		BPF_LEN		0x80	///< Packet length.
#define		BPF_MSH		0xa0	///< Byte offset within IP header of fragment offset.
/**@}*/

/** @name BPF ALU/Jump Fields */
/**@{*/
#define BPF_OP(code)	((code) & 0xf0) ///< Extracts the operation operand of a BPF ALU/Jump instruction.
#define		BPF_ADD		0x00	///< Addition.
#define		BPF_SUB		0x10	///< Subtraction.
#define		BPF_MUL		0x20	///< Multiplication.
#define		BPF_DIV		0x30	///< Division.
#define		BPF_OR		0x40	///< Bitwise OR.
#define		BPF_AND		0x50	///< Bitwise AND.
#define		BPF_LSH		0x60	///< Left shift.
#define		BPF_RSH		0x70	///< Right shift.
#define		BPF_NEG		0x80	///< Negation.
#define		BPF_JA		0x00	///< Jump always.
#define		BPF_JEQ		0x10	///< Jump if equal.
#define		BPF_JGT		0x20	///< Jump if greater than.
#define		BPF_JGE		0x30	///< Jump if greater than or equal.
#define		BPF_JSET	0x40	///< Jump if bit is set.
#define		BPF_CKMATCH_IMM	0x50	///< Check for match with immediate value.
#define BPF_SRC(code)	((code) & 0x08) ///< Extracts the source operand of a BPF ALU/Jump instruction.
#define		BPF_K		0x00	///< Use constant value (k).
#define		BPF_X		0x08	///< Use index register (X).
/**@}*/

/** @name BPF Return Fields */
/**@{*/
#define BPF_RVAL(code)	((code) & 0x38) ///< Extracts the return value type of a BPF return instruction.
#define		BPF_A		0x10	///< Return value in accumulator.
#define		BPF_MATCH_IMM	0x18	///< Return match status with immediate value.
#define		BPF_MATCH_DATA	0x20	///< Return match status with data.
/**@}*/

/** @name BPF Miscellaneous Fields */
/**@{*/
#define BPF_MISCOP(code) ((code) & 0xf8) ///< Extracts the operation of a BPF miscellaneous instruction.
#define		BPF_TAX		0x00	///< Copy accumulator to index register.
#define		BPF_TXA		0x80	///< Copy index register to accumulator.
#define		BPF_KEY		0x10	///< Set key for subsequent match operations.
#define		BPF_REG_DATA	0x18	///< Register data.
#define		BPF_POSTPONE	0x20	///< Postpone decision.
/**@}*/

/**
 * @brief The BPF instruction data structure.
 */
struct bpf_insn {
	unsigned short	code;	///< Instruction code.
	unsigned char 	jt;	///< Jump if true offset.
	unsigned char 	jf;	///< Jump if false offset.
	int	k;		///< Generic operand.
};
typedef struct bpf_insn *bpf_insn_t; ///< Typedef for a pointer to a BPF instruction.

/*
 * largest bpf program size
 */
#define NET_MAX_BPF ((NET_MAX_FILTER*sizeof(filter_t))/sizeof(struct bpf_insn)) ///< Maximum size of a BPF program.

/** @name Macros for BPF Instruction Array Initializers */
/**@{*/
/**
 * @brief Initializes a BPF statement instruction.
 * @param code The instruction code.
 * @param k The generic operand.
 */
#define BPF_STMT(code, k) { (unsigned short)(code), 0, 0, k }

/**
 * @brief Initializes a BPF jump instruction.
 * @param code The instruction code.
 * @param k The generic operand.
 * @param jt The jump if true offset.
 * @param jf The jump if false offset.
 */
#define BPF_JUMP(code, k, jt, jf) { (unsigned short)(code), jt, jf, k }

/**
 * @brief Initializes a BPF return match instruction.
 * @param code The instruction code.
 * @param k The generic operand.
 * @param nkey The number of keys.
 */
#define BPF_RETMATCH(code, k, nkey) { (unsigned short)(code), nkey, 0, k }

/**
 * @brief Macro to set a BPF statement instruction in an array.
 * @param pc Pointer to the current instruction in the array.
 * @param c The instruction code.
 * @param n The generic operand.
 */
#define	BPF_INSN_STMT(pc, c, n)  {\
	(pc)->code = (c);		\
	(pc)->jt = (pc)->jf = 0;	\
	(pc)->k = (n);			\
	(pc)++;				\
}

/**
 * @brief Macro to set a BPF jump instruction in an array.
 * @param pc Pointer to the current instruction in the array.
 * @param c The instruction code.
 * @param n The generic operand.
 * @param jtrue The jump if true offset.
 * @param jfalse The jump if false offset.
 */
#define BPF_INSN_JUMP(pc, c, n, jtrue, jfalse) {\
	(pc)->code = (c);		\
	(pc)->jt = (jtrue);		\
	(pc)->jf = (jfalse);		\
	(pc)->k = (n);			\
	(pc)++;				\
}

/**
 * @brief Macro to set a BPF return match instruction in an array.
 * @param pc Pointer to the current instruction in the array.
 * @param c The instruction code.
 * @param n The generic operand.
 * @param nkey The number of keys.
 */
#define BPF_INSN_RETMATCH(pc, c, n, nkey) {\
	(pc)->code = (c);		\
	(pc)->jt = (nkey);		\
	(pc)->jf = 0;			\
	(pc)->k = (n);			\
	(pc)++;				\
}
/**@}*/

/*
 * Number of scratch memory words (for BPF_LD|BPF_MEM and BPF_ST).
 */
#define BPF_MEMWORDS 16 ///< Number of scratch memory words.

/*
 * Link level header can be accessed by adding BPF_DLBASE to an offset.
 */
#define BPF_DLBASE	(1<<30) ///< Base offset for accessing link-level header.

#define BPF_BYTES(n) ((n) * sizeof (struct bpf_insn)) ///< Converts number of BPF instructions to bytes.
#define BPF_BYTES2LEN(n) ((n) / sizeof (struct bpf_insn)) ///< Converts bytes to number of BPF instructions.

/**
 * @brief Compares two BPF instructions.
 * @param p Pointer to the first instruction.
 * @param q Pointer to the second instruction.
 * @return True if instructions are equal, false otherwise.
 */
#define BPF_INSN_EQ(p,q) ((p)->code == (q)->code && \
			  (p)->jt == (q)->jt &&	\
			  (p)->jf == (q)->jf &&	\
			  (p)->k == (q)->k)

#endif /* _DEVICE_BPF_H_ */
