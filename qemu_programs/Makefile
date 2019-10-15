TARGET = tetris
TARGET_BIN = $(TARGET).bin
TARGET_SYS = $(TARGET).sys
TARGET_IMG = $(TARGET).img

SRCS  = stdfunc.s
SRCS += bootpack.c
SRCS += ../mylib.c
SRCS += ../func.c
SRCS += ../main.c

PREFIX	 = 
GCC		 = $(PREFIX)gcc
RM       = rm -f



all : $(TARGET_IMG)

$(TARGET_IMG) : ipl.bin $(TARGET_SYS) Makefile
	mformat -f 1440 -C -B ipl.bin -i $(TARGET_IMG) ::
	mcopy $(TARGET_SYS) -i $(TARGET_IMG) ::

ipl.bin : ipl.s
	$(GCC) -nostdlib -Wl,--oformat=binary -T ipl.ld -o $@ $^

$(TARGET_SYS) : asmhead.bin $(TARGET_BIN)
	cat asmhead.bin $(TARGET_BIN) > $(TARGET_SYS)

asmhead.bin : asmhead.s
	$(GCC) -nostdlib -Wl,--oformat=binary -T asmhead.ld -o $@ $^

$(TARGET_BIN) : $(SRCS)
	$(GCC) -march=i386 -m32 -nostdlib -fno-pie -Wl,--oformat=binary -T bootpack.ld -o $@ $^

clean :
	-$(RM) *.bin
	-$(RM) *.o
	-$(RM) $(TARGET_SYS)
	-$(RM) $(TARGET_IMG)

