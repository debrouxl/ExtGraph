| C prototype: void Tile16x16_RPLC_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprite asm("%a1"), void *plane asm("%a0"));

.include "common.s"

.text
.globl Tile16x16_RPLC_R
.even

Tile16x16_RPLC_R:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #(16/8)-1,%d2

0:
    move.w   (%a1)+,(%a0)

    move.w   (%a1)+,PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,2*PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,3*PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,4*PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,5*PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,6*PLANE_BYTE_WIDTH(%a0)

    move.w   (%a1)+,7*PLANE_BYTE_WIDTH(%a0)

    lea.l    8*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    rts
