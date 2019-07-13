#include "debug.h"

#include <sys/serial.h>

#include <stdarg.h>
#include <stdint.h>

#include <string.h>

void
debugf(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);

	vadebug(fmt, args);

	va_end(args);
}

/* remember that x86 is little-endian */
#define HEXFMT(v, len) {							\
		int8_t vp;									\
		int i, p;									\
		p = 0;										\
		serial_write("0x", 2);						\
		/* work nibble-by-nibble */					\
		for (i = 0; i < (len*2); ++i) {				\
			vp = (v >> ((len*2) -1 -i)*4) & 0x0F;	\
			if (!p && vp == 0)						\
				continue;							\
			p = 1;									\
			if (vp <= 9) {							\
				vp += '0';							\
			} else {								\
				vp += 'a' - 10;						\
			}										\
			serial_write(&vp, 1);					\
		}											\
		if (!p)										\
			serial_write("0", 1);					\
	}

#define DECFMT(v, len, buf, buflen) {				\
		int i, q, r, p;								\
		i = buflen-1;								\
		buf[i--] = '\0';							\
		if (v == 0) {								\
			buf[i] = '0';							\
			serial_write(buf+i, 1);					\
		} else {									\
			do {									\
				q = v / 10;							\
				r = v % 10;							\
				buf[i--] = r + '0';					\
				v = q;								\
			} while(q != 0);						\
			i++;									\
			serial_write(buf+i, buflen-i);			\
		}											\
	}

void
vadebug(char *fmt, va_list l)
{
	/* should be enough even for 64bit integer */
	char buf[32];

	for (; *fmt; fmt++) {
		if (*fmt != '%') {
			serial_write(fmt, 1);
			continue;
		}

		if (!*(++fmt)) {
			serial_write("\nNUL after %\n", 13);
			return;
		}

		switch (*fmt) {
		case '%':
			serial_write("%", 1);
			break;

		case 'd':{
				int32_t v;
				v = va_arg(l, int32_t);

				if (v < 0) {
					serial_write("-", 1);
					v *= -1;
				}

				DECFMT(v, 4, buf, 32);
				break;
			}

		case 'x':{
				int32_t v;
				v = va_arg(l, int32_t);

				if (v < 0) {
					serial_write("-", 1);
					v *= -1;
				}

				HEXFMT(v, 4);
				break;
			}

		case 'u':{
				uint32_t v;
				v = va_arg(l, int32_t);

				DECFMT(v, 4, buf, 32);
				break;
			}

		case 'X':{
				uint32_t v;
				v = va_arg(l, uint32_t);

				HEXFMT(v, 4);
				break;
			}

		case 'h':
			/* look up next char */
			if (!*(++fmt)) {
				serial_write("\nNUL after h\n", 13);
				return;
			}
			switch (*fmt) {
			case 'd':{
					int v;
					v = va_arg(l, int);

					if (v < 0) {
						serial_write("-", 1);
						v *= -1;
					}

					DECFMT(v, 2, buf, 32);
					break;
				}

			case 'x':{
					/*
					 * int16_t are promoted to int when passed * to vaargs
					 * functions. 
					 */
					int v;
					v = va_arg(l, int);

					if (v < 0) {
						serial_write("-", 1);
						v *= -1;
					}

					HEXFMT(v, 2);
					break;
				}

			case 'u':{
					unsigned int v;
					v = va_arg(l, unsigned int);

					DECFMT(v, 2, buf, 32);
					break;
				}

			case 'X':{
					/*
					 * int16_t are promoted to int when passed to vaargs
					 * functions. 
					 */
					unsigned int v;
					v = va_arg(l, unsigned int);

					HEXFMT(v, 2);
					break;
				}
			}
			break;

		case 'l':
			/* look up next char */
			if (!*(++fmt)) {
				serial_write("\nNUL after l\n", 13);
				return;
			}
			switch (*fmt) {
			case 'd':{
					int64_t v;
					v = va_arg(l, int64_t);

					if (v < 0) {
						serial_write("-", 1);
						v *= -1;
					}

					DECFMT(v, 8, buf, 32);
					break;
				}

			case 'x':{
					int64_t v;
					v = va_arg(l, int64_t);

					if (v < 0) {
						serial_write("-", 1);
						v *= -1;
					}

					HEXFMT(v, 8);
					break;
				}

			case 'u':{
					uint64_t v;
					v = va_arg(l, uint64_t);

					DECFMT(v, 8, buf, 32);
					break;
				}

			case 'X':{
					uint64_t v;
					v = va_arg(l, uint64_t);

					HEXFMT(v, 8);
					break;
				}
			}
			break;

		case 'c':{
				/*
				 * char are promoted to int when passed * to vaargs
				 * functions. 
				 */
				int v;
				char c;
				v = va_arg(l, int);

				c = (char) v;
				serial_write(&c, 1);
				break;
			}

		case 's':{
				char *s;
				s = va_arg(l, char *);

				serial_write(s, strlen(s));
				break;
			}
		}
	}
}

#undef DECFMT
#undef HEXFMT
