
An os for fun. It does pratically nothing so far.

When it'll be capable of doing *something*, I'll update this doc.

## running

deps:

 - freestanding GCC + binutils for i386 somewhere in $PATH (see [here](https://wiki.osdev.org/GCC_Cross-Compiler))
 - qemu (with i386 emulation enabled) or bochs (or both)
 - GNU make: sorry for this. I'm working on a linux env atm and I cannot
 find a copy of OpenBSD make to run. I also needed `include`s and `if`s.
 - grub if you want a bootable ISO. Depending on the OS you may need to install also xorriso and mtools

At the moment it only works (for some definition of the word) on i386.

	make run

should start qemu with the kernel running.

	make iso

should produce a file `y.iso` capable of booting.

## code fmt

The code should be formatted with
[indent](https://invisible-island.net/cindent/cindent.html) using this
set of rules:

	indent -bad -bap -bbb -sc -br -ce -npcs -nbc -psl -ta -i4 -ts4 -cli0 -lps

## resources

 - [arm a64 instruction set](https://static.docs.arm.com/100898/0100/the_a64_Instruction_set_100898_0100.pdf)
 - [arm v8 reference manual](https://static.docs.arm.com/ddi0487/db/DDI0487D_b_armv8_arm.pdf)
 - [intel - AT&T syntax](https://www.imada.sdu.dk/~kslarsen/dm546/Material/IntelnATT.htm)
 - [little book about os dev](https://littleosbook.github.io/#output)
 - [james molloy kernel tutorial](http://www.jamesmolloy.co.uk/tutorial_html/) (used for gdt/idt)
 - [intel manuals](https://software.intel.com/en-us/articles/intel-sdm)
