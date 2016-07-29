CC = i686-elf-gcc
CP = i686-elf-g++
AS = i686-elf-as

CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

ARCH := $(shell ../arch.sh)

CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

ODIR = obj

OBJ_LINK := arch/$(ARCH)/$(ODIR)/crti.o $(CRTBEGIN_OBJ) arch/$(ARCH)/$(ODIR)/boot.o kernel/$(ODIR)/kernel.o $(CRTEND_OBJ) arch/$(ARCH)/$(ODIR)/crtn.o

all: crti crtn kernel boot link

crti:
	$(AS) arch/$(ARCH)/crti.s -o arch/$(ARCH)/$(ODIR)/crti.o

crtn:
	$(AS) arch/$(ARCH)/crtn.s -o arch/$(ARCH)/$(ODIR)/crtn.o

kern_link: kernel link

kernel:
	$(CP) -c kernel/kernel.cpp -o kernel/$(ODIR)/kernel.o $(CFLAGS)

boot:
	$(AS) arch/$(ARCH)/boot.s -o arch/$(ARCH)/$(ODIR)/boot.o

link:
	$(CC) -T arch/$(ARCH)/linker.ld -o ../bin/os.bin -ffreestanding -O2 -nostdlib $(OBJ_LINK) -lgcc

clean:
	rm arch/$(ARCH)/$(ODIR)/*.o
	rm kernel/$(ODIR)/*.o

.PHONY: all crti crtn kern_link kernel boot link clean
