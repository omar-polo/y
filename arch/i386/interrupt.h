#ifndef I386_INTERRUPT_H
#define I386_INTERRUPT_H

/*
	for (i in `{seq 0 31})
		echo void isr$i'();'
 */

/* In reality, some of these function (isr8, 10-14 inclusive)
 * takes parameters.  But, since are definied in assembly and
 * we need the prototype only for C type checking (to get the
 * address for the IDT later during the linker phase), the
 * may be incomplete */

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void irq32();
void irq33();

#endif
