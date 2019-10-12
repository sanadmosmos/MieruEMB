/***** Sample Program for MieruEMB System v1.1                    *****/
/**********************************************************************/

volatile char *e_vram = (char*)0x900000;
volatile char *e_sw1  = (char*)0x8001fc;
volatile char *e_sw2  = (char*)0x8001fd;
volatile char *e_sw3  = (char*)0x8001fe;
volatile int  *e_time = (int *)0x80010c;
volatile char *e_gp1  = (char*)0x8001f0;
volatile char *e_gp2  = (char*)0x8001f1;
volatile char *e_gin  = (char*)0x8001ff;

#include "cfont.h" // include character & number font
#include "define.h"

/**********************************************************************/

int map[12][10];
STATES state;
mino m;
flag f;

/**********************************************************************/
#ifdef QEMU
int MieruEmb_main()
#else
int main()
#endif
{
	int i, j;
	int tmp;

	state = INIT;
	
    while(1){
		switch (state) {
			case INIT:
				for (i = 0; i < 12; i++) {
					for (j = 0; j < 10; j++) {
						map[i][j] = 0;
					}
				}
    			mylib_clear(0);
				putgrid();
				mino_clear(&m);
				state = NEW_BLOCK;
				break;

			case NEW_BLOCK:
				mino_t(&m);
				m.x = 4;
				m.y = 0;
				state = FALL;
				break;

			case FALL:
				if (f.set == 1) {
					f.set = 0;
					state = SET;
					break;
				}
				f.set = judge_set(&map, &m);
		        putmino(&m);
				// if push rotate
				if (*e_sw2 == 0 && f.rotate == 0) {
					rotate_mino(&m);
					f.rotate = 1;
				}
				if (*e_sw2 == 1 && f.rotate != 0)
					f.rotate = 0;
				// if push left
				tmp = m.x + m.l; // most left
				if (*e_sw1 == 0 && tmp >= 1 && f.xl == 0) {
					m.x--;
					f.xl = 1;
				}
				if (*e_sw1 == 1 && f.xl != 0)
					f.xl = 0;
				// if push right
				tmp = m.x + m.r; // most right
		        if (*e_sw3 == 0 && tmp <= 8 && f.xr == 0) {
					m.x++;
					f.xr = 1;
				}
				if (*e_sw3 == 1 && f.xr != 0)
					f.xr = 0;
		
				if (f.fall > 50) {
					f.fall = 0;
					if (m.y > 9) {
					} else {
						m.y++;
					}
				}
				f.fall++;
				break;

			case SET:
				for (i = 0; i < M_HEIGHT; i++) {
					for (j = 0; j < M_WIDTH; j++) {
						if (m.data[i][j] == 1) {
							map[m.y+i][m.x+j] = m.color;
						}
					}
				}
				putmap(&map);
				state = NEW_BLOCK;
				break;

			case CLEAR_LINE:
				state = NEW_BLOCK;
				break;

			case END:
				state = INIT;
				break;

			default:
				break;
		}
        mylib_msleep(20);
    }
}
/**********************************************************************/
