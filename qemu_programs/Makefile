TARGET = tetris

SRCS  = stdfunc.s
SRCS += bootpack.c
SRCS += ../main.c
SRCS += ../mylib.c
SRCS += ../func.c

PREFIX	 = 
GCC		 = $(PREFIX)gcc
RM       = rm -f



all : $(TARGET).img

$(TARGET).img : ipl.bin $(TARGET).sys Makefile
	mformat -f 1440 -C -B ipl.bin -i $(TARGET).img ::
	mcopy $(TARGET).sys -i $(TARGET).img ::

ipl.bin : ipl.s
	$(GCC) -nostdlib -Wl,--oformat=binary -T ipl.ld -o $@ $^

$(TARGET).sys : asmhead.bin $(TARGET).bin
	cat asmhead.bin $(TARGET).bin > $(TARGET).sys

asmhead.bin : asmhead.s
	$(GCC) -nostdlib -Wl,--oformat=binary -T asmhead.ld -o $@ $^

$(TARGET).bin : $(SRCS)
	$(GCC) -march=i386 -m32 -nostdlib -fno-pie -Wl,--oformat=binary -T bootpack.ld -DQEMU -o $@ $^

clean :
	-$(RM) *.bin
	-$(RM) *.o
	-$(RM) $(TARGET_SYS)
	-$(RM) $(TARGET_IMG)

