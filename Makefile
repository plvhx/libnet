CC        := gcc
SONAME    := libnet.so.2
CFLAGS_O  := -fPIC -g -c -Wall -Werror
CFLAGS_SO := -shared -Wl,-soname,$(SONAME)
INCDIR    := ./include
SRCDIR    := ./lib

SO_OBJS := \
	$(SRCDIR)/readline.o \
	$(SRCDIR)/readn.o \
	$(SRCDIR)/sock_ntop.o \
	$(SRCDIR)/writen.o

all: libnet

clean:
	rm -f *.o *.so.2

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

$(SRCDIR)/sock_ntop.o: $(SRCDIR)/sock_ntop.c
	$(CC) $(CFLAGS_O) $< -o $@

$(SRCDIR)/writen.o: $(SRCDIR)/writen.c
	$(CC) $(CFLAGS_O) $< -o $@
