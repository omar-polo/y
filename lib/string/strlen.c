#include <string.h>

size_t
strlen(char *s)
{
	size_t i;
	i = 0;
	while (*s++)
		i++;
	return i;
}
