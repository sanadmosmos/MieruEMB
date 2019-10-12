#include "define.h"
#include "cfont.h"

extern volatile char *e_vram;
extern volatile int  *e_time;
extern volatile char *e_gp1;
extern volatile char *e_gp2;
extern volatile char *e_sw1;
extern volatile char *e_sw2;
extern volatile char *e_sw3;
extern volatile char *e_gin;

#ifdef QEMU
extern int count;
#endif

/**********************************************************************/
void mylib_putpic(int x, int y, int width, int height,  
                  const unsigned int data[][width]){
    int i,j;

    for(i=0; i<height; i++)
        for(j=0; j<width; j++)
            e_vram[(x+j) + (y+i)*128] =  data[i][j];
}

/**********************************************************************/
void mylib_putc(int x, int y, char c, int color){
    int i, j;
    
    for(i=0; i<16; i++){
        for(j=0; j<8; j++){
            if(e_char[(int)(c-'A')][i][j]) 
                e_vram[(x+j)+(y+i)*128] = color;
        }
    }
}
/**********************************************************************/
void mylib_putnum(int x, int y, int num, int color){
    int i, j;
    
    for(i=0; i<16; i++){
        for(j=0; j<8; j++){
            if(e_number[num][i][j]) e_vram[(x+j)+(y+i)*128] = color;
        }
    }
}

/**********************************************************************/
void mylib_msleep(unsigned int tm){
#ifdef QEMU
    count = 0;
    while(count <= (tm / 10)) {
        io_stihlt();
    }
#else
    unsigned int end = (unsigned int) *e_time + tm;
    while (*e_time < end);
#endif
}

/**********************************************************************/
void mylib_clear(int color){
    int i;
    for(i=0; i<128*128; i++) e_vram[i] = color;
}

