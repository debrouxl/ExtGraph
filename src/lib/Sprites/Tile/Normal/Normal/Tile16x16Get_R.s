| C prototype: void Tile16x16Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned short *dest asm("%a1"));

.include "common.s"

.text
.globl Tile16x16Get_R
.even

Tile16x16Get_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #(16/8)-1,%d2

0:
    move.w   (%a0),(%a1)+

    move.w   PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   2*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   3*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   4*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   5*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   6*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.w   7*PLANE_BYTE_WIDTH(%a0),(%a1)+

    lea      8*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    rts
