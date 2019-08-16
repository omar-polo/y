#include <sys/term.h>
#include <sys/serial.h>

#include <arch/i386/debug.h>

void
kernel_main(void)
{
	/* this should NOT triple fault and reset */
	__asm__("int $0x6");
	__asm__("int $0x2");
	__asm__("int $0x0");

	/* test serial */
	serial_write("hello, serial!\n", 15);

	/* do the same to the screen */
	term_init();
	term_write("hello, world!\n", 14);

	/* try the debug facilities */
	debugf("my fav number is %u\n", 0xCAFEF00D);

	debugf("goodbye");
}
