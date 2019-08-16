#include "handler.h"

#include "debug.h"
#include "b.h"

#include <mem.h>

handlerfn handlers[256];

void
handler_init()
{
	memset(handlers, 0, 256 * sizeof(handlers));
}

void
handler_register(uint32_t n, handlerfn fn)
{
	debugf("registering handler for interrupt #%d\n", n);
	if (n < 256)
		handlers[n] = fn;
}

void
interrupt_handler(struct cpu_state c, uint32_t in, uint32_t err)
{
	handlerfn fn;

	fn = handlers[in];
	if (fn == nil)
		debugf("un-handled interrupt #%d (err: %d)\n", in, err);
	else
		fn(c, in, err);
}

void
irq_handler(struct cpu_state c, uint32_t in, uint32_t err)
{
	handlerfn fn;

	if (in >= 40)
		outb(0xA0, 0x20);
	outb(0x20, 0x20);

	fn = handlers[in];
	if (fn == nil)
		debugf("un-handled irq #%d (err: %d)\n", in, err);
	else
		fn(c, in, err);
}
