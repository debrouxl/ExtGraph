| C prototype: void GrayIShadowPlanesX16_R(register short height asm("%d0"),register short wordwidth asm("%d1"), register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__regparm__(4)));
|
| Derived from Gray..._ISHADOW_R routines. This one has a hard-coded white
| mask (effect applied to all pixels), applied to both planes, whose height 
| is variable (0 < height <= 0xFFFF) and whose width is multiple of 16.

.text
.globl GrayIShadowPlanesX16_R
.even

GrayIShadowPlanesX16_R:
    subq.w   #1,%d0
    blt.s    2f
    subq.w   #1,%d1
    blt.s    2f

    movem.l  %d3-%d5,-(%sp)

    move.w   %d1,%d5

0:
    move.w   %d5,%d1
1:
    move.w   (%a0),%d2
    move.w   (%a1),%d3

    and.w    %d3,%d2

    move.w   %d3,(%a0)+
    move.w   %d2,(%a1)+

    dbf      %d1,1b
    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5

2:
    rts
