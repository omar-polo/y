.section ".text"

// loop n times.
.globl delay
delay:	subs	w0, w0, #1
	bne	delay
	ret
