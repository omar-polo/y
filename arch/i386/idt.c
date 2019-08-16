#include "idt.h"

#include <mem.h>

#include "interrupt.h"
#include "dts_utils.h"
#include "b.h"
#include "rtc.h"

struct idt_entry my_idt[256];

void
idt_init()
{
	struct idt idt;

	idt.base = my_idt;
	idt.limit = 256 * sizeof(struct idt_entry);

	/* zero everything, so we can load only the entries we are
	 * interested in.  This should work because setting all the
	 * bytes to 0 will set also the P (present) flag, disabling
	 * that handler. */
	memset(&my_idt, 0, 256 * sizeof(struct idt_entry));

	/*
	 * for (i in `{seq 0 18}) echo 'my_idt['$i'] = IDT_INIT_ENTRY((uint32_t)&isr'$i', 0x8E);'
	 */
	my_idt[0] = IDT_INIT_ENTRY((uint32_t) &isr0, 0x8E);
	my_idt[1] = IDT_INIT_ENTRY((uint32_t) &isr1, 0x8E);
	my_idt[2] = IDT_INIT_ENTRY((uint32_t) &isr2, 0x8E);
	my_idt[3] = IDT_INIT_ENTRY((uint32_t) &isr3, 0x8E);
	my_idt[4] = IDT_INIT_ENTRY((uint32_t) &isr4, 0x8E);
	my_idt[5] = IDT_INIT_ENTRY((uint32_t) &isr5, 0x8E);
	my_idt[6] = IDT_INIT_ENTRY((uint32_t) &isr6, 0x8E);
	my_idt[7] = IDT_INIT_ENTRY((uint32_t) &isr7, 0x8E);
	my_idt[8] = IDT_INIT_ENTRY((uint32_t) &isr8, 0x8E);
	my_idt[9] = IDT_INIT_ENTRY((uint32_t) &isr9, 0x8E);
	my_idt[10] = IDT_INIT_ENTRY((uint32_t) &isr10, 0x8E);
	my_idt[11] = IDT_INIT_ENTRY((uint32_t) &isr11, 0x8E);
	my_idt[12] = IDT_INIT_ENTRY((uint32_t) &isr12, 0x8E);
	my_idt[13] = IDT_INIT_ENTRY((uint32_t) &isr13, 0x8E);
	my_idt[14] = IDT_INIT_ENTRY((uint32_t) &isr14, 0x8E);
	my_idt[15] = IDT_INIT_ENTRY((uint32_t) &isr15, 0x8E);
	my_idt[16] = IDT_INIT_ENTRY((uint32_t) &isr16, 0x8E);
	my_idt[17] = IDT_INIT_ENTRY((uint32_t) &isr17, 0x8E);
	my_idt[18] = IDT_INIT_ENTRY((uint32_t) &isr18, 0x8E);
	/* 19..31 are reserved by intel */

	/* remap the PIC so its interrupt are in the range 32...47
	 * inclusive */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	/*
	 * for (i in `{seq 32 47}) echo 'my_idt['$i'] = IDT_INIT_ENTRY(&irq'$i', 0x8E);'
	 */
	my_idt[32] = IDT_INIT_ENTRY((uint32_t) &irq32, 0x8E);	/* real time clock */
	//my_idt[33] = IDT_INIT_ENTRY((uint32_t) &irq_kbd, 0x8E);  /* i/o (keyboard)  */

	idt_flush(&idt);
}
