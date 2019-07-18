#include <fmt.h>

#include <stdint.h>
#include <string.h>

void
fmt(writefn fn, char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vafmt(fn, fmt, args);
	va_end(args);
}

/* remember that x86 is little-endian */
#define HEXFMT(fn, v, len) {						\
		int8_t vp;									\
		int i, p;									\
		p = 0;										\
		fn("0x", 2);								\
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
			fn(&vp, 1);								\
		}											\
		if (!p)										\
			fn("0", 1);								\
	}

#define DECFMT(fn, v, len, buf, buflen) {			\
		int i, q, r;								\
		i = buflen-1;								\
		buf[i--] = '\0';							\
		if (v == 0) {								\
			buf[i] = '0';							\
			fn(buf+i, 1);							\
		} else {									\
			do {									\
				q = v / 10;							\
				r = v % 10;							\
				buf[i--] = r + '0';					\
				v = q;								\
			} while(q != 0);						\
			i++;									\
			fn(buf+i, buflen-i);					\
		}											\
	}

void
vafmt(writefn fn, char *fmt, va_list l)
{
	/* should be enough even for 64bit integer */
	char buf[32];

	for (; *fmt; fmt++) {
		if (*fmt != '%') {
			fn(fmt, 1);
			continue;
		}

		if (!*(++fmt)) {
			fn("\nNUL after %\n", 13);
			return;
		}

		switch (*fmt) {
		case '%':
			fn("%", 1);
			break;

		case 'd':{
				int32_t v;
				v = va_arg(l, int32_t);

				if (v < 0) {
					fn("-", 1);
					v *= -1;
				}

				DECFMT(fn, v, 4, buf, 32);
				break;
			}

		case 'x':{
				int32_t v;
				v = va_arg(l, int32_t);

				if (v < 0) {
					fn("-", 1);
					v *= -1;
				}

				HEXFMT(fn, v, 4);
				break;
			}

		case 'u':{
				uint32_t v;
				v = va_arg(l, int32_t);

				DECFMT(fn, v, 4, buf, 32);
				break;
			}

		case 'X':{
				uint32_t v;
				v = va_arg(l, uint32_t);

				HEXFMT(fn, v, 4);
				break;
			}

		case 'h':
			/* look up next char */
			if (!*(++fmt)) {
				fn("\nNUL after h\n", 13);
				return;
			}
			switch (*fmt) {
			case 'd':{
					int v;
					v = va_arg(l, int);

					if (v < 0) {
						fn("-", 1);
						v *= -1;
					}

					DECFMT(fn, v, 2, buf, 32);
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
						fn("-", 1);
						v *= -1;
					}

					HEXFMT(fn, v, 2);
					break;
				}

			case 'u':{
					unsigned int v;
					v = va_arg(l, unsigned int);

					DECFMT(fn, v, 2, buf, 32);
					break;
				}

			case 'X':{
					/*
					 * uint16_t are promoted to int when passed to vaargs
					 * functions. 
					 */
					unsigned int v;
					v = va_arg(l, unsigned int);

					HEXFMT(fn, v, 2);
					break;
				}
			}
			break;

		case 'l':
			/* look up next char */
			if (!*(++fmt)) {
				fn("\nNUL after l\n", 13);
				return;
			}
			switch (*fmt) {
			case 'd':{
					int64_t v;
					v = va_arg(l, int64_t);

					if (v < 0) {
						fn("-", 1);
						v *= -1;
					}

					DECFMT(fn, v, 8, buf, 32);
					break;
				}

			case 'x':{
					int64_t v;
					v = va_arg(l, int64_t);

					if (v < 0) {
						fn("-", 1);
						v *= -1;
					}

					HEXFMT(fn, v, 8);
					break;
				}

			case 'u':{
					uint64_t v;
					v = va_arg(l, uint64_t);

					DECFMT(fn, v, 8, buf, 32);
					break;
				}

			case 'X':{
					uint64_t v;
					v = va_arg(l, uint64_t);

					HEXFMT(fn, v, 8);
					break;
				}
			}
			break;

		case 'c':{
				/*
				 * char are promoted to int when passed to vaargs
				 * functions. 
				 */
				int v;
				char c;
				v = va_arg(l, int);

				c = (char) v;
				fn(&c, 1);
				break;
			}

		case 's':{
				char *s;
				s = va_arg(l, char *);

				fn(s, strlen(s));
				break;
			}
		}
	}
}

#undef DECFMT
#undef HEXFMT
