| C prototype: void Tile8x8_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned char *sprite asm("%a1"), const unsigned char maskval asm("%d3"), void *plane asm("%a0"));

.include "common.s"

.text
.globl Tile8x8_BLIT_R
.even

Tile8x8_BLIT_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d1,%d1
    add.w    %d0,%d1
    adda.w   %d1,%a0

    moveq.l  #(8/4)-1,%d2

0:
    move.b   (%a1)+,%d0
    and.b    %d3,(%a0)
    or.b     %d0,(%a0)

    move.b   (%a1)+,%d0
    and.b    %d3,PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,PLANE_BYTE_WIDTH(%a0)

    move.b   (%a1)+,%d0
    and.b    %d3,2*PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,2*PLANE_BYTE_WIDTH(%a0)

    move.b   (%a1)+,%d0
    and.b    %d3,3*PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,3*PLANE_BYTE_WIDTH(%a0)

    lea.l    4*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    rts
