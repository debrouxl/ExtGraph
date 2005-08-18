| C prototype: void GraySprite8_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt0,unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite8_TRANW_R
.even

GraySprite8_TRANW_R:
    dbf      %d2,0f
    rts

0:
    movem.l  %d3-%d4/%a2-%a3,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3

    move.w   %d1,%d3	| d3 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d3,%d1	| d1 = 15*y

    move.w   %d0,%d3	| d3 = x
    lsr.w    #4,%d3	| d3 = x/16

    add.w    %d3,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8
    adda.w   %d1,%a0	| a0 += offset
    adda.w   %d1,%a1

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0

    moveq    #0,%d3
    move.b   (%a3)+,%d3
    swap.w   %d3
    lsr.l    %d1,%d3

    move.l   %d3,%d4
    not.l    %d4
    and.l    (%a0),%d4
    or.l     %d0,%d4
    move.l   %d4,(%a0)

    not.l    %d0
    and.l    (%a1),%d0
    or.l     %d3,%d0
    move.l   %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b
    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts

2:
    lea      30(%a0),%a0
    lea      30(%a1),%a1
3:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0

    moveq    #0,%d3
    move.b   (%a3)+,%d3
    lsl.w    %d1,%d3

    move.w   %d3,%d4
    not.w    %d4
    and.w    (%a0),%d4
    or.w     %d0,%d4
    move.w   %d4,(%a0)

    not.w    %d0
    and.w    (%a1),%d0
    or.w     %d3,%d0
    move.w   %d0,(%a1)

    dbf      %d2,2b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts
