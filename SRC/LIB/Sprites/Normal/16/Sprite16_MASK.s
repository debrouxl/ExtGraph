| C prototype: void Sprite16_MASK(short x,short y,short h,unsigned short *sprt,unsigned short *mask,void *dest) __attribute__((__stkparm__));

.text
.globl Sprite16_MASK
.even

Sprite16_MASK:
    move.l   %a2,-(%sp)

    lea.l    4+4(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    addq.l   #2,%a0
    movea.l  (%a0)+,%a1
    movea.l  (%a0)+,%a2
    movea.l  (%a0),%a0

|    move.w   4+4+0(%sp),%d0
|    move.w   4+4+2(%sp),%d1
|    movea.l  4+4+6(%sp),%a1
|    movea.l  4+4+10(%sp),%a2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

|    movea.w  %d1,%a0
|    adda.l   4+4+14(%sp),%a0

    move.w   4+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

1:
    moveq.l  #-1,%d0
    move.w   (%a2)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,(%a0)

    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)

    lea      30(%a0),%a0
    dbf      %d2,1b

0:
    movea.l  (%sp)+,%a2
    rts
