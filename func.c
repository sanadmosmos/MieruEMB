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
void map_clear(int a[][MAP_WIDTH])
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++)
		for (j = 0; j < MAP_WIDTH; j++)
			a[i][j] = 0;
}

/**********************************************************************/
void lcd_clear(int color)
{
	int i, j;
	for (i = 0; i < 128; i++)
		for (j = 0; j < 128; j++)
			e_vram[i*LCD_WIDTH+j] = color;
}

/**********************************************************************/
void put_block(int x, int y, int color)
{
	int i, j;
	int tmpx, tmpy;
	tmpx = x*BLOCK_SIZE + OFFSET;
	tmpy = y*BLOCK_SIZE;
	for (i = tmpx+1; i < tmpx+BLOCK_SIZE; i++) {
		for (j = tmpy+1; j < tmpy+BLOCK_SIZE; j++) {
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

void put_next_mino(mino *m_next)
{
    int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		put_block(12 + m_next->data[i].x, 2 + m_next->data[i].y, m_next->color);
	}
}

void delete_next_mino(mino *m_next)
{
	int i;
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		put_block(12 + m_next->data[i].x, 2 + m_next->data[i].y, 0);
	}
}

/**********************************************************************/
void put_grid()
{
	int i, j;
	for (i = 0; i <= MAP_HEIGHT * BLOCK_SIZE; i++) {
		for (j = 0; j <= MAP_WIDTH * BLOCK_SIZE; j++) {
			if (((i % BLOCK_SIZE) == 0) || ((j % BLOCK_SIZE) == 0))
				e_vram[OFFSET+i*LCD_WIDTH+j] = 7;
		}
	}
}

/**********************************************************************/
void put_next()
{
	int i, j;
	for (i = 0; i <= NEXT_WINDOW_SIZE; i++) {
		for (j = 0; j <= NEXT_WINDOW_SIZE; j++) {
			if ((i % NEXT_WINDOW_SIZE) == 0 || (j % NEXT_WINDOW_SIZE) == 0)
				e_vram[(OFFSET+MAP_WIDTH*BLOCK_SIZE+5)+i*LCD_WIDTH+j] = 7;
		}
	}
}

/**********************************************************************/
void put_map(int a[][MAP_WIDTH])
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			put_block(j, i, a[i][j]);
		}
	}
}

/**********************************************************************/
void display_gameover()
{
	mylib_put_rectangle(10, 81, 30, 60, COLOR_GREEN);
	mylib_puts(20, 40, "GAMEOVER", COLOR_PURPLE);
}

/**********************************************************************/
void display_delete_lines(int delete_lines)
{
	int i;
	int most;
	int tmp;
	mylib_puts(85, 61, "LINES", COLOR_WHITE);
	mylib_put_rectangle(84, 128, 77, 92, COLOR_RED);
	while(1) {
		most = 0;
		for (i = 0, tmp = delete_lines; tmp != 0; i++) {
			most = tmp;
			if (tmp < 10)
				break;
			tmp /= 10;
		}
		mylib_putnum(120 - i*8, 77, most, COLOR_WHITE);
		tmp = i;
		for (i = 0; i < tmp; i++) {
			most *= 10;
		}
		delete_lines -= most;
		if (i <= 0)
			break;
	}
}

/**********************************************************************/
void judge_overlap(int a[][MAP_WIDTH], mino *m, flag *f)
{
	int i;
	int left = 0, right = 0;
	int flg = 1;

	for (i = 0; i < NUM_OF_BLOCK; i++) {
		left = (m->data[i].x < left) ? m->data[i].x : left;
		right = (m->data[i].x > right) ? m->data[i].x : right;
	}
	while ((m->x + left) < 0)
		m->x++;
	while ((m->x + right) > 9)
		m->x--;
	
//	while (flg != 0) {
		flg = 1;
		for (i = 0; i < NUM_OF_BLOCK; i++) {
			if (a[m->y+m->data[i].y][m->x+m->data[i].x] != 0)
				flg++;
		}
		if (flg == 1)
			return;

		if (f->movl == 1) {
			m->x++;
		}
		if (f->movr == 1) {
			m->x--;
		}
		if (f->movrotate == 1) {
			m->y--;
			for (i = 0; i < 4; i++) {
				//f->
			}
		}
		if (f->movdown)
			return;
	//}
}

int judge_set(int a[][MAP_WIDTH], mino *m, flag *f)
{
	int i;
	int bottom = 0;

	// in map range
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		bottom = (m->data[i].y > bottom) ? m->data[i].y : bottom;
	}
	if ((m->y + bottom) >= MAP_HEIGHT) {
		return 1;
	}

	// block
	for (i = 0; i < NUM_OF_BLOCK; i++) {
		if (a[m->y+m->data[i].y][m->x+m->data[i].x] != 0) {
			return 1;
		}
	}
	return 0;
}

/**********************************************************************/
void down_1line(int a[][MAP_WIDTH], int num)
{
	int i, j;
	for (i = num; i > 0; i--) {
		for (j = 0; j < MAP_WIDTH; j++) {
			a[i][j] = a[i-1][j];
		}
	}
	for (j = 0; j < MAP_WIDTH; j++) {
		a[0][j] = 0;
	}
}

/**********************************************************************/
/*
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
}*/

void rotate_mino(mino *m)
{
	int i;
	int tmp;
	switch (m->color) {
		case MINO_O:
			break;
		case MINO_Z:
		case MINO_S:
		case MINO_J:
		case MINO_T:
		case MINO_L:
			for (i = 0; i < NUM_OF_BLOCK; i++) {
				//rotate(&(m->data[i].x), &(m->data[i].y), 0, 0);
				tmp = m->data[i].x;
				m->data[i].x = m->data[i].y;
				m->data[i].y = -1 * tmp;
			}
			break;
		case MINO_I:
			for (i = 0; i < NUM_OF_BLOCK; i++) {
				//rotate(&m->data[i].x, &m->data[i].y, (float)0.5, (float)0.5);
				m->data[i].x++;
				m->data[i].x = ~m->data[i].x & 0b11;
				m->data[i].x--;
				tmp = m->data[i].x;
				m->data[i].x = m->data[i].y;
				m->data[i].y = tmp;
			}
			break;
		default:
			break;
	}
}

/**********************************************************************/
void new_mino(mino *m, mino *m_next)
{
	static int count_mino = 0;
	int i;
	if (m_next->color == 0) {
	} else {
		for (i = 0; i < NUM_OF_BLOCK; i++) {
			m->data[i].x = m_next->data[i].x;
			m->data[i].y = m_next->data[i].y;
		}
		m->color = m_next->color;
		m->x = m_next->x;
		m->y = m_next->y;
	}
	switch (count_mino) {
		case 0:
			mino_o(m_next);
			break;
		case 1:
			mino_t(m_next);
			break;
		case 2:
			mino_l(m_next);
			break;
		case 3:
			mino_j(m_next);
			break;
		case 4:
			mino_z(m_next);
			break;
		case 5:
			mino_s(m_next);
			break;
		case 6:
			mino_i(m_next);
			break;
		default:
			break;
	}
	count_mino++;
	count_mino %= 7;
	m->x = 4;
	m->y = 1;
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

