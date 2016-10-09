# thx osdev <3

# multiboot header constants
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# multiboot
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# some additional thingies
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# linker thingey
.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	call kernel_early

	call _init

	call kernel_main

	cli
.Lhang:
	hlt
	jmp .Lhang

.size _start, . - _start