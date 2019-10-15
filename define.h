#ifndef __DEFINE_H__
#define __DEFINE_H__

#define QEMU
#ifdef QEMU
#include "qemu_programs/bootpack.h"
#endif

/* tetris.c */
#define LCD_WIDTH	320
#define LCD_HEIGHT	200
#define M_WIDTH  	4
#define M_HEIGHT 	4
#define P_WIDTH  	10
#define P_HEIGHT 	12
#define NUM_OF_BLOCK 4

typedef struct {
	int x, y;
} block;

typedef struct {
	block data[4];
	int color;
	int x, y;
	int l, t, r, b;
} mino;

typedef struct {
	int xl, xr;
	int set;
	int fall;
	int rotate;
} flag;

typedef enum {
	INIT,
	NEW_BLOCK,
	FALL,
	SET,
	CLEAR_LINE,
	END
} STATES;

#ifdef QEMU
int MieruEmb_main();
#endif
void mino_clear(mino *m);
void map_clear(int a[][10]);
void putblock(int x, int y, int color);
void putmino(mino *m);
void putgrid();
void putmap(int a[][10]);
int judge_set(int a[][10], mino *m);
void rotate_mino(mino *m);
void mino_o(mino *m);
void mino_t(mino *m);
void mino_s(mino *m);
void mino_z(mino *m);
void mino_l(mino *m);
void mino_j(mino *m);
void mino_i(mino *m);

#define MINO_Z 1
#define MINO_S 2
#define MINO_O 3
#define MINO_J 4
#define MINO_T 5
#define MINO_I 6
#define MINO_L 7

#define OFFSET 10



/* mylib.c */
void mylib_putpic(int x, int y, int width, int height, const unsigned int data[][width]);
void mylib_putc(int x, int y, char c, int color);
void mylib_putnum(int x, int y, int num, int color);
void mylib_msleep(unsigned int tm);
void mylib_clear(int color);

#endif
