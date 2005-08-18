| C prototype: void Sprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned long *sprt asm("%a1"),unsigned long *mask asm("%a2"),void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl Sprite32_MASK_R
.even

Sprite32_MASK_R:
    dbf    %d2,1f
    rts

1:
    move.l   %d3,-(%sp)
    move.w   %d4,-(%sp)
    move.l   %a2,-(%sp)

    move.l   4+10(%sp),%a2

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1=y*15

    move.w   %d0,%d3
    lsr.w    #4,%d3		| %d2=x/16

    add.w    %d1,%d3		| %d2=x/16+y*15
    add.w    %d3,%d3		| %d2=x/8+y*30 (nb pair)
    adda.w   %d3,%a0

    andi.w   #15,%d0		| %d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1		| %d1=lefshift

0:
    move.l   (%a2)+,%d3
    not.l    %d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    not.l    %d3
    not.w    %d4
    and.l    %d3,(%a0)+
    and.w    %d4,(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.w     %d4,(%a0)
    or.l     %d3,-(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,0b

    movea.l  (%sp)+,%a2
    move.w   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
