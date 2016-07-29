#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Not a cross-compiler!"
#endif

#if !defined(__i386__)
#error "Target does not match! =/= i386"
#endif

// HW color modes
enum vga_colour {
    C_BLACK = 0,
    C_BLUE = 1,
    C_GREEN = 2,
    C_CYAN = 3,
    C_RED = 4,
    C_MAGENTA = 5,
    C_BROWN = 6,
    C_L_GRAY = 7, // L = LIGHT
    C_D_GRAY = 8, // D = DARK
    C_L_BLUE = 9,
    C_L_GREEN = 10,
    C_L_CYAN = 11,
    C_L_RED = 12,
    C_L_MAGENTA = 13,
    C_L_BROWN = 14,
    C_WHITE = 15,
};

uint8_t make_colour(enum vga_colour fg, enum vga_colour bg) {
    return fg | bg << 4; // foreground and background colours combined using
                         // 4-place shift
}

uint16_t make_vgaentry(char c, uint8_t colour) {
    uint16_t c16 = c;
    uint16_t colour16 = colour;
    return c16 | colour16 << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint16_t* terminal_buffer;

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_colour = make_colour(C_L_GRAY, C_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
	for (size_t x = 0; x < VGA_WIDTH; x++) {
	    const size_t index = y * VGA_WIDTH + x;
	    terminal_buffer[index] = make_vgaentry(' ', terminal_colour);
	}
    }
}

void terminal_setcolour(uint8_t colour) {
    terminal_colour = colour;
}

void terminal_copy(size_t source_x, size_t source_y, size_t x, size_t y) {
    const size_t source_index = source_y * VGA_WIDTH + source_x;
    const size_t index = y * VGA_WIDTH + x;

    terminal_buffer[index] = terminal_buffer[source_index];
}

void terminal_copy_row(size_t source_y, size_t y) {
    size_t source_x = source_y * VGA_WIDTH;
    size_t x = y * VGA_WIDTH;

    while (x < (1+y) * VGA_WIDTH) {
	terminal_copy(source_x, source_y, x, y);

	source_x++;
	x++;
    }
}

void terminal_clear_char(size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(' ', C_BLACK);
}

void terminal_clear_row(size_t y) {
    for (size_t x = y * VGA_WIDTH; x < (1+y) * VGA_WIDTH; x++) {
	terminal_clear_char(x, y);
    }
}

void terminal_scroll_ugly() {
    for (size_t y = 0; y < VGA_HEIGHT-1; y++) {
	terminal_copy_row(y+1, y);
	terminal_clear_row(y+1);
    }
    //terminal_clear_row(VGA_HEIGHT);
}

void terminal_putentryat(char c, uint8_t colour, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, colour);
}


void terminal_putchar(char c) {
    if (c == '\n') {
	terminal_column = 0;
	if (++terminal_row == VGA_HEIGHT) {
	    terminal_row--;
	    terminal_scroll_ugly();
	}
	return;
    } else {
        terminal_putentryat(c, terminal_colour, terminal_column, terminal_row);
    }
    
    if (++terminal_column == VGA_WIDTH) {
	terminal_column = 0;
	if (++terminal_row == VGA_HEIGHT) {
	    terminal_row--;
	    terminal_scroll_ugly();
	    //terminal_row = 0;
	}
    }
}

void terminal_writestring(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++)
	terminal_putchar(data[i]);
}

extern "C"

void kernel_main() {
    //init terminal
    terminal_initialize();

    terminal_writestring("1Hello world! IT'S ALIVE!!!\n2Newline testing...\n3It works.");
}
