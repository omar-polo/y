#ifndef FMT_H
#define FMT_H

#include <stdarg.h>
#include <stddef.h>
/* *INDENT-OFF* */
/* indent wrong indent the following line */

typedef size_t (*writefn) (void *, size_t);

/* *INDENT-ON* */

void fmt(writefn, char *, ...);
void vafmt(writefn, char *, va_list);

#endif
