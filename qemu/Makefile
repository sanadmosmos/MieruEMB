TARGET = tetris
TARGET_BIN = $(TARGET).bin
TARGET_SYS = $(TARGET).sys
TARGET_IMG = $(TARGET).img

OBJS  = naskfunc.o
OBJS += bootpack.o
OBJS += mylib.o
OBJS += func.o
OBJS += main.o

GCC		 = gcc
LD		 = ld
MAKE     = make
NASM     = nasm
RM       = rm -rf

CFLAGS	 = -m32 -nostdlib -Wall -fno-builtin -O3 -DHOST_CYGWIN -fno-pie
LDFLAGS  = -Map bootpack.map -T bootpack.ld -m elf_i386 -static

# デフォルト動作

default :
	$(MAKE) img

# ファイル生成規則

ipl10.bin : ipl10.nas
	$(NASM) -fbin -o ipl10.bin ipl10.nas

asmhead.bin : asmhead.nas
	$(NASM) -fbin -o asmhead.bin asmhead.nas

naskfunc.o : naskfunc.nas
	$(NASM) -felf -o naskfunc.o naskfunc.nas

$(TARGET_BIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET_BIN) $(OBJS)

$(TARGET_SYS) : asmhead.bin $(TARGET_BIN)
	cat asmhead.bin $(TARGET_BIN) > $(TARGET_SYS)

$(TARGET_IMG) : ipl10.bin $(TARGET_SYS) Makefile
	mformat -f 1440 -C -B ipl10.bin -i $(TARGET_IMG) ::
	mcopy $(TARGET_SYS) -i $(TARGET_IMG) ::

# 一般規則

%.o	: %.c
	$(GCC) -o $*.o $(CFLAGS) -c $*.c

# コマンド

img :
	$(MAKE) $(TARGET_IMG)

clean :
	-$(RM) *.bin
	-$(RM) *.o
	-$(RM) *.gas
	-$(RM) bootpack.map
	-$(RM) bootpack.bin
	-$(RM) bootpack.hrb
	-$(RM) $(TARGET_SYS)

src_only :
	$(MAKE) clean
	-$(RM) $(TARGET_IMG)
