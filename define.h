#ifndef __DEFINE_H__
#define __DEFINE_H__

#ifdef QEMU
	#define LCD_WIDTH	320
	#define LCD_HEIGHT	200
	extern int timer_count;
	extern void io_stihlt();
#else
	#define LCD_WIDTH	128
	#define LCD_HEIGHT	128
#endif


#define MAP_WIDTH  		10
#define MAP_HEIGHT 		18
#define NUM_OF_BLOCK 	4
#define SENSITIVITY 	3
#define BLOCK_SIZE		7
#define NEXT_WINDOW_SIZE (BLOCK_SIZE * 5)
#define DROP_SPEED		15

typedef struct {
	int x, y;
} block;

typedef struct {
	block data[4];
	int color;
	int x, y;
} mino;

typedef struct {
	int xl, xr;
	int xledge, xredge;
	int xlrmode;
	int movl, movr, movdown, movrotate;
	int set;
	int fall;
	int rotate;
} flag;

typedef enum {
	INIT,
	NEW_BLOCK,
	FALL,
	SET,
	END,
	WAIT
} STATES;

int main();
void mino_clear(mino *m);
void map_clear(int a[][MAP_WIDTH]);
void lcd_clear(int color);
void put_block(int x, int y, int color);
void put_mino(mino *m);
void delete_mino(mino *m);
void put_next_mino(mino *m_next);
void delete_next_mino(mino *m_next);
void put_grid();
void put_next();
void put_map(int a[][MAP_WIDTH]);
void judge_overlap(int a[][MAP_WIDTH], mino *m, flag *f);
int  judge_set(int a[][MAP_WIDTH], mino *m, flag *f);
void down_1line(int a[][MAP_WIDTH], int num);
void rotate(int *x, int *y, float ox, float oy);
void rotate_mino(mino *m);
void new_mino(mino *m, mino *m_next);
void mino_o(mino *m);
void mino_t(mino *m);
void mino_s(mino *m);
void mino_z(mino *m);
void mino_l(mino *m);
void mino_j(mino *m);
void mino_i(mino *m);

#define MINO_Z 1 // red
#define MINO_S 2 // green
#define MINO_O 3 // yellow
#define MINO_J 4 // blue
#define MINO_T 5 // purple
#define MINO_I 6 // light blue
#define MINO_L 7 // white

#define OFFSET 10



/* mylib.c */
void mylib_putpic(int x, int y, int width, int height, const unsigned int data[][width]);
void mylib_putc(int x, int y, char c, int color);
void mylib_putnum(int x, int y, int num, int color);
void mylib_msleep(unsigned int tm);
void mylib_clear(int color);

#endif
