#ifndef I386_ISR_H
#define I386_ISR_H

#include <stdint.h>

struct registers {
	/* data segment selector */
	uint32_t	ds;
	
	/* pushed by pusha */
	uint32_t	edi, esi, esp, ebx, edx, ecx, eax;
	
	/* interrupt handler and error code (if applicable) */
	uint32_t	int_no, err_code;
	
	/* pushed by the cpu (automatically) */
	uint32_t	eip, cs, eflags, useresp, ss;
};

#endif
