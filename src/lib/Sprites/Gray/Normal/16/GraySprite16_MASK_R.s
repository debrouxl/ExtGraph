| C prototype: void GraySprite16_MASK_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned short *sprt0, const unsigned short *sprt1, const unsigned short *mask0, const unsigned short *mask1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite16_MASK_R
.even

GraySprite16_MASK_R:
    subq.w   #1,%d2
    blt.s    0f

    movem.l  %d3/%a2-%a5,-(%sp)

    lea.l    4+20(%sp),%a5
    movea.l  (%a5)+,%a2
    movea.l  (%a5)+,%a3
    movea.l  (%a5)+,%a4
    movea.l  (%a5),%a5

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    move.w   %d0,%d3
    lsr.w    #4,%d3

    add.w    %d3,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

    and.w    #0xF,%d0
    moveq.l  #16,%d1
    sub.w    %d0,%d1

1:
    move.l   (%a0),%d3

    moveq.l  #-1,%d0
    move.w   (%a4)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,%d3

    moveq.l  #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,%d3
    move.l   %d3,(%a0)

    move.l   (%a1),%d3
    moveq.l  #-1,%d0
    move.w   (%a5)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,%d3

    moveq.l  #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,%d3
    move.l   %d3,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b

    movem.l  (%sp)+,%d3/%a2-%a5
0:
    rts
