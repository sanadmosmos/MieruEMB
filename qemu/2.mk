TARGET = tetris
TARGET_SYS = $(TARGET).sys
TARGET_IMG = $(TARGET).img

OBJS  = bootpack.o
OBJS += naskfunc.o
OBJS += main.o
OBJS += mylib.o
OBJS += func.o

TOOLPATH = ../../z_tools/
INCPATH  = ../../z_tools/haribote/

MAKE     = make -f 2.mk
GCC      = gcc
NASM     = nasm
OBJ2BIM  = gcc
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
RM       = rm -f

CFLAGS	= -nostdlib -Wall -fno-builtin -O3

# デフォルト動作

default :
	$(MAKE) img

# ファイル生成規則

ipl10.bin : ipl10.nas
	$(NASM) -fbin -o ipl10.bin ipl10.nas

asmhead.bin : asmhead.nas
	$(NASM) -fbin -o asmhead.bin asmhead.nas

bootpack.bin : $(OBJS)
	ld -e _HariMain --Map bootpack.map -n -Ttext 0xc200 -static -o bootpack.bin $(OBJS)
	strip -O binary bootpack.bin

$(TARGET_SYS) : asmhead.bin bootpack.bin
	cat asmhead.bin bootpack.bin > $(TARGET_SYS)

$(TARGET_IMG) : ipl10.bin $(TARGET_SYS) Makefile
	$(EDIMG)   imgin:../../z_tools/fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:$(TARGET_SYS) to:@: \
		imgout:$(TARGET_IMG)

# 一般規則

%.o : %.c
	$(GCC) -o $*.o $(CFLAGS) -c $*.c

%.o : %.nas
	$(NASM) -fwin32 -o $*.o $*.nas

# コマンド

img :
	$(MAKE) $(TARGET_IMG)

clean :
	-$(RM) *.bin
	-$(RM) *.o
	-$(RM) *.gas
	-$(RM) bootpack.map
	-$(RM) bootpack.bim
	-$(RM) bootpack.hrb
	-$(RM) $(TARGET_SYS)

src_only :
	$(MAKE) clean
	-$(RM) $(TARGET_IMG)
