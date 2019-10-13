BUILD_DIR = qemu
OBJS = $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/mylib.o
OBJS += $(BUILD_DIR)/func.o

#ARCH	 = i686-w64-mingw32-
GCC		 = $(ARCH)gcc
MAKE     = make
NASM     = nasm

CFLAGS	= -m32 -nostdlib -Wall -fno-builtin -O3 -DHOST_CYGWIN -fno-pie

all :
	$(MAKE) img -f qemu.mk

$(BUILD_DIR)/%.o : %.c
	$(GCC) -o $(BUILD_DIR)/$*.o $(CFLAGS) -c $*.c

img : $(OBJS)
	$(MAKE) -C qemu

clean:
	make -C qemu clean

