| C prototype: void Sprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned long *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl Sprite32_RPLC_R
.even

Sprite32_RPLC_R:
    dbf    %d2,1f
    rts

1:
    move.l   %d3,-(%sp)
    move.w   %d4,-(%sp)
    move.l   %d5,-(%sp)
    move.w   %d6,-(%sp)

    move.w   %d1,%d5
    lsl.w    #4,%d1
    sub.w    %d5,%d1

    move.w   %d0,%d5
    lsr.w    #4,%d5

    add.w    %d5,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    move.w   %d0,%d1
    and.w    #0xF,%d1

    moveq.l  #16,%d5
    sub.w    %d1,%d5

    moveq    #-1,%d3
    lsr.w    %d1,%d3
    move.w   %d3,%d4
    not.l    %d3
    swap     %d3

0:
    move.l   (%a1)+,%d0
    move.w   %d0,%d6
    lsl.w    %d5,%d6
    lsr.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)+
    and.w    %d4,(%a0)
    or.w     %d6,(%a0)

    lea      26(%a0),%a0
    dbf      %d2,0b

    move.w  (%sp)+,%d6
    move.l  (%sp)+,%d5
    move.w  (%sp)+,%d4
    move.l  (%sp)+,%d3
    rts
