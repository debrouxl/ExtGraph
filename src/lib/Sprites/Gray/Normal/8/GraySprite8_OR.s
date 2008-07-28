| C prototype: void GraySprite8_OR(unsigned short x, unsigned short y, unsigned short h, const unsigned char* sprite1, const unsigned char* sprite2, void* dest1, void* dest2) __attribute__((__stkparm__));

.text
.globl GraySprite8_OR
.even

GraySprite8_OR:
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

    move.w   %d1,%d2	| d3 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d2,%d1	| d1 = 15*y

    move.w   %d0,%d2	| d3 = x
    lsr.w    #4,%d2	| d3 = x/16

    add.w    %d2,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8

    adda.w   %d1,%a0
    adda.w   %d1,%a1

    move.w   4+8+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

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
    or.l     %d0,(%a0)
    lea.l    30(%a0),%a0

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a1)
    lea.l    30(%a1),%a1

    dbf      %d2,1b
0:
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts

2:
    lea      30(%a0),%a0
    lea      30(%a1),%a1
3:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a1)

    dbf      %d2,2b

    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
