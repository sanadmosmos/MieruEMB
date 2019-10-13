TARGET = tetris
TARGET_SYS = $(TARGET).sys
TARGET_IMG = $(TARGET).img

OBJS  = naskfunc.o
OBJS += bootpack.o
OBJS += mylib.o
OBJS += func.o
OBJS += main.o

TOOLPATH = ../../z_tools/
INCPATH  = ../../z_tools/haribote/

#ARCH	 = i686-w64-mingw32-
GCC		 = $(ARCH)gcc
LD		 = $(ARCH)ld
STRIP	 = $(ARCH)strip
MAKE     = make
NASM     = nasm
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
EDIMG    = $(TOOLPATH)edimg.exe
RM       = rm -rf

CFLAGS	 = -m32 -nostdlib -Wall -fno-builtin -O3 -DHOST_CYGWIN -fno-pie
LDFLAGS  = -Map bootpack.map -T bootpack.ld -m elf_i386 -static
#LDFLAGS += --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_
#LDFLAGS += -e HariMain--oformat binary

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

bootpack.bim : $(OBJS)
	$(LD) $(LDFLAGS) -o bootpack.bim $(OBJS)
#	$(STRIP) -O binary bootpack.bim
#	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map $(OBJS)
# 3MB+64KB=3136KB

bootpack.hrb : bootpack.bim
#	$(BIM2HRB) bootpack.bim bootpack.hrb 0

$(TARGET_SYS) : asmhead.bin bootpack.bim
	cat asmhead.bin bootpack.bim > $(TARGET_SYS)
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
