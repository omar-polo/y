#include "term.h"
#include "b.h"

uint16_t term_x, term_y;

void
term_move_cursor(uint16_t x, uint16_t y)
{
	uint16_t pos;

	pos = y * VGA_WIDTH + x;

	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

void
term_init()
{
	uint32_t x, y;
	uint16_t *buf, entry;

	buf = (uint16_t *) TERM_ADDR;
	entry = vga_entry(' ', DEFAULT_COLOR);

	for (y = 0; y < VGA_HEIGHT; y++)
		for (x = 0; x < VGA_WIDTH; x++)
			buf[y * VGA_WIDTH + x] = entry;

	term_move_cursor(0, 0);
	term_x = term_y = 0;
}

static inline void
term_newln()
{
	uint16_t x, y, ni, oi, *buf;

	buf = (uint16_t *) TERM_ADDR;

	if (++(term_y) == VGA_HEIGHT) {
		term_y = VGA_HEIGHT - 1;

		/* scroll lines */
		for (y = 1; y < VGA_HEIGHT; ++y) {
			for (x = 0; x < VGA_WIDTH; ++x) {
				ni = y * VGA_WIDTH + x;
				oi = (y - 1) * VGA_WIDTH + x;
				buf[oi] = buf[ni];
			}
		}

		/* empty out last line */
		for (x = 0; x < VGA_WIDTH; ++x) {
			ni = term_y * VGA_WIDTH + x;
			buf[ni] = vga_entry(' ', DEFAULT_COLOR);
		}
	}

	term_x = 0;
}

size_t
term_write(void *b, size_t len)
{
	size_t i;
	uint16_t index, *buf;
	char *bb;

	bb = b;
	buf = (uint16_t *) TERM_ADDR;

	for (i = 0; i < len; ++i) {
		if (bb[i] == '\n') {
			term_newln();
			continue;
		}

		index = term_y * VGA_WIDTH + term_x;
		buf[index] = vga_entry(bb[i], DEFAULT_COLOR);

		if (++term_x == VGA_WIDTH)
			term_newln();
	}

	term_move_cursor(term_x, term_y);

	return i;
}
