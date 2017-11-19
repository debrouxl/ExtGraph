| C prototype: void Tile32x32Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned long *dest asm("%a1"));

.include "common.s"

.text
.globl Tile32x32Get_R
.even

Tile32x32Get_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d0,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

    moveq.l  #(32/8)-1,%d2

0:
    move.l   (%a0),(%a1)+

    move.l   PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   2*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   3*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   4*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   5*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   6*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.l   7*PLANE_BYTE_WIDTH(%a0),(%a1)+

    lea      8*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    rts
