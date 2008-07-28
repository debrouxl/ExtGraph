| C prototype: void FastInvertRect160_R(void* plane asm("%a0"), short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
.text
.globl FastInvertRect160_R
.even
FastInvertRect160_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    bra.s    1f
0:
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)
    lea      14(%a0),%a0
1:
    dbf      %d1,0b
    rts
