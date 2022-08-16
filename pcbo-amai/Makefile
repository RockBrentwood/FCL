APPS=pcbo

ifneq (, $(findstring Windows, $(OS)))
WINDOWS=1
X=.exe
PLATFORM=windows
LIBS=
else
X=
PLATFORM=linux
LIBS=-lpthread
endif

CC=gcc
CFLAGS=-Wall -pedantic

FOPT=-O3 -fomit-frame-pointer

FI686=-m32 -march=i686 -mtune=i686
FAMD64=-m64
FSPARC=-m64 -mcpu=niagara -mtune=niagara
ifeq ($(WINDOWS), 1)
ARCH=i686
else
ARCH=$(shell uname -m)
endif
ifeq ($(ARCH), i686)
FARCH=$(FI686)
endif
ifeq ($(ARCH), x86_64)
FARCH=$(FAMD64)
endif
ifeq ($(ARCH), sparc64)
FARCH=$(FSPARC)
endif

.PHONY: all debug static clean

all: $(APPS)

debug: $(addsuffix -debug,$(APPS))

static: $(addsuffix -static,$(APPS))

pcbo: %: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) $(LIBS) -o $@$X $^
	strip $@$X

pcbo-debug: %-debug: %.c
	$(CC) $(CFLAGS) -g $(FARCH) $(LIBS) -o $@$X $^

pcbo-static: %-static: %.c
	$(CC) $(CFLAGS) $(FOPT) $(FARCH) -static -o $@-$(PLATFORM)-$(ARCH)$X $^ $(LIBS)
	strip $@-$(PLATFORM)-$(ARCH)$X

clean:
	rm -f $(APPS)$X
	rm -f $(APPS)-debug$X
	rm -f $(APPS)-static*$X
