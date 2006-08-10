| C prototype: void GraySprite8_MASK(short x,short y,short h,unsigned char *sprt0,unsigned char *sprt1,unsigned char *mask0,unsigned char *mask1,void *dest0,void *dest1) __attribute__((__stkparm__));

.text
.globl GraySprite8_MASK
.even

GraySprite8_MASK:
    movem.l  %a2-%a5,-(%sp)

    lea.l    4+16(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    addq.l   #2,%a1
    movea.l  (%a1)+,%a2
    movea.l  (%a1)+,%a3
    movea.l  (%a1)+,%a4
    movea.l  (%a1)+,%a5
    movea.l  (%a1)+,%a0
    movea.l  (%a1),%a1

    move.w   %d1,%d2	| d3 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d2,%d1	| d1 = 15*y

    move.w   %d0,%d2	| d3 = x
    lsr.w    #4,%d2	| d3 = x/16

    add.w    %d2,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8

    adda.w   %d1,%a0
    adda.w   %d1,%a1

    move.w   4+16+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq.l  #-1,%d0
    move.b   (%a4)+,%d0
    swap.w   %d0
    ror.l    %d1,%d0
    and.l    %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a0)

    moveq.l  #-1,%d0
    move.b   (%a5)+,%d0
    swap.w   %d0
    ror.l    %d1,%d0
    and.l    %d0,(%a1)

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b
0:
    movem.l  (%sp)+,%a2-%a5
    rts

2:
    lea      30(%a0),%a0
    lea      30(%a1),%a1
3:
    moveq.l  #-1,%d0
    move.b   (%a4)+,%d0
    rol.w    %d1,%d0
    and.w    %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)

    moveq.l  #-1,%d0
    move.b   (%a5)+,%d0
    rol.w    %d1,%d0
    and.w    %d0,(%a1)

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a1)

    dbf      %d2,2b

    movem.l  (%sp)+,%a2-%a5
    rts
