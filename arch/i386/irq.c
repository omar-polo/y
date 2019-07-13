#include "irq.h"
#include "isr.h"
#include "b.h"

#include "debug.h"

void
irq_handler(struct registers r)
{
	/* Send an EOI signal to the PICS if this
	 * interrupt involved the slave. */
	if (r.int_no >= 40) {
		outb(0xA0, 0x20);
	}

	/* send reset signal to master */
	outb(0x20, 0x20);
	
	/* do something based on r.int_no */
	/* debugf("irq #%X\n", r.int_no); <- this breaks everything! */
}
