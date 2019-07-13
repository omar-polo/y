#include "dts.h"

#include <sys/serial.h>

void	kernel_main(void);

void
kinit(void)
{
	/* init the serial */
	serial_init();

	init_dts();
	
	kernel_main();
}