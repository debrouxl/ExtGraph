| C prototype: void Tile8x8Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned char *dest asm("%a1"));

.include "common.s"

.text
.globl Tile8x8Get_R
.even

Tile8x8Get_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d1,%d1
    add.w    %d0,%d1

    adda.w   %d1,%a0


    move.b   (%a0),(%a1)+

    move.b   PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   2*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   3*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   4*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   5*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   6*PLANE_BYTE_WIDTH(%a0),(%a1)+

    move.b   7*PLANE_BYTE_WIDTH(%a0),(%a1)+

    rts
