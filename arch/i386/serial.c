#include <stddef.h>

#include "serial.h"
#include "b.h"

/* Check if the transmit FIFO queue for the given COM port is empty.
 */
int
serial_is_fifo_empty(uint32_t com)
{
	/* we need to check if the 5th bit is 1 or not:
	 * 0x20 = 0010_0000 */
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/* initialize the serial (assumed COM1) */
void
serial_init()
{
	int port = SERIAL_COM1_BASE;

	outb(port + 1, 0x00);	/* Disable all interrupts */
	outb(port + 3, 0x80);	/* Enable DLAB (set baud rate divisor) */
	outb(port + 0, 0x03);	/* Set divisor to 3 (lo byte) 38400 baud */
	outb(port + 1, 0x00);	/*                  (hi byte) */
	outb(port + 3, 0x03);	/* 8 bits, no parity, one stop bit */
	outb(port + 2, 0xC7);	/* Enable FIFO, clear them, with 14-byte threshold */
	outb(port + 4, 0x0B);	/* IRQs enabled, RTS/DSR set */
}

static void
serial_write_char(uint8_t c)
{
	while(!serial_is_fifo_empty(SERIAL_COM1_BASE))
			; /* spin */
	outb(SERIAL_COM1_BASE, c);
}

/* write(2)-like for the serial port - assume COM1 */
size_t
serial_write(void *b, size_t len)
{
	size_t	i;
	char	*s;
	
	s = b;
	
	for (i = 0; i < len; i++) {
		/* CRLF is needed on the serial */
		if (s[i] == '\n') {
			serial_write_char('\r');
		}
		serial_write_char(s[i]);
	}

	return len;
}
