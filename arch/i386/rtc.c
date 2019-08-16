#include "rtc.h"

#include "b.h"
#include "debug.h"
#include "handler.h"

void
rtc_init(uint32_t freq)
{
	uint32_t div;
	uint16_t h, l;

	handler_register(32, &irq_rtc);

	div = 1193180 / freq;
	debugf("initializing rtc with a div of %d.\n", div);

	l = (div & 0xFF);
	h = ((div >> 8) & 0xFF);

	outb(0x43, 0x36);
	outb(0x40, l);
	outb(0x40, h);
}

void
irq_rtc(struct cpu_state c)
{
	/* debugf("tick\n"); */
}
