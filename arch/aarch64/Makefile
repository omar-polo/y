MAINDIR	= ../..
ARCHDIR	= .

# temporary
TARGET=aarch64-elf

include ../../config.mk
include config.mk

.PHONY: build clean

build: ${ARCH_OBJ}

clean:
	rm -f ${ARCH_OBJ}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

.S.o:
	${AS} $< -o $@

