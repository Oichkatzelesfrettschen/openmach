#
# Copyright (c) 1994 The University of Utah and
# the Center for Software Science (CSS).  All rights reserved.
#
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
#
# THE UNIVERSITY OF UTAH AND CSS ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
# IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSS DISCLAIM ANY LIABILITY OF
# ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
#
# CSS requests users of this software to return to css-dist@cs.utah.edu any
# improvements that they make and grant CSS redistribution rights.
#
#      Author: Bryan Ford, University of Utah CSS


#### Start of configuration section ####

GSRCDIR	= @top_gsrcdir@
MSRCDIR = ../..
OBJDIR	= @top_objdir@

prefix = /usr/local
exec_prefix = ${prefix}

include $(OBJDIR)/Makeconf

##### End of configuration section #####


# Only build libmach if the user asked for it.
ifeq ($(ENABLE_LIBMACH),yes)


SRCDIRS += $(MSRCDIR)/libmach/unixoid $(GSRCDIR)/libmach/unixoid

TARGET	= libmach.a

NO_LIBMACHSA_INC = yes
STDINC = yes

include $(MSRCDIR)/libmach/Makerules

install: $(INSTALL_LIBDIR)/$(TARGET)

else

all:
clean:
install:

endif
