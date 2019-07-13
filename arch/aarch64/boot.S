.section ".text.boot"

.globl _start

	.org 0x80000
// entry point for the kernel.
_start:
	// read cpu id, stop slave cores
	mrs	x1, mpidr_el1
	and	x1, x1, #3
	cbz	x1, 2f
	
	// cpu > 0 => stop
1:	wfe
	b	1b
	
	// cpu = 0
2:	// set the stack before our code
	ldr	x1, =_start
	mov	sp, x1
	
	// clear bss
	ldr	x1, =__bss_start
	ldr	w2, =__bss_size
3:	cbz	w2, 4f
	str	xzr, [x1], #8
	sub	w2, w2, #1
	cbnz	w2, 3b
	
	// branch to C code, should not return
4:	bl	kinit

	// for failsafe, halt this core too
	b	1b
