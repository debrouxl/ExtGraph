| C prototype: void Sprite32Get(unsigned short x, unsigned short y, unsigned short height, void* src, unsigned long* dest) __attribute__((__stkparm__));
|
| This routine is faster (about 30%) than the previous C routine, because the
| algorithm was changed.

.text
.globl Sprite32Get
.even

Sprite32Get:
    move.w   0+4+0(%sp),%d0
    move.w   0+4+2(%sp),%d1
    movea.l  0+4+10(%sp),%a1

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    movea.w  %d0,%a0
    adda.l   0+4+6(%sp),%a0

    andi.w   #0xF,%d2

    moveq    #16,%d1
    sub.w    %d2,%d1

    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)

    move.w   4+4+4(%sp),%d3
    beq.s    0f
    subq.w   #1,%d3
    
1:
    move.l   (%a0)+,%d0
    lsl.l    %d2,%d0
    move.w   (%a0),%d4
    lsr.w    %d1,%d4
    or.w     %d4,%d0
    move.l   %d0,(%a1)+
    lea      30-4(%a0),%a0
    dbf      %d3,1b

0:
    move.w  (%sp)+,%d4
    move.w  (%sp)+,%d3
    rts
