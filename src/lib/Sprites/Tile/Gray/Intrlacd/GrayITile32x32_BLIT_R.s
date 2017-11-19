| C prototype: void GrayITile32x32_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprite, const unsigned long maskval asm("%d3"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayITile32x32_BLIT_R
.even
 
GrayITile32x32_BLIT_R:
    move.l   %a2,-(%sp)
 
    move.l   4+4(%sp),%a2
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(32/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)
    move.l   (%a2)+,%d0
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)

    move.l   (%a2)+,%d0
    and.l    %d3,PLANE_BYTE_WIDTH(%a0)
    or.l     %d0,PLANE_BYTE_WIDTH(%a0)
    move.l   (%a2)+,%d0
    and.l    %d3,PLANE_BYTE_WIDTH(%a1)
    or.l     %d0,PLANE_BYTE_WIDTH(%a1)
 
    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    rts
