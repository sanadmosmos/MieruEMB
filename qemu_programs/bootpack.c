#include "bootpack.h"
#include "../define.h"


/**********************************************************************
 * variables
 **********************************************************************/

char key_data[3] = { 1, 1, 1};
int count;

extern char *e_sw1;
extern char *e_sw2;
extern char *e_sw3;
extern char *e_vram;


/**********************************************************************
 * prototype declaration
 **********************************************************************/

/* graphic.c */
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

/* dsctbl.c */
void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);

/* int.c */
void init_pic(void);
void inthandler21(int *esp);

/* timer.c */
void init_pit(void);
void inthandler20(int *esp);


/**********************************************************************
 * main
 **********************************************************************/

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;

	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PICの初期化が終わったのでCPUの割り込み禁止を解除 */
	init_pit();
	io_out8(PIC0_IMR, 0xf8); /* PITとPIC1とキーボードを許可(11111000) */

	init_palette();

	e_sw1 = &key_data[0];
	e_sw2 = &key_data[1];
	e_sw3 = &key_data[2];
	e_vram = binfo->vram;

	MieruEmb_main();
}


/**********************************************************************
 * functions
 **********************************************************************/

/* graphic.c */
void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:黒 */
		0xff, 0x00, 0x00,	/*  1:明るい赤 */
		0x00, 0xff, 0x00,	/*  2:明るい緑 */
		0xff, 0xff, 0x00,	/*  3:明るい黄色 */
		0x00, 0x00, 0xff,	/*  4:明るい青 */
		0xff, 0x00, 0xff,	/*  5:明るい紫 */
		0x00, 0xff, 0xff,	/*  6:明るい水色 */
		0xff, 0xff, 0xff,	/*  7:白 */
		0xc6, 0xc6, 0xc6,	/*  8:明るい灰色 */
		0x84, 0x00, 0x00,	/*  9:暗い赤 */
		0x00, 0x84, 0x00,	/* 10:暗い緑 */
		0x84, 0x84, 0x00,	/* 11:暗い黄色 */
		0x00, 0x00, 0x84,	/* 12:暗い青 */
		0x84, 0x00, 0x84,	/* 13:暗い紫 */
		0x00, 0x84, 0x84,	/* 14:暗い水色 */
		0x84, 0x84, 0x84	/* 15:暗い灰色 */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char 命令は、データにしか使えないけどDB命令相当 */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();	/* 割り込み許可フラグの値を記録する */
	io_cli(); 					/* 許可フラグを0にして割り込み禁止にする */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* 割り込み許可フラグを元に戻す */
	return;
}


/* dsctbl.c */

void init_gdtidt(void)
{
	struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *) ADR_GDT;
	struct GATE_DESCRIPTOR    *idt = (struct GATE_DESCRIPTOR    *) ADR_IDT;
	int i;

	/* GDTの初期化 */
	for (i = 0; i <= LIMIT_GDT / 8; i++) {
		set_segmdesc(gdt + i, 0, 0, 0);
	}
	set_segmdesc(gdt + 1, 0xffffffff,   0x00000000, AR_DATA32_RW);
	set_segmdesc(gdt + 2, LIMIT_BOTPAK, ADR_BOTPAK, AR_CODE32_ER);
	load_gdtr(LIMIT_GDT, ADR_GDT);

	/* IDTの初期化 */
	for (i = 0; i <= LIMIT_IDT / 8; i++) {
		set_gatedesc(idt + i, 0, 0, 0);
	}
	load_idtr(LIMIT_IDT, ADR_IDT);

	/* IDTの設定 */
	set_gatedesc(idt + 0x20, (int) asm_inthandler20, 2 * 8, AR_INTGATE32);
	set_gatedesc(idt + 0x21, (int) asm_inthandler21, 2 * 8, AR_INTGATE32);

	return;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar)
{
	if (limit > 0xfffff) {
		ar |= 0x8000; /* G_bit = 1 */
		limit /= 0x1000;
	}
	sd->limit_low    = limit & 0xffff;
	sd->base_low     = base & 0xffff;
	sd->base_mid     = (base >> 16) & 0xff;
	sd->access_right = ar & 0xff;
	sd->limit_high   = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
	sd->base_high    = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar)
{
	gd->offset_low   = offset & 0xffff;
	gd->selector     = selector;
	gd->dw_count     = (ar >> 8) & 0xff;
	gd->access_right = ar & 0xff;
	gd->offset_high  = (offset >> 16) & 0xffff;
	return;
}


/* int.c */
void init_pic(void)
/* PICの初期化 */
{
	io_out8(PIC0_IMR,  0xff  ); /* 全ての割り込みを受け付けない */
	io_out8(PIC1_IMR,  0xff  ); /* 全ての割り込みを受け付けない */

	io_out8(PIC0_ICW1, 0x11  ); /* エッジトリガモード */
	io_out8(PIC0_ICW2, 0x20  ); /* IRQ0-7は、INT20-27で受ける */
	io_out8(PIC0_ICW3, 1 << 2); /* PIC1はIRQ2にて接続 */
	io_out8(PIC0_ICW4, 0x01  ); /* ノンバッファモード */

	io_out8(PIC1_ICW1, 0x11  ); /* エッジトリガモード */
	io_out8(PIC1_ICW2, 0x28  ); /* IRQ8-15は、INT28-2fで受ける */
	io_out8(PIC1_ICW3, 2     ); /* PIC1はIRQ2にて接続 */
	io_out8(PIC1_ICW4, 0x01  ); /* ノンバッファモード */

	io_out8(PIC0_IMR,  0xfb  ); /* 11111011 PIC1以外は全て禁止 */
	io_out8(PIC1_IMR,  0xff  ); /* 11111111 全ての割り込みを受け付けない */

	return;
}

void inthandler21(int *esp)
/* PS/2キーボードからの割り込み */
{
	unsigned char data;

	io_out8(PIC0_OCW2, 0x61);
	data = io_in8(PORT_KEYDAT);
	
	*e_sw1 = (data == KEY_Q) ? 0 : 1;
	*e_sw2 = (data == KEY_W) ? 0 : 1;
	*e_sw3 = (data == KEY_E) ? 0 : 1;
	return;
}


/* timer.c */
void init_pit(void)
{
	io_out8(PIT_CTRL, 0x34);
	io_out8(PIT_CNT0, 0x9c);
	io_out8(PIT_CNT0, 0x2e);
	count = 0;
	return;
}

void inthandler20(int *esp)
{
	io_out8(PIC0_OCW2, 0x60);	/* IRQ-00受付完了をPICに通知 */
	count++;
	return;
}

