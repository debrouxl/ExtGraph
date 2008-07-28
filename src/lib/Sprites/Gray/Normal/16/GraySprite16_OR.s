| C prototype: void GraySprite16_OR(unsigned short x, unsigned short y, unsigned short h, const unsigned short* sprite1, const unsigned short* sprite2, void* dest1, void* dest2) __attribute__((__stkparm__));

.text
.globl GraySprite16_OR
.even

GraySprite16_OR:
    move.l   %a2,-(%sp)
    move.l   %a3,-(%sp)

    lea.l    4+8(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    addq.l   #2,%a1
    movea.l  (%a1)+,%a2
    movea.l  (%a1)+,%a3
    movea.l  (%a1)+,%a0
    movea.l  (%a1),%a1

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0
    adda.w   %d1,%a1

    move.w   4+8+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    and.w    #15,%d0
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

0:
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
