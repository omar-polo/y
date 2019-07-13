#include "isr.h"

#include "debug.h"

void
isr_handler(struct registers r)
{
	/* I don't think doing I/O in an interrupt handler
	 * is a good idea. But, at the moment, we don't have
	 * a better mechanisms to manage this, so log to the
	 * serial the interrupt received for debug purpose */
	debugf("interrupt #%d - err #%d\n", r.int_no, r.err_code);

	/* TODO: do something */
}
