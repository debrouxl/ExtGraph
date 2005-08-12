| C prototype: void Sprite32_MASK(short x,short y,short h,unsigned long *sprt,unsigned long *mask,void *dest) __attribute__((__stkparm__));

.text
.globl Sprite32_MASK
.even

Sprite32_MASK:
    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)
    move.l   %a2,-(%sp)

|    move.w   4+8+4(%sp),%d3
|    beq.s    _end_Sprite32_OR

    lea.l    4+8(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    move.w   (%a0)+,%d3
    beq.s    0f
    movea.l  (%a0)+,%a1
    movea.l  (%a0)+,%a2
    movea.l  (%a0),%a0

    subq.w   #1,%d3

|    move.w   4+8+0(%sp),%d0
|    move.w   4+8+2(%sp),%d1
|    movea.l  4+8+6(%sp),%a1
|    movea.l  4+8+10(%sp),%a2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

|    movea.w  %d1,%a0
|    adda.l   4+8+14(%sp),%a0

    move.w   %d0,%d1
    and.w    #0xF,%d1

    moveq    #16,%d2
    sub.w    %d1,%d2

1:
    move.l   (%a2)+,%d0
    not.l    %d0
    move.w   %d0,%d4
    lsr.l    %d1,%d0
    not.l    %d0
    lsl.w    %d2,%d4
    not.w    %d4
    and.l    %d0,(%a0)+
    and.w    %d4,(%a0)

    move.l   (%a1)+,%d0
    move.w   %d0,%d4
    lsl.w    %d2,%d4
    lsr.l    %d1,%d0
    or.w     %d4,(%a0)
    or.l     %d0,-(%a0)

    lea      30(%a0),%a0
    dbf      %d3,1b

0:
    movea.l (%sp)+,%a2
    move.w  (%sp)+,%d4
    move.w  (%sp)+,%d3
    rts
