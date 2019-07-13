#ifndef SYS_TERM_H
#define SYS_TERM_H

#include <stddef.h>
#include <stdint.h>

#if defined(__i386__)
# include <arch/i386/term.h>
#endif

size_t	term_write(void *buf, size_t len);
void	term_init();

#endif