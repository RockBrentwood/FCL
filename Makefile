APPS=fcbo iteress pcbo

ifneq (, $(findstring Windows, $(OS)))
PLATFORM=windows
X=.exe
LIBP=
LIBM=
## RM=del ## Windows uses rm, now?
RM=rm -f
else
PLATFORM=$(shell uname -s | tr '[:upper:]' '[:lower:]')
X=
LIBP=-lpthread
LIBM=-lm
RM=rm -f
endif

CC=gcc
CFLAGS=-Wall -pedantic# -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

FOPT=-O3 -fomit-frame-pointer

ARCH=$(shell uname -m)
ifeq (, $(ARCH))
ARCH=i686
endif
ifeq ($(ARCH), i686)
#FARCH=-m32 -march=i686 -mtune=i686
FARCH=-march=native
endif
ifeq ($(ARCH), x86_64)
#FARCH=-m64
FARCH=-march=native
endif
ifeq ($(ARCH), sparc64)
#FARCH=-m64 -mcpu=niagara -mtune=niagara
FARCH=-mcpu=native
endif

STRIP=strip $@$X
STRIP_STATIC=strip $@-$(PLATFORM)-$(ARCH)$X

.PHONY: all debug static test test-demo test-debug clean clobber

all: fca $(APPS)
##	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $(filter %.c,$^)
##	strip $@$X

debug: $(addsuffix -debug,$(APPS))
##	$(CC) $(CFLAGS) $(FARCH) -g -o $@$X $(filter %.c,$^)

static: $(addsuffix -static,$(APPS))
##	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH) $(filter %.c,$^)
##	strip $@-$(PLATFORM)-$(ARCH)$X

fca: fca.c
	$(CC) $(CFLAGS) $^ -o $@$X $(LIBM)

fcbo: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $^
	$(STRIP)
iteress: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $^
	$(STRIP)
pcbo: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) $(LIBP) -o $@$X $^
	$(STRIP)

fcbo-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) -o $@$X $^

iteress-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) -o $@$X $^

pcbo-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) $(LIBP) -o $@$X $^

fcbo-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^
	$(STRIP_STATIC)

iteress-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^
	$(STRIP_STATIC)

pcbo-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^ $(LIBP)
	$(STRIP_STATIC)

test: $(APPS)
	sh test.sh

test-debug: $(addsuffix -debug,$(APPS))
	sh test.sh -debug

test-demo: fca
	sh demo.sh
clean:
	$(RM) Log
	$(RM) *.ex

clobber: clean
	$(RM) fca$X
	$(RM) $(APPS)$X
	$(RM) $(addsuffix -debug$X,$(APPS))
	$(RM) $(addsuffix -static-$(PLATFORM)-$(ARCH)$X,$(APPS))
