#ifndef I386_B_H
#define I386_B_H

#include <stdint.h>

/* read the given data port */
char inb(uint16_t port);

/* sends the given data to the given i/o port. */
void outb(uint16_t port, uint8_t data);

#endif
