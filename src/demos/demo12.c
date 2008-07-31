// The program is smaller without OPTIMIZE_ROM_CALLS !
#define OPTIMIZE_ROM_CALLS    // Use ROM Call Optimization
#define NO_EXIT_SUPPORT
#define MIN_AMS 100
#define NO_AMS_CHECK
#define NO_CALC_DETECT

#ifdef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define C89_92V200(x,y) (x)
#else
#undef USE_TI89
#undef USE_TI92P
#undef USE_V200
#define USE_TI92P
#define USE_V200
#define C89_92V200(x,y) (y)
#endif


#include <tigcclib.h>         // Include All Header Files
//#include "extgraph.h"
#include "../../lib/extgraph.h"

#define GRAY
#define FAST_AND_DIRTY


#define NR_ROWS 25
#define NR_COLS 32

unsigned char tabtiles[NR_ROWS][NR_COLS]={
{1,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,2,0,4,2,1,2,4,5,3,2,1,5},
{1,0,4,2,2,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,4,2,0,0,5,2,1,2,3,1,1,2,3,4,2,1,2,3,4,2,3,4,2,1,2,0,5,3,2,1,3},
{1,5,3,3,3,5,0,1,2,3,2,5,2,3,0,2,1,2,3,4,2,3,4,2,1,2,4,5,3,0,1,0},
{1,1,2,0,4,0,6,1,2,4,1,5,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,6,3,4,5,6,3,2,3,1,5,6,3,4,2,1,2,3,4,6,3,0,2,1,2,4,5,3,2,1,3},
{1,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,2,3,4,2,2,2,2,5,0,2,2,3},
{0,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,2,3,4,5,0,1,2,3,1,5,2,3,2,2,1,2,0,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,2,3,3,5,6,1,2,3,1,0,2,3,4,2,1,2,3,4,2,3,4,2,6,2,6,5,3,2,1,6},
{4,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,2,3,4,5,6,1,2,6,1,5,0,3,4,2,1,4,3,4,2,3,4,2,1,2,2,5,3,4,1,3},
{1,1,2,3,4,5,0,1,2,3,1,5,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,1,3,4,5,6,1,2,3,1,5,2,3,4,0,1,2,3,4,2,0,4,0,1,2,4,5,3,2,1,3},
{1,0,2,3,4,5,6,1,2,3,6,5,2,3,4,2,1,2,3,6,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,2,3,4,5,6,1,2,3,1,5,1,3,4,2,1,2,3,4,2,3,4,2,1,2,3,5,3,2,1,3},
{5,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,6,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,2,3,4,5,6,1,2,5,1,5,2,3,0,2,1,2,3,4,2,3,4,2,1,2,4,5,3,0,1,3},
{1,1,4,3,4,5,6,1,0,3,1,4,2,3,4,2,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,4},
{2,6,2,3,5,5,6,1,2,3,1,5,2,3,4,2,1,0,3,4,0,3,4,2,6,2,4,5,3,2,1,3},
{1,1,2,3,4,5,6,1,2,3,1,5,4,3,4,2,1,2,3,4,2,3,4,2,1,2,5,5,3,5,1,3},
{1,1,2,3,4,1,6,1,2,3,1,5,2,3,4,2,1,6,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{1,1,6,3,4,5,6,6,2,3,0,5,2,3,4,2,1,2,3,4,2,3,6,6,1,2,3,0,3,2,1,3},
{1,1,2,3,4,5,6,1,2,1,1,5,2,3,4,3,1,2,3,4,2,3,4,2,1,2,4,5,3,2,1,3},
{0,1,2,3,4,5,6,1,2,3,1,5,2,3,4,2,1,2,3,4,6,3,4,2,1,2,4,5,3,2,4,3}
};

short tabsprites0[7][16]={
{0b0000011111100000,
0b0001100000011000,
0b0010000000000100,
0b0100000000000010,
0b0100010000100010,
0b1000101001010001,
0b1000000000000001,
0b1000000000000001,
0b1000000110000001,
0b1001100000011001,
0b1001010000101001,
0b0100101111010010,
0b0100010000100010,
0b0010001111000100,
0b0001100000011000,
0b0000011111100000},

{0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000},

{0b1111100000011111,
0b1110000000000111,
0b1100000000000011,
0b1000000000000001,
0b1000000000000001,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b1000000000000001,
0b1000000000000001,
0b1100000000000011,
0b1110000000000111,
0b1111100000011111},

{0b0111100000011110,
0b1110000000000111,
0b1100000000000011,
0b1000000000000001,
0b1000000000000001,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b1000000000000001,
0b1000000000000001,
0b1100000000000011,
0b1110000000000111,
0b0111100000011110},

{0x0000,
0x1818,
0x3C3C,
0x7E7E,
0xFFFF,
0xE7E7,
0xC3C3,
0x8181,
0x0000,
0x1818,
0x3C3C,
0x7E7E,
0xFFFF,
0xE7E7,
0xC3C3,
0x8181},

{0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA},

{0xF0F0,
0xE1E1,
0xC3C3,
0x8787,
0x8787,
0xC3C3,
0xE1E1,
0xF0F0,
0xF0F0,
0xE1E1,
0xC3C3,
0x8787,
0x8787,
0xC3C3,
0xE1E1,
0xF0F0}
};

#ifdef GRAY
short tabsprites1[7][16]={
{0b1111100000011111,
0b1110000000000111,
0b1100000000000011,
0b1000000000000001,
0b1000000000000001,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b1000000000000001,
0b1000000000000001,
0b1100000000000011,
0b1110000000000111,
0b1111100000011111},

{0b0111100000011110,
0b1110000000000111,
0b1100000000000011,
0b1000000000000001,
0b1000000000000001,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b0000000000000000,
0b1000000000000001,
0b1000000000000001,
0b1100000000000011,
0b1110000000000111,
0b0111100000011110},

{0b0000011111100000,
0b0001100000011000,
0b0010000000000100,
0b0100000000000010,
0b0100010000100010,
0b1000101001010001,
0b1000000000000001,
0b1000000000000001,
0b1000000110000001,
0b1001100000011001,
0b1001010000101001,
0b0100101111010010,
0b0100010000100010,
0b0010001111000100,
0b0001100000011000,
0b0000011111100000},

{0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000},

{~0x0000,
~0x1818,
~0x3C3C,
~0x7E7E,
~0xFFFF,
~0xE7E7,
~0xC3C3,
~0x8181,
~0x0000,
~0x1818,
~0x3C3C,
~0x7E7E,
~0xFFFF,
~0xE7E7,
~0xC3C3,
~0x8181},

{0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555,
0xAAAA,
0x5555},

{~0xF0F0,
~0xE1E1,
~0xC3C3,
~0x8787,
~0x8787,
~0xC3C3,
~0xE1E1,
~0xF0F0,
~0xF0F0,
~0xE1E1,
~0xC3C3,
~0x8787,
~0x8787,
~0xC3C3,
~0xE1E1,
~0xF0F0}
};
#endif

volatile short count=0;
#ifndef FAST_AND_DIRTY
DEFINE_INT_HANDLER(CountFps)
{
	count++;
}
#else
// This is the dirty, but currently faster and smaller way to make a custom
// interrupt handler...
extern void *CountFps;
asm(".xdef CountFps
CountFps:
.long CountFpsBody

CountFpsBody:
addq.w #1,count
rte");
#endif

#ifdef FAST_AND_DIRTY
unsigned char fpssprite[20]={0};
#endif

#ifdef FAST_AND_DIRTY
extern void Sprite16_BLIT_R_very_special(register unsigned short mask asm("%d1"), register unsigned char* src asm("%a1")) __attribute__((__regparm__));
asm("
.text
.globl Sprite16_BLIT_R_very_special
.even

Sprite16_BLIT_R_very_special:
    moveq    #5-1,%d2
    movea.l  __D_plane(%pc),%a0

_loop_Sprite16_BLIT_R:
    move.w   (%a0),%d0
    and.w    %d1,%d0
    or.w     (%a1)+,%d0
    move.w   %d0,(%a0)
    lea      30(%a0),%a0

    move.w   (%a0),%d0
    and.w    %d1,%d0
    or.w     (%a1)+,%d0
    move.w   %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,_loop_Sprite16_BLIT_R

    rts
");
#endif


// Try (nearly) every trick to be as fast as possible.
void _main(void)
{

	INT_HANDLER ai1,ai5;
	short xscroll,yscroll;
	short xtile,ytile;
	short i,j;

	void *vscreen0;
#ifdef GRAY
	void *vscreen1;
#endif

	unsigned short fps;
	unsigned char fps_str[5]={};

	LCD_BUFFER backbuffer;

	LCD_save(backbuffer);
#ifdef GRAY
	vscreen0=malloc(LCD_SIZE*2);
#else
	vscreen0=malloc(LCD_SIZE);
#endif
	if(!vscreen0)
		return;
#ifdef GRAY
	vscreen1=vscreen0+LCD_SIZE;
#endif

	ai1=GetIntVec(AUTO_INT_1);
	ai5=GetIntVec(AUTO_INT_5);

	SetIntVec(AUTO_INT_1,DUMMY_HANDLER);
	SetIntVec(AUTO_INT_5,CountFps);

	xscroll=yscroll=xtile=ytile=0;

	count=fps=0;

      ClrScr();
#ifdef GRAY
	if(GrayOn())
	{
#endif
#ifdef FAST_AND_DIRTY
		PortSet(fpssprite,15,9);
#endif
		do
		{
#ifndef GRAY
			memset(vscreen0,0,LCD_SIZE);
			for(j=14;j>=-1;j--)
				for(i=7;i>=-1;i--)
					ClipSprite16_OR_R(16*j+xscroll,16*i+yscroll,16,tabsprites0[tabtiles[ytile+i][xtile+j]],vscreen0);
			FastCopyScreen_R(vscreen0,LCD_MEM);
#else
			GrayClearScreen2B_R(vscreen0,vscreen1);
			for(j=14;j>=-1;j--)
				for(i=7;i>=-1;i--)
					GrayClipSprite16_OR_R(16*j+xscroll,16*i+yscroll,16,tabsprites0[tabtiles[ytile+i][xtile+j]],tabsprites1[tabtiles[ytile+i][xtile+j]],vscreen0,vscreen1);


			FastCopyScreen_R(vscreen0,GrayGetPlane(LIGHT_PLANE));
			FastCopyScreen_R(vscreen1,GrayGetPlane(DARK_PLANE));
#endif
#ifdef FAST_AND_DIRTY
			Sprite16_BLIT_R_very_special(C89_92V200(0xF,0),fpssprite);
#else
			DrawStr(0,0,fps_str,A_REPLACE);
#endif

			BEGIN_KEYTEST
			if(_keytest_optimized(RR_RIGHT) && (xscroll || xtile<32-15))
			{
				xscroll--;
				if(xscroll<0)
				{
					xscroll=15;
					xtile++;
				}
			}
			if(_keytest_optimized(RR_LEFT) && (xtile || xscroll))
			{
				xscroll++;
				if(xscroll>15)
				{
					xscroll=0;
					xtile--;
				}
			}
			if(_keytest_optimized(RR_DOWN) && (yscroll || ytile<25-8))
			{
				yscroll--;
				if(yscroll<0)
				{
					yscroll=15;
					ytile++;
				}
			}
			if(_keytest_optimized(RR_UP) && (ytile || yscroll))
			{
				yscroll++;
				if(yscroll>15)
				{
					yscroll=0;
					ytile--;
				}
			}
			END_KEYTEST

			fps++;
			if(count>19)
			{
				CharNumber(fps,0,fps_str);
#ifdef FAST_AND_DIRTY
				*(unsigned long *)fpssprite=0;
				*((unsigned long *)fpssprite+1)=0;
				*((unsigned long *)fpssprite+2)=0;
				*((unsigned long *)fpssprite+3)=0;
				*((unsigned long *)fpssprite+4)=0;
				DrawStr(0,0,fps_str,A_NORMAL);
#endif
				count=fps=0;
			}

		} while(!_keytest(RR_ESC));
#ifdef FAST_AND_DIRTY
	        PortRestore();
#endif
#ifdef GRAY
	}
#endif

#ifdef GRAY
	GrayOff();
#endif

	SetIntVec(AUTO_INT_1,ai1);
	SetIntVec(AUTO_INT_5,ai5);

	free(vscreen0);
	LCD_restore(backbuffer);
	GKeyFlush();
	ST_helpMsg(EXTGRAPH_VERSION_PWDSTR);
}
