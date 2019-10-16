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
void put_block(int x, int y, int color)
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
void put_mino(mino *m)
{
    int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		put_block(m->x + m->data[i].x, m->y + m->data[i].y, m->color);
	}
}

void delete_mino(mino *m)
{
	int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		put_block(m->x + m->data[i].x, m->y + m->data[i].y, 0);
	}
}

/**********************************************************************/
void put_grid()
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
void put_map(int a[][10])
{
	int i, j;
	for (i = 0; i < P_HEIGHT; i++) {
		for (j = 0; j < P_WIDTH; j++) {
			put_block(j, i, a[i][j]);
		}
	}
}

/**********************************************************************/
int judge_set(int a[][10], mino *m)
{
	int i, j;
	int bottom = 0, left = 0, right = 0;
	int tmp = 0;

	for (i = 0; i < NUM_OF_BLOCK; i++) {
		bottom = (m->data[i].y > bottom) ? m->data[i].y : bottom;
		left = (m->data[i].x < left) ? m->data[i].x : left;
		right = (m->data[i].x > right) ? m->data[i].x : right;
	}
	while ((m->x + left) < 0)
		m->x += 1;
	while ((m->x + right) > 9)
		m->x -= 1;
	if ((m->y + bottom) >= (P_HEIGHT - 1)) {
		return 1;
	}


	return 0;
}

/**********************************************************************/
void rotate(int *x, int *y, float ox, float oy)
{
	float tmp_x, tmp_y;
	float tmp;

	tmp_x = (float)*x;
	tmp_y = (float)*y;

	tmp_x -= ox;
	tmp_y -= oy;

	tmp = tmp_x;
	tmp_x = tmp_y;
	tmp_y = -1 * tmp;
	
	tmp_x += ox;
	tmp_y += oy;

	*x = (int)tmp_x;
	*y = (int)tmp_y;
}

void rotate_mino(mino *m)
{
	int i;
	switch (m->color) {
		case MINO_O:
			break;
		case MINO_Z:
		case MINO_S:
		case MINO_J:
		case MINO_T:
		case MINO_L:
			for (i = 0; i < NUM_OF_BLOCK; i++) {
				rotate(&m->data[i].x, &m->data[i].y, 0, 0);
			}
			break;
		case MINO_I:
			for (i = 0; i < NUM_OF_BLOCK; i++) {
				rotate(&m->data[i].x, &m->data[i].y, 0.5, 0.5);
			}
			break;
		default:
			break;
	}
}

/**********************************************************************/
void new_mino(mino *m)
{
	static int count_mino = 0;
	switch (count_mino) {
		case 0:
			mino_o(m);
			break;
		case 1:
			mino_t(m);
			break;
		case 2:
			mino_l(m);
			break;
		case 3:
			mino_j(m);
			break;
		case 4:
			mino_z(m);
			break;
		case 5:
			mino_s(m);
			break;
		case 6:
			mino_i(m);
			break;
		default:
			break;
	}
	count_mino++;
	count_mino %= 7;
}

/**********************************************************************/
void mino_t(mino *m)
{
	m->color = MINO_T;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x =  0;	m->data[1].y = -1;
	m->data[2].x = -1;	m->data[2].y =  0;
	m->data[3].x =  1;	m->data[3].y =  0;
}

void mino_o(mino *m)
{
	m->color = MINO_O;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x =  0;	m->data[1].y =  1;
	m->data[2].x =  1;	m->data[2].y =  1;
	m->data[3].x =  1;	m->data[3].y =  0;
}

void mino_l(mino *m)
{
	m->color = MINO_L;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x = -1;	m->data[1].y =  0;
	m->data[2].x =  1;	m->data[2].y =  0;
	m->data[3].x =  1;	m->data[3].y = -1;
}

void mino_j(mino *m)
{
	m->color = MINO_J;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x = -1;	m->data[1].y =  0;
	m->data[2].x = -1;	m->data[2].y = -1;
	m->data[3].x =  1;	m->data[3].y =  0;
}

void mino_s(mino *m)
{
	m->color = MINO_S;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x = -1;	m->data[1].y =  0;
	m->data[2].x =  0;	m->data[2].y = -1;
	m->data[3].x =  1;	m->data[3].y = -1;
}

void mino_z(mino *m)
{
	m->color = MINO_Z;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x =  0;	m->data[1].y = -1;
	m->data[2].x = -1;	m->data[2].y = -1;
	m->data[3].x =  1;	m->data[3].y =  0;
}

void mino_i(mino *m)
{
	m->color = MINO_I;
	m->data[0].x =  0;	m->data[0].y =  0;
	m->data[1].x = -1;	m->data[1].y =  0;
	m->data[2].x =  1;	m->data[2].y =  0;
	m->data[3].x =  2;	m->data[3].y =  0;
}

