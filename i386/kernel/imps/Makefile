#
# Copyright (c) 1994 The University of Utah and
# the Computer Systems Laboratory (CSL).  All rights reserved.
#
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
#
# THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
# IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
# ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
#
# CSL requests users of this software to return to csl-dist@cs.utah.edu any
# improvements that they make and grant CSL redistribution rights.
#
#      Author: Bryan Ford, University of Utah CSL
#


# This makefile creates a microkernel
# that supports Intel MP specification-compliant machines.
#### Start of configuration section ####

GSRCDIR	= @top_gsrcdir@
MSRCDIR = ../..
OBJDIR	= @top_objdir@

prefix = /usr/local
exec_prefix = ${prefix}

include $(OBJDIR)/Makeconf

##### End of configuration section #####


# Only build an MP kernel if the user asked for one.
ifeq ($(ENABLE_MP),yes)


# First define what we're trying to accomplish.
TARGET	= kernel-imps.bmod


# For Intel MP spec support add the imps directory.
SRCDIRS += $(MSRCDIR)/kernel/imps


# Everything else is done in here.
include $(MSRCDIR)/kernel/Makerules


# Be sure and build the asm symbol file before anything else.
# This is sort of a bogus dependency, but it does the job.
i386asm.h: impsasm.h
CLEAN_FILES += impsasm.h


else

all:
clean:
install:

endif
