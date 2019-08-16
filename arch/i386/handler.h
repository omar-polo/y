#ifndef I386_HANDLER_H
#define I386_HANDLER_H

#include <stdint.h>

struct cpu_state {
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
} __attribute__((packed));

typedef void (*handlerfn) (struct cpu_state, uint32_t, uint32_t);

void handler_init();
void handler_register(uint32_t, handlerfn);
void interrupt_handler(struct cpu_state, uint32_t, uint32_t);
void irq_handler(struct cpu_state, uint32_t, uint32_t);

#endif
