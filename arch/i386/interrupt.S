/* when some interrupt occurs the CPU pushesh onto the stack the error
 * code, sometimes not. Define two macro, one that pushes a 0 and then the
 * interrupt number, and the second that pushes only the number of the
 * interrupt. Both will then jmp to a common stub. So we can manage ALL
 * interrupts in the same routes.
 */

.macro isr_noerrcode num
	.globl	isr\num
	.type	isr\num, @function

	isr\num:
		cli
		push	$0
		push	$\num
		jmp	isr_common_stub
.endm

.macro isr_errcode num
	.globl	isr\num
	.type	isr\num, @function

	isr\num:
		cli
		push	$\num
		jmp	isr_common_stub
.endm

/* Define the first 32 interrupt handler.

	rc snippet:
	for (i in `{seq 0 31}) {
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
isr_errcode	8
isr_noerrcode	9
isr_errcode	10
isr_errcode	11
isr_errcode	12
isr_errcode	13
isr_errcode	14
isr_noerrcode	15
isr_noerrcode	16
isr_noerrcode	17
isr_noerrcode	18
isr_noerrcode	19
isr_noerrcode	20
isr_noerrcode	21
isr_noerrcode	22
isr_noerrcode	23
isr_noerrcode	24
isr_noerrcode	25
isr_noerrcode	26
isr_noerrcode	27
isr_noerrcode	28
isr_noerrcode	29
isr_noerrcode	30
isr_noerrcode	31

/* then define the common stub */

/* extern function to handle the interrupt */
.extern	isr_handler

.type	isr_common_stub, @function

/* isr_common_stub - save the processor state, sats up for kernel mode
 * segments, calls the C fault handler and finally restores the stack
 * frame!
 *
 * stack: error code and interrupt number */
isr_common_stub:
	/* pushes edi,esi,ebp,esp,ebx,edx,ecx,eax */
	pusha

	mov	%ds, %ax
	push	%eax

	mov	$0x10, %ax	/* load kernel data segment */
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	call	isr_handler	/* call the handler */

	/* restore the original data segment descriptor */
	pop	%eax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	popa			/* pops edi,esi,ebp,... */

	/* cleans up the pushed error code and ISR number */
	add	$8, %esp
	
	sti	/* is it needed? */

	/* pops 5 things at once: cs,eip,eflags,ss,esp */
	iret

/* do the same thing for irqs */

.macro irq n m
	.globl	irq\n
	.type	irq\n, @function
	
	irq\n:	cli
		push	$0
		push	$\n
		jmp	irq_common_stub
		
.endm

/* define the 15 interrupt handlers for the PIC

	for (i in `{seq 0 15})
		echo 'irq	'^$i `{echo $i + 32 | bc}
 */

irq	0  32
irq	1  33
irq	2  34
irq	3  35
irq	4  36
irq	5  37
irq	6  38
irq	7  39
irq	8  40
irq	9  41
irq	10 42
irq	11 43
irq	12 44
irq	13 45
irq	14 46
irq	15 47

/* irq_common_sutb - save the processor state, sats up for kernel mode
 * segments, calls the C fault handler and finally restores the stack
 * frame!
 *
 * stack: 0 and irq number
 */
irq_common_stub:
	/* pushes edi,esi,ebp,esp,ebx,edx,ecx,eax */
	pusha

	mov	%ds, %ax
	push	%eax

	mov	$0x10, %ax	/* load kernel data segment */
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	call	irq_handler	/* call the handler */

	/* restore the original data segment descriptor */
	pop	%eax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	popa			/* pops edi,esi,ebp,... */

	/* cleans up the pushed error code and ISR number */
	add	$8, %esp
	
	sti	/* is it needed? */

	/* pops 5 things at once: cs,eip,eflags,ss,esp */
	iret
