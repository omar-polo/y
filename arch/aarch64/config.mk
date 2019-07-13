ARCH_OBJ=	${ARCHDIR}/boot.o \
		${ARCHDIR}/delay.o \
		${ARCHDIR}/kinit.o

ARCH_SRC=	${ARCHDIR}/boot.S \
		${ARCHDIR}/delay.S \
		${ARCHDIR}/kinit.c

LDSCRIPT = ${ARCHDIR}/linker.ld
