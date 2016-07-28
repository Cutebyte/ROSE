CC = i686-elf-gcc
CP = i686-elf-g++
AS = i686-elf-as
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

ODIR = obj

all: kernel boot link

kernel:
	$(CP) -c kernel.cpp -o $(ODIR)/kernel.o $(CFLAGS)

boot:
	$(AS) boot.s -o $(ODIR)/boot.o

link:
	$(CC) -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib $(ODIR)/boot.o $(ODIR)/kernel.o -lgcc

run:
	qemu-system-i386 -kernel os.bin

clean:
	rm $(ODIR)/*.o
