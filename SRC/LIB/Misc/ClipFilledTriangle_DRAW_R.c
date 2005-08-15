// Modified a source done by Thomas:
// * fixed the ASM FillSpan and changed #if 0 to #if 1 to use it.
// * now using regparm calling convention and direct call to the
//   ASM FillSpan.
// * modified the main function to accept normal x coordinates
//   instead of x coordinates << 7.
// Original version taken from David Coz (coz.hubert@infonie.fr),
// the previous version was said to be more than 4 times faster.
// See demo19 for a bench.


#include <tigcclib.h>

#define ASM_SWAP(val) ({\
    register unsigned long tmp = val;\
    asm volatile ("swap %0" : "=d" (tmp) : "0" (tmp));\
    tmp;})

#define ASM_EXCHANGE(val1,val2) asm volatile ("exg %0,%1" : "=da" (val1),"=da" (val2) : "0" (val1),"1" (val2) : /*"memory",*/"cc")


#if 1
//-----------------------------------------------------------------------
// supposes %d0 = x1, %d1 = x2, %a0 = addr (trashes %d2)
//-----------------------------------------------------------------------
asm(".data
.even
.globl FillSpanOR
FillSpanOR:
_fillspn: cmp.w   %d0,%d1        | if (x1>x2) exchange(x1,x2)
          bge.s   _skip1
          exg     %d0,%d1
_skip1:	  tst.w   %d0            | if (x1<0) x1=0
	  bge.s   _skip2
	  clr.w   %d0
          tst.w   %d1            | if (x2<0) x2=0
          bge.s   _skip2
          rts                    | return immediately: x1 & x2 are both lower than 0!
_skip2:   move.w  #239,%d2
          cmp.w   %d2,%d1        | if (x2>239) x2=239
	  ble.s   _skip3
	  move.w  %d2,%d1        | if (x1>239) x1=239
	  cmp.w   %d2,%d0
	  ble.s  _skip3
	  rts                    | return immediately: x1 & x2 are both larger than 239!

_skip3:   |bra.s _skip3
          |-----------------------------------------------------------------
          | now %d0.w contains left x value and %d1.w contains right x value
          | both clipped to [0-239]
          |-----------------------------------------------------------------
          move.w %d0,%d2
	  lsr.w  #4,%d2
	  add.w  %d2,%d2
	  add.w  %d2,%a0       | p = addr+((x1>>3)&0x1e)) [%a0]
	  move.w %d0,%d2
	  andi.w #15,%d2       | sx = x1 & 0xf [%d2]
	  sub.w  %d0,%d1
	  addq.w #1,%d1        | dx = x2-x1+1 [%d1]

          |--------------------------------------------------------------------
          | if (dx<16) ... very short line ...
          |--------------------------------------------------------------------
	  cmp.w  #15,%d1       | if (dx<16) {*p^=(ASM_SWAP(table2[dx])) >> sx;return;}
	  bgt.s  _dxgt16
          moveq  #0,%d0
          move.w %d1,%d0
          add.w  %d0,%d0
          move.w (__table2,%pc,%d0.w),%d0
          swap   %d0
          lsr.l  %d2,%d0
          eor.l  %d0,(%a0)    | replace this for OR instead of XOR!
	  rts
.even
__table2: .word     0,32768,49152,57344,61440,63488,64512,65024
          .word 65280,65408,65472,65504,65520,65528,65532,65534

_dxgt16:  tst.w  %d2           | if (sx) ...
	  beq.s  _loopwds
          move.w %d2,%d0
          add.w  %d0,%d0
          move.w (__table1,%pc,%d0.w),%d0 | *p++ ^= table1[sx]
  	  eor.w  %d0,(%a0)+
 	  add.w  #-16,%d2
          add.w  %d2,%d1       | dx -= 16 - sx <=> dx += sx - 16;
_loopwds:
	  cmp.w  #15,%d1       | while (dx >= 16) {*p++ ^= 0xffff;dx-=16;}
          ble.s  _last
_loop:
	  not.w  (%a0)+
	  add.w #-16,%d1
	  jbra  _loopwds
_last:
	  tst.w %d1        | if (dx) *p ^= table2[dx];
	  jbeq  _end
          add.w  %d1,%d1
          move.w (__table2,%pc,%d1.w),%d0
          eor.w  %d0,(%a0)
_end:
	  rts
.even
__table1: .word 65535,32767,16383, 8191, 4095, 2047, 1023,  511
          .word   255,  127,   63,   31,   15,    7,    3,    1
");



extern void FillSpanOR(unsigned short x1 asm("%d0"), unsigned short x2 asm("%d1"), unsigned char * addr asm("%a0"));


#else


#define DRAW_XOR
//=============================================================================
// fills a horizontal line from x1 to x2 starting at address addr
//=============================================================================
static inline void FillSpanOR(short x1,short x2,unsigned char* addr) {
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
// draws a filled triangle
//=============================================================================
void ClipFilledTriangle_DRAW_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *plane asm("%a0")) {
    short m1,m2,m3,y,xa,xb;
//    short d1,d2;
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

    x1 <<= 7;
    x2 <<= 7;
    x3 <<= 7;

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

    addr = (unsigned char *)plane+((((y3)+(y3))<<4)-((y3)+(y3)));

    if (x2<(x3+(y2-y3)*m1)) {
//        d1=1,d2=0;

        // now draw the spans
        for (y=y3;y<y2;y++,xa+=m1,xb+=m2,(unsigned char *)addr+=30) {
            FillSpanOR(1+(xa>>7),0+(xb>>7),addr);
        }
        for (;y<y1;y++,xa+=m1,xb+=m3,(unsigned char *)addr+=30) {
            FillSpanOR(1+(xa>>7),0+(xb>>7),addr);
        }
    }
    else {
//        d1=0,d2=1;

        // now draw the spans
        for (y=y3;y<y2;y++,xa+=m1,xb+=m2,(unsigned char *)addr+=30) {
            FillSpanOR(0+(xa>>7),1+(xb>>7),addr);
        }
        for (;y<y1;y++,xa+=m1,xb+=m3,(unsigned char *)addr+=30) {
            FillSpanOR(0+(xa>>7),1+(xb>>7),addr);
        }
    }

/*
    if (x2<(x3+(y2-y3)*m1)) d1=1,d2=0;
    else                    d1=0,d2=1;

    // now draw the spans
    addr = LCD_MEM+(y3<<5)-(y3<<1);
    for (y=y3;y<y2;y++,xa+=m1,xb+=m2,addr+=30) FillSpan(d1+(xa>>7),d2+(xb>>7),addr);
    for (;y<y1;y++,xa+=m1,xb+=m3,addr+=30)     FillSpan(d1+(xa>>7),d2+(xb>>7),addr);
*/
}
