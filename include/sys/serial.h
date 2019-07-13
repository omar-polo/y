#ifndef SYS_SERIAL_H
#define SYS_SERIAL_H

#include <stddef.h>
#

void	serial_init();

size_t	serial_write(void*, size_t);

#endif
