# Makefile for nobuffer
#

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
MANDIR = $(PREFIX)/man/man1

TARGET = libnobuffer.so

all: $(TARGET)

$(TARGET) : nobuffer.c
	gcc -Wall -o $@ $< -ldl -nostartfiles -shared -fPIC

man :
	rst2man nobuffer.1.rst nobuffer.1

clean :
	@-rm -rf $(TARGET)

install : $(TARGET)
	mkdir -p $(BINDIR) $(LIBDIR) $(MANDIR)
	install $(TARGET) $(LIBDIR)/$(TARGET)
	sed "s,#DEFAULT_PREFIX#,$(PREFIX)," < nobuffer > $(BINDIR)/nobuffer
	chmod 0755 $(BINDIR)/nobuffer
	install nobuffer.1 $(MANDIR)

uninstall :
	rm -f $(BINDIR)/nobuffer $(LIBDIR)/$(TARGET) $(MANDIR)/nobuffer.1
