CC = i686-elf-gcc
CP = i686-elf-g++
AS = i686-elf-as
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

ODIR = obj

OBJ_LINK := $(ODIR)/crti.o $(CRTBEGIN_OBJ) $(ODIR)/boot.o $(ODIR)/kernel.o $(CRTEND_OBJ) $(ODIR)/crtn.o

all: crti crtn kernel boot link

crti:
	$(AS) crti.s -o $(ODIR)/crti.o

crtn:
	$(AS) crtn.s -o $(ODIR)/crtn.o

kern_link: kernel link

kernel: $(OBJ_LINK)
	$(CP) -c kernel.cpp -o $(ODIR)/kernel.o $(CFLAGS)

boot:
	$(AS) boot.s -o $(ODIR)/boot.o

link:
	$(CC) -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib $(OBJ_LINK) -lgcc

run:
	qemu-system-i386 -kernel os.bin

clean:
	rm $(ODIR)/*.o
