.global outb
.type outb, @function
/* outb - send a byte to an I/O port
 * stack: 8(esp) the data byte
 *        4(esp) the I/O port
 *         (esp) return addr
 */
outb:
	mov 8(%esp), %al	# move the data to be sent into the al register
	mov 4(%esp), %dx	# move the address of the I/O port into the dx reg
	out %al, %dx		# send the data to the I/O port
	ret

.global	inb
.type	inb, @function
/* inb - read a byte from a I/O port
 * stack: 4(esp) the address of the port
 *         (esp) the return address
 */
inb:
	mov	4(%esp),	%dx
	in	%dx,		%al
	ret
