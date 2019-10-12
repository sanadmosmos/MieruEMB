BUILD_DIR = qemu
OBJS = $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/mylib.o
OBJS += $(BUILD_DIR)/func.o

TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
MAKEFONT = $(TOOLPATH)makefont.exe
COPY     = copy
DEL      = del

all :
	$(MAKE) img -f qemu.mk

$(BUILD_DIR)/%.o : %.c qemu.mk
	$(CC1) -o $(BUILD_DIR)/$*.gas $*.c
	$(GAS2NASK) $(BUILD_DIR)/$*.gas $(BUILD_DIR)/$*.nas
	$(NASK) $(BUILD_DIR)/$*.nas $(BUILD_DIR)/$*.o

img : $(OBJS)
	$(MAKE) -C qemu

clean:
	make -C qemu -f 2.mk clean

