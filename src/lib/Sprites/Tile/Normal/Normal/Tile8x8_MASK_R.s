| C prototype: void Tile8x8_MASK_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned char *sprite asm("%a1"), const unsigned char* mask, void *plane asm("%a0")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl Tile8x8_MASK_R
.even

Tile8x8_MASK_R:
    pea      (%a2)

    move.l   4+4(%sp),%a2

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    add.w    %d1,%d1
    add.w    %d0,%d1

    adda.w   %d1,%a0

    moveq.l  #(8/4)-1,%d2

0:
    move.b   (%a2)+,%d0
    move.b   (%a1)+,%d1
    and.b    %d1,(%a0)
    or.b     %d0,(%a0)

    move.b   (%a2)+,%d0
    move.b   (%a1)+,%d1
    and.b    %d1,PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,PLANE_BYTE_WIDTH(%a0)

    move.b   (%a2)+,%d0
    move.b   (%a1)+,%d1
    and.b    %d1,2*PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,2*PLANE_BYTE_WIDTH(%a0)

    move.b   (%a2)+,%d0
    move.b   (%a1)+,%d1
    and.b    %d1,3*PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,3*PLANE_BYTE_WIDTH(%a0)

    lea      4*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,0b

    move.l   (%sp)+,%a2
    rts
