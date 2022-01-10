#include <c64/kernalio.h>
#include <c64/memmap.h>
#include <c64/vic.h>
#include <gfx/bitmap.h>
#include <string.h>
#include <stdio.h>
int i,j;
Bitmap	Screen, Brush;
char	Buffer[200];

#define ScreenMem	((char *)0xe000)
#define ColorMem	((char *)0xd000)

int main(void)
{
	// Install the IRQ trampoline
	mmap_trampoline();

	// Initialize the display bitmap and a brush
	bm_init(&Screen, ScreenMem, 40, 25);
	bm_alloc(&Brush, 2, 2);

	// Clear the color memory with ROM and IO disabled
	mmap_set(MMAP_RAM);
	memset(ScreenMem, 0, 8000);
	memset(ColorMem, 0x70, 1000);
	mmap_set(MMAP_NO_ROM);

	// Switch VIC to hires mode
	vic_setmode(VICM_HIRES, ColorMem, ScreenMem);

	// Draw the brush
	ClipRect	crb = {0, 0, 16, 16};
	bm_fill(&Brush, 0);
	bm_circle_fill(&Brush, &crb, 7, 7, 6, NineShadesOfGrey[8]);

	// Draw the main image
	ClipRect	crr = {0, 0, 320, 200};

        bm_quad_fill(&Screen, &crr,0,0, 0,200,  480,200, 480,0,NineShadesOfGrey[5]);

        for (i=0; i<8; i++){
           bm_quad_fill(&Screen, &crr,i*35, 30, (i*35)+15,60, (i*35)+30 , 30,(i*35)+15, 0,NineShadesOfGrey[8]);
           bm_quad_fill(&Screen, &crr,i*35, 90, (i*35)+15,120, (i*35)+30 , 90,(i*35)+15, 60 ,NineShadesOfGrey[8]);
           bm_quad_fill(&Screen, &crr,i*35, 150, (i*35)+15,180, (i*35)+30 , 150,(i*35)+15, 120,NineShadesOfGrey[8]);
         }

        for (i=0; i<4; i++){
            bm_quad_fill(&Screen, &crr,i*70, 30, (i*70)+15,60, (i*70)+30 , 30,(i*70)+15, 0,NineShadesOfGrey[0]);
            bm_quad_fill(&Screen, &crr,i*70+35, 90, (i*70+35)+15,120, (i*70+35)+30 , 90,(i*70+35)+15,60,NineShadesOfGrey[0]);
            bm_quad_fill(&Screen, &crr,i*70, 150, (i*70)+15,180, (i*70)+30 ,150,(i*70)+15,120,NineShadesOfGrey[0]);
          }

        for (i=0; i<3; i++) {
            bm_line(&Screen, &crr,0,i*60+30,280,i*60+30,255);
            bm_line(&Screen, &crr,0,i*60+29,280,i*60+29,255);
            bm_line(&Screen, &crr,0,i*60+32,280,i*60+32,0);
            bm_line(&Screen, &crr,0,i*60+31,280,i*60+31,0);
        }

        for (i=0;i<4;i++) {
            for(j=0;j<3;j++){
               bm_line(&Screen, &crr,i*70+15, j*60+29, i*70+45, j*60+29, 0);
               bm_line(&Screen, &crr,i*70+15, j*60+30, i*70+45, j*60+30, 0);
               bm_line(&Screen, &crr,i*70+15, j*60+31, i*70+45, j*60+31, 255);
               bm_line(&Screen, &crr,i*70+15, j*60+32, i*70+45, j*60+32, 255);
             }
        }
	mmap_set(MMAP_ROM);

        while(1){};
	return 0;
}
