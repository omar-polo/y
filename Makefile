ARCH	?= i386

include config.mk

.PHONY: all all_ i386 aarch64

all_: all

ifeq "${ARCH}" "aarch64"
include Makefile.aarch64
else
include Makefile.x86
endif

all: ${KIMG}

i386:
	${MAKE} ARCH=i386

aarch64:
	${MAKE} ARCH=aarch64
