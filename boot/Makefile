# If you want to preset the SVGA mode, uncomment the next line and
# set SVGA_MODE to whatever number you want.
# Set it to -DSVGA_MODE=NORMAL_VGA if you just want the EGA/VGA mode.
# The number is the same as you would ordinarily press at bootup.

SVGA_MODE	:= -DSVGA_MODE=NORMAL_VGA

CC		:= gcc
AS		:= as
AR		:= ar
LD		:= ld
OBJCOPY		:= objcopy
INCLUDE_PATH	+= ../include

targets		:= setup.bin setup.elf

boot_sobjs	+= header.o
boot_sobjs	+= bioscall.o
boot_sobjs	+= copy.o
boot_sobjs	+= pmjump.o

boot_cobjs	+= tty.o
boot_cobjs	+= regs.o
boot_cobjs	+= string.o
boot_cobjs	+= main.o
boot_cobjs	+= early_serial_console.o
boot_cobjs	+= cpu.o
boot_cobjs	+= cpucheck.o
boot_cobjs	+= cpuflags.o
boot_cobjs	+= printf.o
boot_cobjs	+= memory.o
boot_cobjs	+= video.o
boot_cobjs	+= video-mode.o
boot_cobjs	+= video-vga.o
boot_cobjs	+= video-vesa.o
boot_cobjs	+= cmdline.o
boot_cobjs	+= pm.o
boot_cobjs	+= a20.o

targets		+= $(boot_cobjs) $(boot_sobjs)

BOOT_COMM_FLAGS		+= -nostdinc -D__KERNEL__ -DCONFIG_CC_STACKPROTECTOR -D_SETUP
BOOT_COMM_FLAGS		+= -DDISABLE_BRANCH_PROFILING -m32 -g -Os 
BOOT_COMM_FLAGS		+= -Wall -Wstrict-prototypes -march=i386 -mregparm=3
BOOT_COMM_FLAGS		+= -fno-strict-aliasing -fomit-frame-pointer -fno-pic
BOOT_COMM_FLAGS		+= -mno-mmx -mno-sse -ffreestanding -fno-stack-protector
BOOT_COMM_FLAGS		+= -mpreferred-stack-boundary=2
BOOT_COMM_FLAGS		+= -isystem $(shell $(CC)  -print-file-name=include)

BOOT_CFLAGS		+= $(BOOT_COMM_FLAGS)
BOOT_AFLAGS		+= $(BOOT_COMM_FLAGS) -D__ASSEMBLY__ $(SVGA_MODE)

.PHONY: all
all: $(targets)

.PHONY: clean
clean:
	rm -f $(targets)

setup.elf: $(boot_sobjs) $(boot_cobjs)
	$(LD) -m elf_x86_64 -z max-page-size=0x200000 -T ./setup.ld $(boot_sobjs) $(boot_cobjs) -o setup.elf
	
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.S
	$(CC) -I$(INCLUDE_PATH) -I. $(BOOT_AFLAGS) -c $< -o $@


%.o: %.c
	$(CC) -I$(INCLUDE_PATH) -I. $(BOOT_CFLAGS) -c $< -o $@
