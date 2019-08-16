/* gdt_flush - load the gdt table
 * stack: 4(esp) the pointer to the gdt struct
 */
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	mov		4(%esp), %eax	/* get the pointer  */
	lgdt	(%eax)			/* load the new GDT */

	mov		$0x10, %ax	/* data offset */

	/* move the correct offset to ALL registers */
	mov		%ax, %ds
	mov		%ax, %es
	mov		%ax, %fs
	mov		%ax, %gs
	mov		%ax, %ss

	/* do a far jump to set the cs. */
	ljmp	$0x08,$flush
flush:
	ret


/* idt_flush - load the idt table
 * stack: 4(esp) the pointer to the idt struct
 */
.global idt_flush
.type idt_flush, @function
idt_flush:
	mov		4(%esp), %eax
	lidt	(%eax)
	ret
