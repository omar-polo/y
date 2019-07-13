#include "dts.h"

#include "dts_utils.h"
#include "interrupt.h"
#include "b.h"

/* Initialize the GDT and IDT and defines the default ISR and IRQ
 * handler.
 */

struct gdt_entry	gdt_entries[5];
struct gdt_ptr		gdt_ptr;
struct idt_entry	idt_entries[256];
struct idt_ptr		idt_ptr;

/* Set the value of one GDT entry. */
static inline void
gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);

	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= gran & 0xF0;

	gdt_entries[num].access = access;
}

static inline void
init_gdt()
{
	gdt_ptr.limit = sizeof(struct gdt_entry) * 5 -1;
	gdt_ptr.base  = (uint32_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);			/* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	/* code */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	/* data */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	/* user mode code */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	/* user mode data */

	gdt_flush((uint32_t)&gdt_ptr);
}

static inline void
idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;

	/* TODO: uncomment the OR when we get user-mode.
	 * it sets the interrupt gate's privilege level to 3
	 */
	idt_entries[num].flags = flags /* | 0x60 */ ;
}

static inline void
init_idt()
{
	uint32_t	i;

	idt_ptr.limit = sizeof(struct idt_entry) * 256 -1;
	idt_ptr.base  = (uint32_t)&idt_entries;

	/* memset(&idt_entries, 0, sizeof(idt_entry_t)*256); */
	for (i = 0; i < 256; i++) {
		idt_entries[i].base_lo = 0;
		idt_entries[i].sel     = 0;
		idt_entries[i].always0 = 0;
		idt_entries[i].flags   = 0;
		idt_entries[i].base_hi = 0;
	}

	/* rc snippet:
	for (i in `{seq 0 31})
		echo '	idt_set_gate('^$i^', (uint32_t)isr'^$i^', 0x08, 0x8E);'
	*/
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	/* remap the PCIs */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0 );
	outb(0xA1, 0x0 );

	/* set handler for the IRQ

	rc snippet:
	for (i in `{seq 0 15})
		echo '	idt_set_gate('^$i^', (uint32_t)irq'^$i^', 0x08, 0x8E);'
	*/
	idt_set_gate(0,  (uint32_t)irq0,  0x08, 0x8E);
	idt_set_gate(1,  (uint32_t)irq1,  0x08, 0x8E);
	idt_set_gate(2,  (uint32_t)irq2,  0x08, 0x8E);
	idt_set_gate(3,  (uint32_t)irq3,  0x08, 0x8E);
	idt_set_gate(4,  (uint32_t)irq4,  0x08, 0x8E);
	idt_set_gate(5,  (uint32_t)irq5,  0x08, 0x8E);
	idt_set_gate(6,  (uint32_t)irq6,  0x08, 0x8E);
	idt_set_gate(7,  (uint32_t)irq7,  0x08, 0x8E);
	idt_set_gate(8,  (uint32_t)irq8,  0x08, 0x8E);
	idt_set_gate(9,  (uint32_t)irq9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)irq15, 0x08, 0x8E);

	/* finally, flush the table! */
	idt_flush((uint32_t)&idt_ptr);
}

void
init_dts()
{
	init_gdt();
	init_idt();
}
