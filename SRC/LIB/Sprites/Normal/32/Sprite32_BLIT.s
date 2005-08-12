| C prototype: void Sprite32_BLIT(short x,short y,short h,unsigned long *sprt,unsigned long maskval,void *dest) __attribute__((__stkparm__));

.text
.globl Sprite32_BLIT
.even

Sprite32_BLIT:
    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)
    move.l   %d5,-(%sp)
    move.w   %d6,-(%sp)

|    move.w   4+10+4(%sp),%d3
|    beq.s    _end_Sprite32_BLIT

    lea.l    4+10(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    move.w   (%a0)+,%d3
    beq.s    0f
    movea.l  (%a0)+,%a1
    move.l   (%a0)+,%d5
    movea.l  (%a0),%a0

    subq.w   #1,%d3

|    move.w   4+10+0(%sp),%d0
|    move.w   4+10+2(%sp),%d1
|    movea.l  4+10+6(%sp),%a1

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

|    movea.w  %d1,%a0
|    adda.l   4+10+14(%sp),%a0

    move.w   %d0,%d1
    and.w    #0xF,%d1

    moveq    #16,%d2
    sub.w    %d1,%d2

|    move.l   4+10+10(%sp),%d5
    not.l    %d5
    move.w   %d5,%d6
    lsr.l    %d1,%d5
    not.l    %d5
    lsl.w    %d2,%d6
    not.w    %d6

1:
    move.l   (%a1)+,%d0
    move.w   %d0,%d4
    lsr.l    %d1,%d0
    lsl.w    %d2,%d4
    and.l    %d5,(%a0)
    or.l     %d0,(%a0)+
    and.w    %d6,(%a0)
    or.w     %d4,(%a0)
    lea      26(%a0),%a0
    dbf      %d3,1b

0:
    move.w  (%sp)+,%d6
    move.l  (%sp)+,%d5
    move.w  (%sp)+,%d4
    move.w  (%sp)+,%d3
    rts
