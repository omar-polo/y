# 0 - Division by zero exception
# 1 - Debug exception
# 2 - Non maskable interrupt
# 3 - Breakpoint exception
# 4 - 'Into detected overflow'
# 5 - Out of bounds exception
# 6 - Invalid opcode exception
# 7 - No coprocessor exception
# 8 - Double fault (pushes an error code)
# 9 - Coprocessor segment overrun
# 10 - Bad TSS (pushes an error code)
# 11 - Segment not present (pushes an error code)
# 12 - Stack fault (pushes an error code)
# 13 - General protection fault (pushes an error code)
# 14 - Page fault (pushes an error code)
# 15 - Unknown interrupt exception
# 16 - Coprocessor fault
# 17 - Alignment check exception
# 18 - Machine check exception
# 19-31 - Reserved

# 8, 10-14

.macro isr_noerrcode num
	.globl	isr\num
	.type	isr\num, @function

	isr\num:
		push	$0
		push	$\num
		jmp		isr_common_stub
.endm

.macro isr_errcode num
	.globl	isr\num
	.type	isr\num, @function

	isr\num:
		push	$\num
		jmp		isr_common_stub
.endm

.macro irq n
	.global	irq\n
	.type	irq\n, @function
	irq\n:
		push	$0
		push	$\n
		jmp		irq_common_stub

.endm

.extern interrupt_handler
.extern irq_handler

/* isr_common_stub - save the processor state, sats up for kernel mode
 * segments, calls the C fault handler and finally restores the stack
 * frame!
 *
 * stack: error code and interrupt number */
.type	isr_common_stub, @function
isr_common_stub:
	pusha
	call	interrupt_handler
	popa

	/* cleans up the pushed error code and ISR number */
	add		$8, %esp

	iret

.type	irq_common_stub, @function
irq_common_stub:
	pusha
	call	irq_handler
	popa
	add		$8, %esp
	iret

/* Define the first 18 interrupt handler.

	rc snippet:
	for (i in `{seq 0 18}) {
		switch ($i) {
		case 8 10 11 12 13 14
			echo 'isr_errcode	'^$i
		case *
			echo 'isr_noerrcode	'^$i
		}
	}
 */

isr_noerrcode	0
isr_noerrcode	1
isr_noerrcode	2
isr_noerrcode	3
isr_noerrcode	4
isr_noerrcode	5
isr_noerrcode	6
isr_noerrcode	7
isr_errcode		8
isr_noerrcode	9
isr_errcode		10
isr_errcode		11
isr_errcode		12
isr_errcode		13
isr_errcode		14
isr_noerrcode	15
isr_noerrcode	16
isr_noerrcode	17	# TODO: check if this push an error on the stack
isr_noerrcode	18

# 19-31 are reserved by intel

irq				32
irq				33