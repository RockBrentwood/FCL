APPS=fcbo iteress pcbo

ifneq (, $(findstring Windows, $(OS)))
PLATFORM=windows
X=.exe
LIBS=
else
PLATFORM=$(shell uname -s | tr '[:upper:]' '[:lower:]')
X=
LIBS=-lpthread
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

.PHONY: all debug static clean

all: $(APPS)
##	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $(filter %.c,$^)
##	strip $@$X

debug: $(addsuffix -debug,$(APPS))
##	$(CC) $(CFLAGS) $(FARCH) -g -o $@$X $(filter %.c,$^)

static: $(addsuffix -static,$(APPS))
##	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH) $(filter %.c,$^)
##	strip $@-$(PLATFORM)-$(ARCH)$X

fcbo: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $^
	$(STRIP)
iteress: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $^
	$(STRIP)
pcbo: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) $(LIBS) -o $@$X $^
	$(STRIP)

fcbo-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) -o $@$X $^

iteress-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) -o $@$X $^

pcbo-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) $(LIBS) -o $@$X $^

fcbo-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^
	$(STRIP_STATIC)

iteress-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^
	$(STRIP_STATIC)

pcbo-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^ $(LIBS)
	$(STRIP_STATIC)

test: $(APPS)
	sh test.sh

test-debug: $(addsuffix -debug,$(APPS))
	sh test.sh -debug

clean:
	rm -f Log
	rm -f *.ex

clobber: clean
	rm -f $(APPS)$X
	rm -f $(addsuffix -debug$X,$(APPS))
	rm -f $(addsuffix -static-$(PLATFORM)-$(ARCH)$X,$(APPS))
