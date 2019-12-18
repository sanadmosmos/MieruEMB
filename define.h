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
#define SENSITIVITY 	4
#define BLOCK_SIZE		7
#define NEXT_WINDOW_SIZE (BLOCK_SIZE * 5)
#define DROP_SPEED		7

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
	int drop_speed;
} flag;

typedef union {
	unsigned char byte;
	struct {
		unsigned char t:1;
		unsigned char s:1;
		unsigned char z:1;
		unsigned char l:1;
		unsigned char j:1;
		unsigned char i:1;
		unsigned char o:1;
		unsigned char :1;
	};
} mino_selection;

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
void display_gameover();
void display_delete_lines(int delete_lines);
void judge_overlap(int a[][MAP_WIDTH], mino *m, flag *f);
int  judge_set(int a[][MAP_WIDTH], mino *m, flag *f);
void down_1line(int a[][MAP_WIDTH], int num);
//void rotate(int *x, int *y, float ox, float oy);
void rotate_mino(mino *m);
int map2seed();
void new_mino(mino *m, mino *m_next);
void mino_o(mino *m);
void mino_t(mino *m);
void mino_s(mino *m);
void mino_z(mino *m);
void mino_l(mino *m);
void mino_j(mino *m);
void mino_i(mino *m);

#define COLOR_4BIT

#if defined(COLOR_3BIT)
#define COLOR_BLACK			0b000
#define COLOR_RED			0b001
#define COLOR_GREEN			0b010
#define COLOR_YELLOW		0b011
#define COLOR_BLUE			0b100
#define COLOR_PURPLE 		0b101
#define COLOR_LIGHT_BLUE 	0b110
#define COLOR_WHITE			0b111
#elif defined(COLOR_4BIT)
#define COLOR_BLACK			0b0000
#define COLOR_RED			0b0001
#define COLOR_GREEN			0b1010
#define COLOR_YELLOW		0b1011
#define COLOR_BLUE			0b0100
#define COLOR_PURPLE 		0b0101
#define COLOR_LIGHT_BLUE 	0b1110
#define COLOR_WHITE			0b1111

#define COLOR_ORANGE		0b1001
#define COLOR_LIGHT_GREEN	0b1000
#define COLOR_ULTRAMARINE	0b1100
#define COLOR_PINK			0b1101
#endif

#define MINO_Z COLOR_RED
#define MINO_S COLOR_GREEN
#define MINO_O COLOR_YELLOW
#define MINO_J COLOR_BLUE
#define MINO_T COLOR_PURPLE
#define MINO_I COLOR_LIGHT_BLUE
#define MINO_L COLOR_ORANGE

#define OFFSET 10



/* mylib.c */
void mylib_putpic(int x, int y, int width, int height, const unsigned int data[][width]);
void mylib_putc(int x, int y, char c, int color);
void mylib_puts(int x, int y, char *p, int color);
void mylib_putnum(int x, int y, int num, int color);
void mylib_puthex(int x, int y, unsigned int hex, int color);
void mylib_put_rectangle(int x1, int x2, int y1, int y2, int color);
void mylib_msleep(unsigned int tm);
void mylib_clear(int color);

#endif
