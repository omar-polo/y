#ifndef I386_DT_H
#define I386_DT_H

/* Contains structure and functions for managing the GDT and IDT */

#include <stdint.h>

/* contains the value of one GDT entry. */
struct gdt_entry {
	uint16_t	limit_low;	/* lower 16 bit of the limit  */
	uint16_t	base_low;	/* lower 16 bit of the base   */
	uint8_t		base_middle;	/* the next 8 bit of the base */
	uint8_t		access;		/* determine the ring         */
	uint8_t		granularity;
	uint8_t		base_high;	/* last 8 bit of the base     */
} __attribute__((packed));

struct gdt_ptr {
	uint16_t	limit;	/* upper 16 bits of all sector limits */
	uint32_t	base;	/* address of the irst gdt_entry      */
} __attribute__((packed));

/* represents an interrupt gate */
struct idt_entry {
	/* lower 16 bits of the address to jump when this interrupt fires */
	uint16_t	base_lo;
	
	uint16_t	sel;	/* kernel segment selector          */
	uint8_t		always0;/* must always be 0 (for *reasons*) */
	uint8_t		flags;	/* more flags.                      */
	
	/* upper 16 bit of the address to jump to */
	uint16_t	base_hi;
} __attribute__((packed));

/* represents a pointer to an arra of interrupt handlers.
 * format suitable for a `lidt'.
 */
struct idt_ptr {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed));

void	init_dts();

#endif
