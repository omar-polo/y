#ifndef I386_TERM_H
#define I386_TERM_H

/* public APIs are in include/sys/term.h ! */

#include <stdint.h>

#include <sys/term.h>

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define TERM_ADDR 0xB8000

#define VGA_WIDTH	80
#define VGA_HEIGHT	25

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t
vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t
vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

#define DEFAULT_COLOR	(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK))

struct term {
	uint16_t x;
	uint16_t y;
};

void term_move_cursor(uint16_t x, uint16_t y);

#endif
