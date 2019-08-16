#ifndef I386_DTS_UTILS_H
#define I386_DTS_UTILS_H

#include <stdint.h>

#include "gdt.h"
#include "idt.h"

void gdt_flush(struct gdt *);

void idt_flush(struct idt *);

#endif
