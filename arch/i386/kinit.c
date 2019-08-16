#include "gdt.h"
#include "idt.h"
#include "rtc.h"

#include <sys/serial.h>

void kernel_main(void);

void
kinit(void)
{
	/* init the serial */
	serial_init();

	gdt_init();
	idt_init();

	rtc_init(50);

	/* make sure that now the interrupt are enabled */
	__asm__("sti");

	kernel_main();

	while (1);
}