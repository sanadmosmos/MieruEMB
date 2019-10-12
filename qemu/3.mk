TARGET = tetris
TARGET_SYS = $(TARGET).sys
TARGET_IMG = $(TARGET).img

OBJS_BOOTPACK  = bootpack.o
OBJS_BOOTPACK += naskfunc.o
OBJS_BOOTPACK += main.o
OBJS_BOOTPACK += mylib.o
OBJS_BOOTPACK += func.o

TOOLPATH = ../../z_tools/
INCPATH  = ../../z_tools/haribote/

GCC		 = i686-w64-mingw32-gcc
MAKE     = make -f 3.mk
NASM     = nasm
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -quiet
#CC1		+= -Wall
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del

CFLAGS	= -nostdlib -Wall -fno-builtin -O3 -DHOST_CYGWIN

# デフォルト動作

default :
	$(MAKE) img

# ファイル生成規則

ipl10.bin : ipl10.nas Makefile
	$(NASM) -fbin -o ipl10.bin ipl10.nas

asmhead.bin : asmhead.nas Makefile
	$(NASM) -fbin -o asmhead.bin asmhead.nas

naskfunc.o : naskfunc.nas
	$(NASM) -fwin32 -o naskfunc.o naskfunc.nas

bootpack.bim : $(OBJS_BOOTPACK) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		$(OBJS_BOOTPACK)
# 3MB+64KB=3136KB

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

$(TARGET_SYS) : asmhead.bin bootpack.hrb Makefile
	cat asmhead.bin bootpack.hrb > $(TARGET_SYS)
#	copy /B asmhead.bin+bootpack.hrb $(TARGET_SYS)

$(TARGET_IMG) : ipl10.bin $(TARGET_SYS) Makefile
	$(EDIMG)   imgin:../../z_tools/fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:$(TARGET_SYS) to:@: \
		imgout:$(TARGET_IMG)

# 一般規則

%.o	: %.c
	$(GCC) -o $*.o $(CFLAGS) -c $*.c

# コマンド

img :
	$(MAKE) $(TARGET_IMG)

clean :
	-$(DEL) *.bin
	-$(DEL) *.o
	-$(DEL) *.gas
	-$(DEL) *.nas
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.hrb
	-$(DEL) $(TARGET_SYS)

src_only :
	$(MAKE) clean
	-$(DEL) $(TARGET_IMG)
