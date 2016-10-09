#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/tty.h>

extern "C"

void kernel_early(void) {
	terminal_initialize();
}

extern "C"

void kernel_main(void) {
	printf("%s","Booting completed.\nTerminal init completed.\nIt seems I'm working OK.");
}
