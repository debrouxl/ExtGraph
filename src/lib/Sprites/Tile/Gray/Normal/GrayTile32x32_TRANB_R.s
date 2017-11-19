| C prototype: void GrayTile32x32_TRANB_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprt0, const unsigned long *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayTile32x32_TRANB_R
.even

GrayTile32x32_TRANB_R:
    movem.l  %d3/%a2-%a3,-(%sp)
 
    move.l   4+12(%sp),%a2
    move.l   4+12+4(%sp),%a3
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(32/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    move.l   (%a3)+,%d1

    move.l   %d1,%d3
    not.l    %d3
    or.l     (%a0),%d3
    and.l    %d0,%d3
    move.l   %d3,(%a0)

    not.l    %d0
    or.l     (%a1),%d0
    and.l    %d1,%d0
    move.l   %d0,(%a1)

    move.l   (%a2)+,%d0
    move.l   (%a3)+,%d1

    move.l   %d1,%d3
    not.l    %d3
    or.l     PLANE_BYTE_WIDTH(%a0),%d3
    and.l    %d0,%d3
    move.l   %d3,PLANE_BYTE_WIDTH(%a0)

    not.l    %d0
    or.l     PLANE_BYTE_WIDTH(%a1),%d0
    and.l    %d1,%d0
    move.l   %d0,PLANE_BYTE_WIDTH(%a1)

    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%d3/%a2-%a3
    rts
