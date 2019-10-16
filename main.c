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

int map[P_HEIGHT][P_WIDTH];
STATES state;
mino m;
flag f;

/**********************************************************************/
int main()
{
	int i, j;
	int tmp;

	state = INIT;
	
    while(1){
		switch (state) {
			case INIT:
				for (i = 0; i < P_HEIGHT; i++) {
					for (j = 0; j < P_WIDTH; j++) {
						map[i][j] = 0;
					}
				}
    			mylib_clear(0);
				put_grid();
				mino_clear(&m);
				state = NEW_BLOCK;
				break;

			case NEW_BLOCK:
				new_mino(&m);
				m.x = 4;
				m.y = 0;
				state = FALL;
				break;

			case FALL:
		        delete_mino(&m);
				if (f.fall > 20) {
					f.fall = 0;
					m.y++;
					if (f.set == 1) {
						f.set = 0;
						m.y--;
						state = SET;
						break;
					}
				}
				f.fall++;
				// if push rotate
				if (*e_sw2 == 0 && f.rotate == 0) {
					rotate_mino(&m);
					f.rotate = 1;
				}
				if (*e_sw2 == 1 && f.rotate != 0)
					f.rotate = 0;

				if (f.xl != 0 && f.xredge == 1)
					f.xl = 0;
				// if push left
				if (*e_sw1 == 0 && f.xredge == 0) {
					f.xledge = (f.xl == 0) ? 1 : 0;
					if ((f.xl % SENSITIVITY) == 0)
						m.x--;
					f.xl++;
				}
				if (*e_sw1 == 1 && f.xl != 0)
					f.xl = 0;
				// if push right
		        if (*e_sw3 == 0 && f.xledge == 0) {
					f.xredge = (f.xr == 0) ? 1 : 0;
					if ((f.xr % SENSITIVITY) == 0)
						m.x++;
					f.xr++;
				}
				if (*e_sw3 == 1 && f.xr != 0)
					f.xr = 0;
		
				f.set = judge_set(&map, &m);
		        put_mino(&m);
				break;

			case SET:
				for (i = 0; i < NUM_OF_BLOCK; i++) {
					map[m.y+m.data[i].y][m.x+m.data[i].x] = m.color;
				}
				put_map(&map);
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
