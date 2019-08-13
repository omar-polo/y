#include "debug.h"

#include <sys/serial.h>

#include <fmt.h>

void
debugf(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);

	vafmt(serial_write, fmt, args);

	va_end(args);
}

void
vadebug(char *fmt, va_list l)
{
	vafmt(serial_write, fmt, l);
}
