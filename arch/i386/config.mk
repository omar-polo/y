ARCH_OBJ=	${ARCHDIR}/boot.o \
		${ARCHDIR}/multiboot.o \
		${ARCHDIR}/kinit.o \
		${ARCHDIR}/b.o \
		${ARCHDIR}/interrupt.o \
		${ARCHDIR}/dts_utils.o \
		${ARCHDIR}/gdt.o \
		${ARCHDIR}/idt.o \
		${ARCHDIR}/handler.o \
		${ARCHDIR}/rtc.o \
		${ARCHDIR}/term.o \
		${ARCHDIR}/serial.o \
		${ARCHDIR}/debug.o

ARCH_SRC=	${ARCHDIR}/boot.S \
		${ARCHDIR}/multiboot.S \
		${ARCHDIR}/kinit.c \
		${ARCHDIR}/b.S \
		${ARCHDIR}/interrupt.S \
		${ARCHDIR}/dts_utils.S \
		${ARCHDIR}/gdt.c \
		${ARCHDIR}/idt.c \
		${ARCHDIR}/handler.c \
		${ARCHDIR}/rtc.c \
		${ARCHDIR}/term.c \
		${ARCHDIR}/serial.c \
		${ARCHDIR}/debug.c

LDSCRIPT = ${ARCHDIR}/linker.ld
