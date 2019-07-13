include config.mk

PWD	!= pwd

MAINDIR	 = ${PWD}
ARCHDIR	 = ${PWD}/arch/${ARCH}
SYSDIR	 = ${PWD}/sys
LIBDIR	 = ${PWD}/lib

QEMU	?= qemu-system-${ARCH}
QFLAGS	 = -m 256 -no-reboot -no-shutdown -d int

# if aarch64 assume it's a raspberry pi3
ifeq "${ARCH}" "aarch64"
QFLAGS	+= -M raspi3
endif

include ${ARCHDIR}/config.mk
include sys/config.mk
include lib/config.mk

.PHONY: build clean run run-iso

run: y
	${QEMU} ${QFLAGS} -kernel ${KIMG}
