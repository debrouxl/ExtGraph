| C prototype: void Sprite32_OR(short x,short y,short h,unsigned long* sprite,void* dest);
|
| This routine is faster (about 30%) than the previous C routine, because the
| algorithm was changed.

.text
.globl Sprite32_OR
.even

Sprite32_OR:
    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)

    lea.l    4+4(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    move.w   (%a0)+,%d3
    beq.s    0f
    movea.l  (%a0)+,%a1
    movea.l  (%a0),%a0

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0

    andi.w   #0xF,%d2

    moveq    #16,%d1
    sub.w    %d2,%d1

    subq.w   #1,%d3

1:
    move.l   (%a1)+,%d0
    move.w   %d0,%d4
    lsr.l    %d2,%d0
    lsl.w    %d1,%d4
    or.l     %d0,(%a0)+
    or.w     %d4,(%a0)
    lea      30-4(%a0),%a0
    dbf      %d3,1b

0:
    move.w   (%sp)+,%d4
    move.w   (%sp)+,%d3
    rts
