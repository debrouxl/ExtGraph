| C prototype: void Tile16x16_MASK_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprite asm("%a1"), const unsigned short* mask, void *plane asm("%a0")) __attribute__((__stkparm__));
 
.include "common.s"

.text
.globl Tile16x16_MASK_R
.even

Tile16x16_MASK_R:
    pea      (%a2)

    move.l   4+4(%sp),%a2

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d0,%d1

    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #(16/4)-1,%d2

0:
    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1

    and.w    %d1,PLANE_BYTE_WIDTH(%a0)
    or.w     %d0,PLANE_BYTE_WIDTH(%a0)
    swap     %d0
    swap     %d1
    and.w    %d1,(%a0)
    or.w     %d0,(%a0)

    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1

    and.w    %d1,3*PLANE_BYTE_WIDTH(%a0)
    or.w     %d0,3*PLANE_BYTE_WIDTH(%a0)
    swap     %d0
    swap     %d1
    and.w    %d1,2*PLANE_BYTE_WIDTH(%a0)
    or.w     %d0,2*PLANE_BYTE_WIDTH(%a0)

    lea.l    4*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    move.l   (%sp)+,%a2
    rts
