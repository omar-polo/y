#include <mem.h>

void *
memset(void *b, int c, size_t len)
{
	size_t i;
	unsigned char d, *e;

	d = c;
	e = b;

	for (i = 0; i < len; ++i)
		e[i] = d;

	return b;
}