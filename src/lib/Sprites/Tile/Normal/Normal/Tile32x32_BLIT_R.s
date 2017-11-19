| C prototype: void Tile32x32_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprite asm("%a1"), const unsigned long maskval asm("%d3"), void *plane asm("%a0"));

.include "common.s"

.text
.globl Tile32x32_BLIT_R
.even

Tile32x32_BLIT_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d0,%d1

    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #(32/4)-1,%d2

0:
    move.l   (%a1)+,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,PLANE_BYTE_WIDTH(%a0)
    or.l     %d0,PLANE_BYTE_WIDTH(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,2*PLANE_BYTE_WIDTH(%a0)
    or.l     %d0,2*PLANE_BYTE_WIDTH(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,3*PLANE_BYTE_WIDTH(%a0)
    or.l     %d0,3*PLANE_BYTE_WIDTH(%a0)

    lea.l    4*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    rts
