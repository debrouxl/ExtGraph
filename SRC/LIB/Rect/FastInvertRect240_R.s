| C prototype: void FastInvertRect240_R(register void* plane asm("%a0"),register short starty asm("%d0"), register unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
.text
.globl FastInvertRect240_R
.even
FastInvertRect240_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
0:
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.w    (%a0)+
    dbf      %d1,0b
    rts
