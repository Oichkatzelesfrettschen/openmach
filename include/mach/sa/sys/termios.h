/*
 * Copyright (c) 1988, 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	@(#)termios.h	8.3 (Berkeley) 3/28/94
 * termios.h,v 1.3 1994/08/02 07:53:46 davidg Exp
 */

#ifndef _MACH_SA_SYS_TERMIOS_H_
#define _MACH_SA_SYS_TERMIOS_H_

/*
 * Special Control Characters
 *
 * Index into c_cc[] character array.
 *
 *	Name	     Subscript	Enabled by
 */
#define VEOF 0    /* ICANON */
#define VEOL 1    /* ICANON */
#define VERASE 3  /* ICANON */
#define VKILL 5   /* ICANON */
#define VINTR 8   /* ISIG */
#define VQUIT 9   /* ISIG */
#define VSUSP 10  /* ISIG */
#define VSTART 12 /* IXON, IXOFF */
#define VSTOP 13  /* IXON, IXOFF */
#define VMIN 16   /* !ICANON */
#define VTIME 17  /* !ICANON */
#define NCCS 20

#define _POSIX_VDISABLE ((unsigned char)'\377')

/*
 * Input flags - software input processing
 */
#define IGNBRK 0x00000001 /* ignore BREAK condition */
#define BRKINT 0x00000002 /* map BREAK to SIGINTR */
#define IGNPAR 0x00000004 /* ignore (discard) parity errors */
#define PARMRK 0x00000008 /* mark parity and framing errors */
#define INPCK 0x00000010  /* enable checking of parity errors */
#define ISTRIP 0x00000020 /* strip 8th bit off chars */
#define INLCR 0x00000040  /* map NL into CR */
#define IGNCR 0x00000080  /* ignore CR */
#define ICRNL 0x00000100  /* map CR to NL (ala CRMOD) */
#define IXON 0x00000200   /* enable output flow control */
#define IXOFF 0x00000400  /* enable input flow control */
#ifndef _POSIX_SOURCE
#define IXANY 0x00000800   /* any char will restart after stop */
#define IMAXBEL 0x00002000 /* ring bell on input queue full */
#endif                     /*_POSIX_SOURCE */

/*
 * Output flags - software output processing
 */
#define OPOST 0x00000001 /* enable following output processing */

/*
 * Control flags - hardware control of terminal
 */
#ifndef _POSIX_SOURCE
#define CIGNORE 0x00000001 /* ignore control flags */
#endif
#define CSIZE 0x00000300  /* character size mask */
#define CS5 0x00000000    /* 5 bits (pseudo) */
#define CS6 0x00000100    /* 6 bits */
#define CS7 0x00000200    /* 7 bits */
#define CS8 0x00000300    /* 8 bits */
#define CSTOPB 0x00000400 /* send 2 stop bits */
#define CREAD 0x00000800  /* enable receiver */
#define PARENB 0x00001000 /* parity enable */
#define PARODD 0x00002000 /* odd parity, else even */
#define HUPCL 0x00004000  /* hang up on last close */
#define CLOCAL 0x00008000 /* ignore modem status lines */

/*
 * "Local" flags - dumping ground for other state
 *
 * Warning: some flags in this structure begin with
 * the letter "I" and look like they belong in the
 * input flag.
 */

#define ECHOE 0x00000002   /* visually erase chars */
#define ECHOK 0x00000004   /* echo NL after line kill */
#define ECHO 0x00000008    /* enable echoing */
#define ECHONL 0x00000010  /* echo NL even if ECHO is off */
#define ISIG 0x00000080    /* enable signals INTR, QUIT, [D]SUSP */
#define ICANON 0x00000100  /* canonicalize input lines */
#define IEXTEN 0x00000400  /* enable DISCARD and LNEXT */
#define EXTPROC 0x00000800 /* external processing */
#define TOSTOP 0x00400000  /* stop background jobs from output */
#ifndef _POSIX_SOURCE
#define FLUSHO 0x00800000     /* output being flushed (state) */
#define NOKERNINFO 0x02000000 /* no kernel output from VSTATUS */
#define PENDIN 0x20000000     /* XXX retype pending input (state) */
#endif                        /*_POSIX_SOURCE */
#define NOFLSH 0x80000000     /* don't flush after interrupt */

typedef unsigned long tcflag_t;
typedef unsigned char cc_t;
typedef long speed_t;

struct termios {
  tcflag_t c_iflag; /* input flags */
  tcflag_t c_oflag; /* output flags */
  tcflag_t c_cflag; /* control flags */
  tcflag_t c_lflag; /* local flags */
  cc_t c_cc[NCCS];  /* control chars */
  long c_ispeed;    /* input speed */
  long c_ospeed;    /* output speed */
};

/*
 * Commands passed to tcsetattr() for setting the termios structure.
 */
#define TCSANOW 0   /* make change immediate */
#define TCSADRAIN 1 /* drain output, then change */
#define TCSAFLUSH 2 /* drain output, flush input */
#ifndef _POSIX_SOURCE
#define TCSASOFT 0x10 /* flag - don't alter h.w. state */
#endif

/*
 * Standard speeds
 */
#define B0 0
#define B50 50
#define B75 75
#define B110 110
#define B134 134
#define B150 150
#define B200 200
#define B300 300
#define B600 600
#define B1200 1200
#define B1800 1800
#define B2400 2400
#define B4800 4800
#define B9600 9600
#define B19200 19200
#define B38400 38400
#ifndef _POSIX_SOURCE
#define B7200 7200
#define B14400 14400
#define B28800 28800
#define B57600 57600
#define B76800 76800
#define B115200 115200
#define B230400 230400
#define EXTA 19200
#define EXTB 38400
#endif /* !_POSIX_SOURCE */

#define TCIFLUSH 1
#define TCOFLUSH 2
#define TCIOFLUSH 3
#define TCOOFF 1
#define TCOON 2
#define TCIOFF 3
#define TCION 4

#include <mach/sa/sys/cdefs.h>

__BEGIN_DECLS
speed_t cfgetispeed(const struct termios *);
speed_t cfgetospeed(const struct termios *);
int cfsetispeed(struct termios *, speed_t);
int cfsetospeed(struct termios *, speed_t);
int tcgetattr(int, struct termios *);
int tcsetattr(int, int, const struct termios *);
int tcdrain(int);
int tcflow(int, int);
int tcflush(int, int);
int tcsendbreak(int, int);
__END_DECLS

#endif /* !_MACH_SA_SYS_TERMIOS_H_ */
