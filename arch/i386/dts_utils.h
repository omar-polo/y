#ifndef I386_DTS_UTILS_H
#define I386_DTS_UTILS_H

#include <stdint.h>

void	gdt_flush(uint32_t);

void	idt_flush(uint32_t);

#endif
