#ifndef FMT_H
#define FMT_H

#include <stdarg.h>
#include <stddef.h>

typedef size_t(*writefn) (void *, size_t);

void fmt(writefn, char *, ...);
void vafmt(writefn, char *, va_list);

#endif
