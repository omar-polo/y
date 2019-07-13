CC	 = ${TARGET}-gcc
AS	 = ${TARGET}-as
AR	 = ${TARGET}-ar
LD	 = ${TARGET}-ld
OBJCOPY	 = ${TARGET}-objcopy

CFLAGS	 = -nostdlib -std=c99 -ffreestanding -O2 -Wall -Wextra -I${MAINDIR}/include -I${MAINDIR}
