| C prototype: void GrayTile16x16_TRANW_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprt0, const unsigned short *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayTile16x16_TRANW_R
.even

GrayTile16x16_TRANW_R:
    movem.l  %d3/%a2-%a3,-(%sp)
 
    move.l   4+12(%sp),%a2
    move.l   4+12+4(%sp),%a3
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(16/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    move.l   (%a3)+,%d1

    move.w   %d1,%d3
    not.w    %d3
    and.w    PLANE_BYTE_WIDTH(%a0),%d3
    or.w     %d0,%d3
    move.w   %d3,PLANE_BYTE_WIDTH(%a0)

    not.w    %d0
    and.w    PLANE_BYTE_WIDTH(%a1),%d0
    or.w     %d1,%d0
    move.w   %d0,PLANE_BYTE_WIDTH(%a1)

    swap     %d0
    swap     %d1

    move.w   %d1,%d3
    not.w    %d3
    and.w    (%a0),%d3
    or.w     %d0,%d3
    move.w   %d3,(%a0)

    not.w    %d0
    and.w    (%a1),%d0
    or.w     %d1,%d0
    move.w   %d0,(%a1)

    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%d3/%a2-%a3
    rts
