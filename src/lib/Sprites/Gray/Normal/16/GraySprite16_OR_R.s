| C prototype: void GraySprite16_OR_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned short *sprt0, const unsigned short *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite16_OR_R
.even

GraySprite16_OR_R:
    subq.w   #1,%d2
    blt.s    0f

    move.w   %d3,-(%sp)
    move.l   %a2,-(%sp)
    move.l   %a3,-(%sp)

    move.l   4+10(%sp),%a2
    move.l   4+10+4(%sp),%a3

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
    moveq    #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)
    lea.l    30(%a0),%a0

    moveq    #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a1)
    lea.l    30(%a1),%a1

    dbf      %d2,1b

    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
0:
    rts
