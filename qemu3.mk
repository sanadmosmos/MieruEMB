BUILD_DIR = qemu
OBJS = $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/mylib.o
OBJS += $(BUILD_DIR)/func.o

TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/

GCC		 = i686-w64-mingw32-gcc
MAKE     = make
NASM     = nasm
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
MAKEFONT = $(TOOLPATH)makefont.exe
COPY     = copy
DEL      = del

CFLAGS	= -nostdlib -Wall -fno-builtin -O3 -DHOST_CYGWIN

all :
	$(MAKE) img -f qemu3.mk

$(BUILD_DIR)/%.o : %.c qemu.mk
	$(GCC) -o $(BUILD_DIR)/$*.o $(CFLAGS) -c $*.c

#	$(CC1) -o $(BUILD_DIR)/$*.gas $*.c
#	$(GAS2NASK) $(BUILD_DIR)/$*.gas $(BUILD_DIR)/$*.nas
#	$(NASM) -fwin32 -o $(BUILD_DIR)/$*.o $(BUILD_DIR)/$*.nas

img : $(OBJS)
	$(MAKE) -C qemu -f 3.mk

clean:
	make -C qemu -f 2.mk clean

