| C prototype: void GrayITile16x16_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprite, const unsigned short maskval asm("%d3"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayITile16x16_BLIT_R
.even
 
GrayITile16x16_BLIT_R:
    move.l   %a2,-(%sp)
 
    move.l   4+4(%sp),%a2
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(16/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    and.w    %d3,(%a1)
    or.w     %d0,(%a1)
    swap     %d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)
 
    move.l   (%a2)+,%d0
    and.w    %d3,PLANE_BYTE_WIDTH(%a1)
    or.w     %d0,PLANE_BYTE_WIDTH(%a1)
    swap     %d0
    and.w    %d3,PLANE_BYTE_WIDTH(%a0)
    or.w     %d0,PLANE_BYTE_WIDTH(%a0)
 
    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    rts
