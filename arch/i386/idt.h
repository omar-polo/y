#ifndef I386_IDT_H
#define I386_IDT_H

#include <stdint.h>

struct idt_entry {
	uint16_t offset_low;
	uint16_t sselector;
	uint8_t zero;
	uint8_t type;
	uint16_t offset_high;
} __attribute__((packed));

#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define IDT_INIT_ENTRY(offset, t) (struct idt_entry){			\
		.offset_low  = ((offset) & 0xffff),						\
		.sselector   = KERNEL_CODE_SEGMENT_OFFSET,				\
		.zero        = 0,										\
		.type        = t,										\
		.offset_high = (((offset) & 0xffff0000) >> 16),			\
	}

struct idt {
	uint16_t limit;
	struct idt_entry *base;
} __attribute__((packed));

void idt_init();

#endif
