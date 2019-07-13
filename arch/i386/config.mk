ARCH_OBJ=	${ARCHDIR}/boot.o \
		${ARCHDIR}/multiboot.o \
		${ARCHDIR}/kinit.o \
		${ARCHDIR}/b.o \
		${ARCHDIR}/dts_utils.o \
		${ARCHDIR}/interrupt.o \
		${ARCHDIR}/isr.o \
		${ARCHDIR}/irq.o \
		${ARCHDIR}/dts.o \
		${ARCHDIR}/term.o \
		${ARCHDIR}/serial.o \
		${ARCHDIR}/debug.o

ARCH_SRC=	${ARCHDIR}/boot.S \
		${ARCHDIR}/multiboot.S \
		${ARCHDIR}/kinit.c \
		${ARCHDIR}/b.S \
		${ARCHDIR}/dts_utils.S \
		${ARCHDIR}/interrupt.S \
		${ARCHDIR}/isr.c \
		${ARCHDIR}/irq.o \
		${ARCHDIR}/dts.c \
		${ARCHDIR}/term.c \
		${ARCHDIR}/serial.c \
		${ARCHDIR}/debug.c

LDSCRIPT = ${ARCHDIR}/linker.ld
