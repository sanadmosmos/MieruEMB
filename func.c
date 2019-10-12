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
	int i, j;
	for (i = 0; i < P_WIDTH; i++)
		for (j = 0; j < P_HEIGHT; j++)
			m->data[i][j] = 0;
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
    int i,j;
	
    for(i=0; i<M_HEIGHT-1; i++) {
        for(j=0; j<M_WIDTH-1; j++) {
			//if (m->data[i][j] == 1) {
				putblock(m->x+j, m->y+i, m->color * m->data[i][j]);
			//}
		}
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

	tmp = m->b + m->y;
	if (tmp >= 12) {
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
			if (m->data[i][j] == 1 && m->data[i+1][j] == 0 && a[m->x+j+1][m->y+i] == 1) {
				return 1;
			}
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
			tmp = m->data[1][0];
			m->data[1][0] = m->data[1][2];
			m->data[1][2] = m->data[3][2];
			m->data[3][2] = m->data[3][0];
			m->data[3][0] = tmp;
			tmp = m->data[1][1];
			m->data[1][1] = m->data[2][2];
			m->data[2][2] = m->data[3][1];
			m->data[3][1] = m->data[2][0];
			m->data[2][0] = tmp;
			break;
		case MINO_I:
			tmp = m->data[0][0];
			m->data[0][0] = m->data[0][3];
			m->data[0][3] = m->data[3][3];
			m->data[3][3] = m->data[3][0];
			m->data[3][0] = m->data[0][0];
			tmp = m->data[0][1];
			m->data[0][1] = m->data[1][3];
			m->data[1][3] = m->data[3][2];
			m->data[3][2] = m->data[2][0];
			m->data[2][0] = m->data[0][1];
			tmp = m->data[0][2];
			m->data[0][2] = m->data[2][3];
			m->data[2][3] = m->data[3][1];
			m->data[3][1] = m->data[1][0];
			m->data[1][0] = m->data[0][2];
			tmp = m->data[1][1];
			m->data[1][1] = m->data[1][2];
			m->data[1][2] = m->data[2][2];
			m->data[2][2] = m->data[2][1];
			m->data[2][1] = m->data[1][1];
			break;
		default:
			break;
	}
}

/**********************************************************************/
void mino_o(mino *m)
{
	m->color = MINO_O;
	m->data[1][1] = 1;
	m->data[1][2] = 1;
	m->data[2][1] = 1;
	m->data[2][2] = 1;
	m->l = 1;
	m->t = 1;
	m->r = 2;
	m->b = 2;
}

void mino_t(mino *m)
{
	m->color = MINO_T;
	m->data[0][1] = 1;
	m->data[1][0] = 1;
	m->data[1][1] = 1;
	m->data[1][2] = 1;
	m->l = 0;
	m->t = 1;
	m->r = 2;
	m->b = 2;
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
