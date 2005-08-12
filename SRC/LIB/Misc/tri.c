/******************************************************************************
*
* project name:   ExtGraph
* file name:      tri.c
* initial date:   23/04/2002
* author:         thomas.nussbaumer@gmx.net
* description:    triangle filling function
*
* build it with: tigcc -O3 -fomit-frame-pointer tri.c
*
*
* Original version taken from David Coz (coz.hubert@infonie.fr)
* The now optimized version runs about 4 times faster.
*
*
*
* actual results (TIGCC 0.93 on VTI):
* ------------------------------------
*
* INT-1 ticks:  8025
* seconds:      ~20s  (~500 triangles/second)
*
*
* $Id$
*
******************************************************************************/

//#define OPTIMIZE_ROM_CALLS  //we gain speed if NOT used this!
#define NO_EXIT_SUPPORT
#define USE_TI89
#define USE_TI92P

#include <tigcclib.h>

#define ASM_SWAP(val) ({\
    register unsigned long tmp = val;\
    asm volatile ("swap %0" : "=d" (tmp) : "0" (tmp));\
    tmp;})

#define ASM_EXCHANGE(val1,val2) asm volatile ("exg %0,%1" : "=da" (val1),"=da" (val2) : "0" (val1),"1" (val2) : /*"memory",*/"cc")


#if 0
//
// DONT USE - CONTAINS BUG!
//
//-----------------------------------------------------------------------
// supposes %d0 = x1, %d1 = x2, %a0 = addr (trashes %d2)
//-----------------------------------------------------------------------
asm(".data
.even
.globl FillSpan
_fillspn: clr.l   %d2
          cmp.w   %d0,%d1        | if (x1>x2) exchange(x1,x2)
          bge.s   _skip1
          exg     %d0,%d1
_skip1:	  tst.w   %d0            | if (x1<0) x1=0
	  bge.s   _skip2
	  clr.w   %d0
          tst.w   %d1            | if (x2<0) x2=0
          bge.s   _skip2
          rts                    | return immediately: x1 & x2 are both lower than 0!
_skip2:   cmp.w   #239,%d1       | if (x2>239) x2=239
	  ble.s   _skip3
	  move.w  #239,%d1       | if (x1>239) x1=239
	  cmp.w   #239,%d0
	  ble.s  _skip3
	  rts                    | return immediately: x1 & x2 are both larger than 239!

_skip3:   |bra.s _skip3
          |-----------------------------------------------------------------
          | now %d0.w contains left x value and %d1.w contains right x value
          | both clipped to [0-239]
          |-----------------------------------------------------------------
          move.w %d0,%d2
	  lsr.w  #3,%d2
	  and.w  #30,%d2
	  add.w  %d2,%a0       | p = addr+((x1>>3)&0x1e)) [%a0]
	  move.w %d0,%d2
	  and.w  #15,%d2       | sx = x1 & 0xf [%d2]
	  sub.w  %d0,%d1
	  addq.w #1,%d1        | dx = x2-x1+1 [%d1]

          |--------------------------------------------------------------------
          | if (dx<16) ... very short line ...
          |--------------------------------------------------------------------
	  cmp.w  #15,%d1       | if (dx<16) {*p^=(ASM_SWAP(table2[dx])) >> sx;return;}
	  bgt.s  _dxgt16
          clr.l  %d0
          lsl.w  #1,%d1 | !!!!! FIX !!!!
          move.w (__table2,%pc,%d1),%d0
          lsr.w  #1,%d1 | !!!!! FIX !!!!
          swap   %d0
          lsr.l  %d1,%d0
          move.l (%a0),%d1
          eor.l  %d0,(%a0)    | replace this for OR instead of XOR!
	  rts
.even
__table2: .word     0,32768,49152,57344,61440,63488,64512,65024
          .word 65280,65408,65472,65504,65520,65528,65532,65534

_dxgt16:  tst.w  %d2           | if (sx) ...
	  beq.s  _loopwds
          lsl.w  #1,%d2 | !!!!! FIX !!!!
          move.w (__table1,%pc,%d2),%d0 | *p++ ^= table1[sx]
          lsr.w  #1,%d2 | !!!!! FIX !!!!
  	  eor.w  %d0,(%a0)+
 	  add.w  #-16,%d2
          sub.w  %d2,%d1       | dx -= 16 - sx;
_loopwds:
	  cmp.w  #15,%d1       | while (dx >= 16) {*p++ ^= 0xffff;dx-=16;}
	  bgt.s  _loop
	  bra.s  _last
_loop:
	  eor.w #-1,(%a0)+
	  add.w #-16,%d1
	  jbra  _loopwds
_last:
	  tst.w %d1        | if (dx) *p ^= table2[dx];
	  jbeq  _end
          lsl.w  #1,%d1 | !!!!! FIX !!!!
          move.w (__table2,%pc,%d1),%d0
          eor.w  %d0,(%a0)
_end:
	  rts
.even
__table1: .word 65535,32767,16383, 8191, 4095, 2047, 1023,  511
          .word   255,  127,   63,   31,   15,    7,    3,    1
");



#define FillSpan(x1,x2,a) \
({unsigned long t1=(x1),t2=(x2);void* p = (a);\
 asm volatile("move.l %0,%%d0;move.l %1,%%d1;move.l %2,%%a0;jbsr _fillspn" : \
    "=d" (t1),"=d" (t2), "=a" (p) : "0" (t1),"1" (t2), "2" (p) : "d0","d1","a0","d2","memory","cc");})



#else


#define DRAW_XOR
//=============================================================================
// fills a horizontal line from x1 to x2 starting at address addr
//=============================================================================
static inline void FillSpan(short x1,short x2,unsigned char* addr) {
    static const unsigned short table1[16] = {0xffff,0x7fff,0x3fff,0x1fff,
                                              0x0fff,0x07ff,0x03ff,0x01ff,
                                              0x00ff,0x007f,0x003f,0x001f,
                                              0x000f,0x0007,0x0003,0x0001};
    static const unsigned short table2[16] = {0x0000,0x8000,0xc000,0xe000,
                                              0xf000,0xf800,0xfc00,0xfe00,
                                              0xff00,0xff80,0xffc0,0xffe0,
                                              0xfff0,0xfff8,0xfffc,0xfffe};

    short           dx;
    short           sx;
    unsigned short* p;

    // make sure x1 is left of x2 ...
    if (x1>x2) {
        //printf_xy(0,0,"SWAP=%d/%d",x1,x2);
        ASM_EXCHANGE(x1,x2);
    }

    // clipping of x1 and x2 to range [0-239]
    if (x1<0) {
        if (x2<0) return;
        x1=0;
    }
    if (x2>239) {
        if (x1>239) return;
        x2=239;
    }

    p  = (unsigned short*)(addr+((x1>>3)&0x1e));
    dx = x2-x1+1;
    sx = x1 & 0x0f;

    //-------------------------------------------------------------------------
    // lines shorter than 16 pixels are written in one step
    //-------------------------------------------------------------------------
    if (dx<16) {
        unsigned long val = (ASM_SWAP(table2[dx])) >> sx;
        #if defined DRAW_XOR
        *(unsigned long*)p ^= val;
        #else
        *(unsigned long*)p |= val;
        #endif
        return;
    }

    //-------------------------------------------------------------------------
    // are there any pixels in front of the "word"-line?
    //-------------------------------------------------------------------------
    if (sx) {
        #if defined DRAW_XOR
        *p++ ^= table1[sx];
        #else
        *p++ |= table1[sx];
        #endif
        dx -= (16-sx);
    }


    //-------------------------------------------------------------------------
    // draw "dword"-line (full dword by dword)
    //-------------------------------------------------------------------------
    unsigned long* tmp=(unsigned long*)p;
    while (dx >= 32) {
        *p++ ^= 0xffffffffL;
        dx-=32;
    }

    //-------------------------------------------------------------------------
    // draw "word"-line (full word by word)
    //-------------------------------------------------------------------------
    while (dx >= 16) {
        #if defined DRAW_XOR
        *p++ ^= 0xffff;
        #else
        *p++ |= 0xffff;
        #endif
        dx-=16;
    }

    //-------------------------------------------------------------------------
    // are there any pixels left trailing the "word"-line?
    //-------------------------------------------------------------------------
    if (dx) {
        #if defined DRAW_XOR
        *p ^= table2[dx];
        #else
        *p |= table2[dx];
        #endif
    }
}

#endif

typedef struct {
   short x,y;
} POINT2D;

typedef union {
   POINT2D       s;
   unsigned long l;
} POINT;

//=============================================================================
// draws a filled triangle (x values are x<<=7 !!)
//=============================================================================
void DrawTriangle(short x1,short y1,short x2,short y2,short x3,short y3) {
    short m1,m2,m3,y,xa,xb,d1,d2;
    unsigned char* addr;

/*
    static const unsigned short nr[128] = {0,1,0,2,0,0,0,3,0,0,0,0,0,0,0,4,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7};
*/
    // check for a degenerated triangle
    // (y coordinates or x coordinates collapsed)
    if ((y1==y2 && y2==y3) || (x1==x2 && x2==x3)) return;

    // sort points by their y coordinate ...
    // point with highest y will be afterwards in (x1/y1),
    // point with lowest y will be in (x3/y3)
    if (y2>=y1) {
        ASM_EXCHANGE(x1,x2);
        ASM_EXCHANGE(y1,y2);
    }

    if (y3>=y1) {
        ASM_EXCHANGE(x1,x3);
        ASM_EXCHANGE(y1,y3);
    }

    if (y3>=y2) {
        ASM_EXCHANGE(x2,x3);
        ASM_EXCHANGE(y2,y3);
    }

    //calculate dx/dy for highest-to-middle point
    if ((y=y1-y2)) m3 = (x1-x2)/y;
    else           m3 = 999;

    //calculate dx/dy for highest-to-lowest point
    if ((y=y1-y3)) m1 = (x1-x3)/y;
    else           m1 = 999;

    //calculate dx/dy for middle-to-lowest point
    if ((y=y2-y3)) m2 = (x2-x3)/y;
    else           m2 = 999;

    // start point is the lowest one point (xcoordinates shifted up by 7 bits)
    xa=x3;

    // if highest-and-middle lowest point share their xcoordinate xb is the xcoord of middle point
    if (m2==999) xb=x2;
    else         xb=xa;

    if (x2<(x3+(y2-y3)*m1)) d1=1,d2=0;
    else                    d1=0,d2=1;

    // now draw the spans
    addr = LCD_MEM+(y3<<5)-(y3<<1);
    for (y=y3;y<y2;y++,xa+=m1,xb+=m2,addr+=30) FillSpan(d1+(xa>>7),d2+(xb>>7),addr);
    for (;y<y1;y++,xa+=m1,xb+=m3,addr+=30)     FillSpan(d1+(xa>>7),d2+(xb>>7),addr);
}

//-----------------------------------------------------------------------------
//
// END OF TRIANGLE FUNCTION - START OF BENCHMARK CODE
//
//-----------------------------------------------------------------------------
volatile unsigned short counter = 0;


//=============================================================================
// simple counter hooked on int1
//=============================================================================
DEFINE_INT_HANDLER (myint1handler) {
    counter++;
}

#define RANDOM_TRIANGLES 2500
#define NR_LOOPS         4

short* x = NULL;
short* y = NULL;


//=============================================================================
// allocate and initialize global points arrays with "random" values
//=============================================================================
static inline short InitArrays(void) {
    unsigned short i;
    x = y = NULL;
    if (!(x = (short*)malloc(RANDOM_TRIANGLES*3*sizeof(short)))) return 0;
    if (!(y = (short*)malloc(RANDOM_TRIANGLES*3*sizeof(short)))) return 0;

    srand(0x00000000UL); // always start on same seed
    for (i=0;i<RANDOM_TRIANGLES*3;i++) {
       x[i]=(random(150)+5)<<7;
       y[i]=random(90)+5;
    }
    return 1;
}


//=============================================================================
// free the allocate global points arrays
//=============================================================================
static inline void CleanupArrays(void) {
    if (x) free(x);
    if (y) free(y);
}


//=============================================================================
// run the triangle drawing benchmark
//
// RANDOM_TRIANGLES*NR_LOOPS triangles will be drawn
//=============================================================================
void Bench(void) {
    short i,j;

    for (j=0;j<NR_LOOPS;j++) {
        for (i=0;i<RANDOM_TRIANGLES*3;i+=3) DrawTriangle(x[0+i],y[0+i],x[1+i],y[1+i],x[2+i],y[2+i]);
        //for (i=RANDOM_TRIANGLES*3-3;i>=0;i-=3) DrawTriangle(x[0+i],y[0+i],x[1+i],y[1+i],x[2+i],y[2+i]);
    }
//DrawTriangle(0,0,159,0,80,99);
//__HALT;
}



//=============================================================================
// where all the fun starts ...
//=============================================================================
void _main(void) {
    INT_HANDLER oldint1 = GetIntVec(AUTO_INT_1);
    INT_HANDLER oldint5 = GetIntVec(AUTO_INT_5);
    char        buffer[100];
    LCD_BUFFER  screen;

    if (!InitArrays()) {
        CleanupArrays();
        ST_helpMsg("error: out of mem");
        return;
    }
    LCD_save(screen);
    memset(LCD_MEM,0,LCD_SIZE);

    counter = 0;
    SetIntVec(AUTO_INT_1,myint1handler);
    SetIntVec(AUTO_INT_5,DUMMY_HANDLER);

    Bench();

    sprintf(buffer,"int-1 ticks=%u",counter);
    SetIntVec(AUTO_INT_1,oldint1);
    SetIntVec(AUTO_INT_5,oldint5);
    CleanupArrays();
    LCD_restore(screen);
    ST_helpMsg(buffer);
}

//#############################################################################
// Revision History
//#############################################################################
//
// $Log$
//
//
