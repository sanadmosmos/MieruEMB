#ifndef __BOOTPACK_H__
#define __BOOTPACK_H__

/* asmhead.nas */
struct BOOTINFO { /* 0x0ff0-0x0fff */
	char cyls; /* ブートセクタはどこまでディスクを読んだのか */
	char leds; /* ブート時のキーボードのLEDの状態 */
	char vmode; /* ビデオモード  何ビットカラーか */
	char reserve;
	short scrnx, scrny; /* 画面解像度 */
	char *vram;
};
#define ADR_BOOTINFO	0x00000ff0

/* naskfunc.nas */
extern void io_hlt(void);
extern void io_cli(void);
extern void io_sti(void);
extern void io_stihlt(void);
extern int io_in8(int port);
extern void io_out8(int port, int data);
extern int io_load_eflags(void);
extern void io_store_eflags(int eflags);
extern void load_gdtr(int limit, int addr);
extern void load_idtr(int limit, int addr);
extern void asm_inthandler20(void);
extern void asm_inthandler21(void);

/* graphic.c */
#define COL8_000000		0	// black
#define COL8_FF0000		1	// red
#define COL8_00FF00		2	// green
#define COL8_FFFF00		3	// yellow
#define COL8_0000FF		4	// blue
#define COL8_FF00FF		5	// purple
#define COL8_00FFFF		6	// light blue
#define COL8_FFFFFF		7	// white
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

/* dsctbl.c */
struct SEGMENT_DESCRIPTOR {
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};
struct GATE_DESCRIPTOR {
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
};
#define ADR_IDT			0x0026f800
#define LIMIT_IDT		0x000007ff
#define ADR_GDT			0x00270000
#define LIMIT_GDT		0x0000ffff
#define ADR_BOTPAK		0x00280000
#define LIMIT_BOTPAK	0x0007ffff
#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e

/* int.c */
#define PIC0_ICW1		0x0020
#define PIC0_OCW2		0x0020
#define PIC0_IMR		0x0021
#define PIC0_ICW2		0x0021
#define PIC0_ICW3		0x0021
#define PIC0_ICW4		0x0021
#define PIC1_ICW1		0x00a0
#define PIC1_OCW2		0x00a0
#define PIC1_IMR		0x00a1
#define PIC1_ICW2		0x00a1
#define PIC1_ICW3		0x00a1
#define PIC1_ICW4		0x00a1

#define PORT_KEYDAT		0x0060

#define KEY_Q_PRESS		0x10
#define KEY_Q_RELEASE	0x90
#define KEY_W_PRESS		0x11
#define KEY_W_RELEASE	0x91
#define KEY_E_PRESS		0x12
#define KEY_E_RELEASE	0x92
#define KEY_ON			0
#define	KEY_OFF			1

/* timer.c */
#define PIT_CTRL	0x0043
#define PIT_CNT0	0x0040

#endif
