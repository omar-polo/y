#ifndef I386_GDT_H
#define I386_GDT_H

#include <stdint.h>

struct gdt_entry {
	union {
		struct {
			uint32_t a;
			uint32_t b;
		};
		struct {
			uint16_t limit0;
			uint16_t base0;
			uint16_t base1:8, type:4, s:1, dpl:2, p:1;
			uint16_t limit:4, avl:1, l:1, d:1, g:1, base2:8;
		};
	};
} __attribute__((packed));

/* easy way to init a gdt entry */
#define GDT_INIT_ENTRY(flags, base, limit) (struct gdt_entry){				\
	{																		\
		{																	\
			.a = ((limit) & 0xffff) | (((base) & 0xffff) << 16),			\
			.b = (((base) & 0xff0000) >> 16) | (((flags) & 0xf0ff) << 8) |	\
					((limit) & 0xf0000) | ((base) & 0xff000000),			\
		}																	\
	}																		\
}

struct gdt {
	uint16_t limit;
	struct gdt_entry *base;
} __attribute__((packed));

void gdt_init();

#endif
