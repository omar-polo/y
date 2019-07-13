/* declare constants for the multiboot header. */
.set ALIGN,	1<<0		/* align loaded modules on page boundaries */
.set MEMINFO,	1<<1		/* provide memory map */
.set FLAGS,	0		/* multiboot flag field */
.set MAGIC,	0x1BADB002	/* magic number lets bootloader find the header */
.set CHECKSUM,	-(MAGIC+FLAGS)	/* checksum of above */

/* declare a multiboot header that marks the problam as a kernel.
 * These are magic values that are documented in the multiboot standard.
 * The bootloader will search for this signature in the first 8KiB of the
 * kernel file, aligned at a 32-bit boundary.  The signature is in its own
 * section so the header can be forced to be within the first 8KiB of the
 * kernel file. */
.section .multiboot
.align 0x4
.long MAGIC
.long FLAGS
.long CHECKSUM
