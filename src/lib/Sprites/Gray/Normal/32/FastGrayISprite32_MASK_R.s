| C prototype: void FastGrayISprite32_MASK_R(short x,short y,short h,long* sprite,long *mask,void* dest);
| Environ 65% plus rapide que GraySprite16_MASK d'extgraph 1.02

.text
.globl FastGrayISprite32_MASK_R

FastGrayISprite32_MASK_R:
    dbf      %d2,__suite__
    rts

__suite__:
    move.l   %d3,-(%a7)
    move.l   %d5,-(%a7)
    move.w   %d4,-(%a7)
    move.w   %d6,-(%a7)

    |addq.l   #4,%a0

    |y*15
    move.w    %d1,%d3
    lsl.w     #4,%d1
    sub.w     %d3,%d1

    |x/16
    move.w    %d0,%d3
    lsr.w     #4,%d3

    add.w     %d3,%d1
    add.w     %d1,%d1
    adda.w    %d1,%a0

    addq.l    #4,%a0

    andi.w   #15,%d0          | d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1          | d1=lefshift

    |Mask1
    moveq.l  #-1,%d5
    lsr.l    %d0,%d5
    not.l    %d5

    |Mask2
    move.w   #-1,%d6
    lsl.w    %d1,%d6
    not.w    %d6

    lsr.w    #1,%d2
    bcs.s    Bouboucle32

    lea.l    -30(%a0),%a0
    bra.s    Milieu

Bouboucle32:
    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d5,%d3
    or.w     %d6,%d4
    and.l     %d3,(%a0)+
    and.w     %d4,(%a0)

    and.l     %d3,6000-4(%a0)
    and.w     %d4,6000(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,-4(%a0)
    or.w     %d4,(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,6000-4(%a0)
    or.w     %d4,6000(%a0)

Milieu:
    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d5,%d3
    or.w     %d6,%d4
    and.l     %d3,26(%a0)
    and.w     %d4,30(%a0)

    and.l     %d3,6000+26(%a0)
    and.w     %d4,6000+30(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,26(%a0)
    or.w     %d4,30(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,6000+26(%a0)
    or.w     %d4,6000+30(%a0)

    lea.l    26+30(%a0),%a0

    dbf    %d2,Bouboucle32

    move.w   (%a7)+,%d6
    move.w   (%a7)+,%d4
    move.l   (%a7)+,%d5
    move.l   (%a7)+,%d3
    rts
