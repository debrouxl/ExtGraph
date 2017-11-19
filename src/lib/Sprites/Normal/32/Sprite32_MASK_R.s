| C prototype: void Sprite32_MASK_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned long *sprt asm("%a1"), const unsigned long *mask, void *dest asm("%a0")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl Sprite32_MASK_R
.even

Sprite32_MASK_R:
    subq.w   #1,%d2
    blt.s    0f

    move.l   %d3,-(%sp)
    move.w   %d4,-(%sp)
    move.l   %a2,-(%sp)

    move.l   4+10(%sp),%a2

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d3

    move.w   %d0,%d3
    lsr.w    #4,%d3		| %d2=x/16

    add.w    %d1,%d3		| %d2=x/16+y*PLANE_BYTE_WIDTH/2
    add.w    %d3,%d3		| %d2=x/8+y*PLANE_BYTE_WIDTH
    adda.w   %d3,%a0

    andi.w   #15,%d0		| %d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1		| %d1=lefshift

1:
    move.l   (%a2)+,%d3
    not.l    %d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    not.l    %d3
    not.w    %d4
    and.l    %d3,(%a0)+
    and.w    %d4,(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.w     %d4,(%a0)
    or.l     %d3,-(%a0)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b

    movea.l  (%sp)+,%a2
    move.w   (%sp)+,%d4
    move.l   (%sp)+,%d3
0:
    rts
