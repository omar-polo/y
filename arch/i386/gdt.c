#include "gdt.h"
#include "dts_utils.h"

/* our gdt is stored here! */
struct gdt_entry my_gdt[5];

void
gdt_init()
{
	struct gdt g;

	my_gdt[0] = GDT_INIT_ENTRY(0, 0, 0);	/* null segment */
	my_gdt[1] = GDT_INIT_ENTRY(0xc09a, 0, 0xfffff);		/* kernel cs */
	my_gdt[2] = GDT_INIT_ENTRY(0xc092, 0, 0xfffff);		/* kernel ds */
	my_gdt[3] = GDT_INIT_ENTRY(0xc0fa, 0, 0xfffff);		/* userland cs */
	my_gdt[4] = GDT_INIT_ENTRY(0xc0f2, 0, 0xfffff);		/* userland ds */

	g.base = my_gdt;
	g.limit = 5 * sizeof(struct gdt_entry);

	gdt_flush(&g);
}
