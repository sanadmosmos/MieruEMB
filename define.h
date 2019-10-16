#ifndef __DEFINE_H__
#define __DEFINE_H__

#ifdef QEMU
	#define LCD_WIDTH	320
	#define LCD_HEIGHT	200
	extern int count;
	extern void io_stihlt();
#else
	#define LCD_WIDTH	128
	#define LCD_HEIGHT	128
#endif


#define MAP_WIDTH  		10
#define MAP_HEIGHT 		12
#define NUM_OF_BLOCK 	4
#define SENSITIVITY 	2
#define BLOCK_SIZE		10

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

int main();
void mino_clear(mino *m);
void map_clear(int a[][MAP_WIDTH]);
void put_block(int x, int y, int color);
void put_mino(mino *m);
void delete_mino(mino *m);
void put_grid();
void put_map(int a[][MAP_WIDTH]);
int judge_set(int a[][MAP_WIDTH], mino *m);
void rotate_mino(mino *m);
void new_mino(mino *m);
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
