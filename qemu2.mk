BUILD_DIR = qemu
OBJS = $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/mylib.o
OBJS += $(BUILD_DIR)/func.o

GCC		= gcc
CFLAGS	= -nostdlib -Wall -fno-builtin -O3

.SUFFIXES: .o .c

all :
	make -r img -f qemu2.mk

$(BUILD_DIR)/%.o : %.c
	gcc -o $(BUILD_DIR)/$*.o $(CFLAGS) -c $*.c 

img : $(OBJS)
	make -C qemu -f 2.mk

clean:
	make -C qemu -f 2.mk clean

