#include "define.h"

extern volatile char *e_vram;
extern volatile int  *e_time;
extern volatile char *e_gp1;
extern volatile char *e_gp2;
extern volatile char *e_sw1;
extern volatile char *e_sw2;
extern volatile char *e_sw3;
extern volatile char *e_gin;

/**********************************************************************/
void mino_clear(mino *m)
{
	int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		m->data[i].x = 0;
		m->data[i].y = 0;
	}
}

/**********************************************************************/
void map_clear(int a[][10])
{
	int i, j;
	for (i = 0; i < 12; i++)
		for (j = 0; j < 10; j++)
			a[i][j] = 0;
}

/**********************************************************************/
void putblock(int x, int y, int color)
{
	int i, j;
	int tmpx, tmpy;
	tmpx = x*10 + OFFSET;
	tmpy = y*10;
	for (i = tmpx+1; i < tmpx+10; i++) {
		for (j = tmpy+1; j < tmpy+10; j++) {
			if (i >= LCD_WIDTH || i >= LCD_HEIGHT)
				continue;
			e_vram[j*LCD_WIDTH+i] = color;
		}
	}
}

/**********************************************************************/
void putmino(mino *m)
{
    int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		putblock(m->x + m->data[i].x, m->y + m->data[i].y, m->color);
	}
}

/**********************************************************************/
void deletemino(mino *m)
{
	int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		putblock(m->x + m->data[i].x, m->y + m->data[i].y, 0);
	}
}

/**********************************************************************/
void putgrid()
{
	int i, j;
	for (i = 0; i <= 120; i++) {
		for (j = 0; j <= 100; j++) {
			if (((i % 10) == 0) || ((j % 10) == 0))
				e_vram[OFFSET+i*LCD_WIDTH+j] = 7;
		}
	}
}

/**********************************************************************/
void putmap(int a[][10])
{
	int i, j;
	for (i = 0; i < P_HEIGHT; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			putblock(j, i, a[i][j]);
		}
	}
}

/**********************************************************************/
int judge_set(int a[][10], mino *m)
{
	int i, j;
	int bottom = 0;
	int tmp = 0;

	for (i = 0; i < NUM_OF_BLOCK; i++) {
		bottom = (m->data[i].y > bottom) ? m->data[i].y : bottom;
	}
	tmp = m->y + bottom;
	if (tmp >= 11) {
		return 1;
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			//if (m->data[][]
			//if (bottom < 
			//	bottom = 
		}
	}
	//if ()
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
		/*
			if (m->data[i][j] == 1 && m->data[i+1][j] == 0 && a[m->x+j+1][m->y+i] == 1) {
				return 1;
			}
			*/
		}
	}
	return 0;
}

/**********************************************************************/
void rotate_mino(mino *m)
{
	int i, j;
	int tmp;
	switch (m->color) {
		case MINO_O:
			break;
		case MINO_Z:
		case MINO_S:
		case MINO_J:
		case MINO_T:
		case MINO_L:
			break;
		case MINO_I:
			break;
		default:
			break;
	}
}

/**********************************************************************/
void mino_o(mino *m)
{
	m->color = MINO_O;
	m->data[0].x =  0;
	m->data[0].y =  0;
	m->data[1].x =  0;
	m->data[1].y =  1;
	m->data[2].x =  1;
	m->data[2].y =  1;
	m->data[3].x =  1;
	m->data[3].y =  0;
	/*
	m->l = 1;
	m->t = 1;
	m->r = 2;
	m->b = 2;
	*/
}

void mino_t(mino *m)
{
	m->color = MINO_T;
	m->data[0].x =  0;
	m->data[0].y =  0;
	m->data[1].x =  0;
	m->data[1].y = -1;
	m->data[2].x = -1;
	m->data[2].y =  0;
	m->data[3].x =  1;
	m->data[3].y =  0;
	/*
	m->l = 0;
	m->t = 1;
	m->r = 2;
	m->b = 2;
	*/
}

/*
void mino_z(unsigned int data[][P_WIDTH])
{
	int i, j;
	for (i = 0; i < P_WIDTH; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			if () {
			} else {
				data[i][j] = 7;
			}
		}
	}
}

void mino_s(unsigned int data[][P_WIDTH])
{
	int i, j;
	for (i = 0; i < P_WIDTH; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			if () {
			} else {
				data[i][j] = 7;
			}
		}
	}
}

void mino_l(unsigned int data[][P_WIDTH])
{
	int i, j;
	for (i = 0; i < P_WIDTH; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			if () {
			} else {
				data[i][j] = 7;
			}
		}
	}
}

void mino_j(unsigned int data[][P_WIDTH])
{
	int i, j;
	for (i = 0; i < P_WIDTH; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			if () {
			} else {
				data[i][j] = 7;
			}
		}
	}
}

void mino_i(unsigned int data[][P_WIDTH])
{
	int i, j;
	for (i = 0; i < P_WIDTH; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			if () {
			} else {
				data[i][j] = 7;
			}
		}
	}
}
*/
