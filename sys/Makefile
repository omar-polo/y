MAINDIR	= ..
SYSDIR	= .

include config.mk
include ${MAINDIR}/config.mk

.PHONY: build clean vars

build: ${SYS_OBJ}

clean:
	rm -f ${SYS_OBJ}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

vars:
	@echo MAINDIR: ${MAINDIR}
	@echo SYSDIR: ${SYSDIR}
	@echo CFLAGS: ${CFLAGS}