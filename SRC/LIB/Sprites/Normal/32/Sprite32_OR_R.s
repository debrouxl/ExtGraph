| C prototype: void Sprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned long *sprt asm("%a1"),void *dest asm("%a0"));

.text
.globl Sprite32_OR_R
.even

Sprite32_OR_R:
    dbf    %d2,0f
    rts

0:
    move.l   %d3,-(%sp)
    move.w   %d4,-(%sp)

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | %d1=y*15

    move.w   %d0,%d3
    lsr.w    #4,%d3           | %d3=x/16

    add.w    %d1,%d3          | %d3=x/16+y*15
    add.w    %d3,%d3          | %d3=x/8+y*30 (even)
    adda.w   %d3,%a0

    andi.w   #15,%d0          | %d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1          | %d1=lefshift

1:
    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,(%a0)+
    or.w     %d4,(%a0)

    lea.l    30-4(%a0),%a0
    dbf      %d2,1b

    move.w   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
