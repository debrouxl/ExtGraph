| C prototype: void GrayIShadowPlanes240_R(void *dest0 asm("%a0"), void *dest1 asm("%a1"), unsigned short height asm("%d0")) __attribute__((__regparm__(3)));
|
| Derived from Gray..._ISHADOW_R routines. This one has a hard-coded white
| mask (effect applied to all pixels), applied to both planes, whose height 
| is variable (0 < height <= 0xFFFF) and whose width is multiple of 32.

.text
.globl GrayIShadowPlanes240_R
.even

GrayIShadowPlanes240_R:
    subq.w   #1,%d0
    blt.s    2f

    movem.l  %d3-%d5,-(%sp)

    moveq    #7-1,%d1
    move.w   %d1,%d5

0:
    move.w   %d5,%d1
1:
    move.l   (%a0),%d2
    move.l   (%a1),%d3

    and.l    %d3,%d2

    move.l   %d3,(%a0)+
    move.l   %d2,(%a1)+

    dbf      %d1,1b

    move.w   (%a0),%d2
    move.w   (%a1),%d3

    and.w    %d3,%d2

    move.w   %d3,(%a0)+
    move.w   %d2,(%a1)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5

2:
    rts
