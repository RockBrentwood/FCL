APPS=iteress

ifneq (, $(findstring Windows, $(OS)))
WINDOWS=1
X=.exe
PLATFORM=windows
else
X=
PLATFORM=$(shell uname -s | tr '[:upper:]' '[:lower:]')
endif

CC=gcc
CFLAGS=-Wall -pedantic -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

FOPT=-O3 -fomit-frame-pointer

FI686=-march=native
FX86_64=-march=native
FSPARC=-mcpu=native
ARCH=$(shell uname -m)
ifeq (, $(ARCH))
ARCH=i686
endif
ifeq ($(ARCH), i686)
FARCH=$(FI686)
endif
ifeq ($(ARCH), x86_64)
FARCH=$(FX86_64)
endif
ifeq ($(ARCH), sparc64)
FARCH=$(FSPARC)
endif

.PHONY: all debug static clean

all: $(APPS)

debug: $(addsuffix -debug,$(APPS))

static: $(addsuffix -static,$(APPS))

iteress: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -o $@$X $^
	strip $@$X

iteress-debug: %-debug: %.c
	$(CC) $(CFLAGS) $(FARCH) -g -o $@$X $^

iteress-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^
	strip $@-$(PLATFORM)-$(ARCH)$X

clean:
	rm -f $(APPS)$X
	rm -f $(APPS)-debug$X
	rm -f $(APPS)-static*$X
