# BSD 3-Clause License
#
# Copyright (c) 2021, Paulus Gandung Prakosa <gandung@lists.infradead.org>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CC        := gcc
SONAME    := libnet.so.2
CFLAGS_O  := -fPIC -g -c -Wall -Werror
CFLAGS_SO := -shared -Wl,-soname,$(SONAME)
INCDIR    := ./include
SRCDIR    := ./lib

SO_OBJS := \
	$(SRCDIR)/readline.o \
	$(SRCDIR)/readn.o \
	$(SRCDIR)/sock_bind_wild.o \
	$(SRCDIR)/sock_cmp_addr.o \
	$(SRCDIR)/sock_cmp_port.o \
	$(SRCDIR)/sock_ntop.o \
	$(SRCDIR)/writen.o

all: libnet

clean:
	rm -f $(SRCDIR)/*.o *.so.2

install:
	ln -sf $(shell pwd)/$(SONAME) ../
	ln -sf $(shell pwd)/$(INCDIR) ../

uninstall:
	rm -f ../libnet.so.2 ../include

libnet: $(SO_OBJS)
	$(CC) $(CFLAGS_SO) -o $(SONAME) $(SO_OBJS)

$(SRCDIR)/readline.o: $(SRCDIR)/readline.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/readn.o: $(SRCDIR)/readn.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/sock_bind_wild.o: $(SRCDIR)/sock_bind_wild.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/sock_cmp_addr.o: $(SRCDIR)/sock_cmp_addr.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/sock_cmp_port.o: $(SRCDIR)/sock_cmp_port.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/sock_ntop.o: $(SRCDIR)/sock_ntop.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/writen.o: $(SRCDIR)/writen.c
	$(CC) $(CFLAGS_O) $< -o $@
