| C prototype: void GrayFastInvertRect2B160_R(register void* lightplane asm("%a0"),register unsigned char* darkplane asm("%a1"),register short starty asm("%d0"), register unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
.text
.globl GrayFastInvertRect2B160_R
.even
GrayFastInvertRect2B160_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    adda.w   %d2,%a1
    bra.s    1f
0:
    not.l    (%a0)+
    not.l    (%a1)+
    not.l    (%a0)+
    not.l    (%a1)+
    not.l    (%a0)+
    not.l    (%a1)+
    not.l    (%a0)+
    not.l    (%a1)+
    not.l    (%a0)
    not.l    (%a1)
    lea      14(%a0),%a0
    lea      14(%a1),%a1
1:
    dbf      %d1,0b
    rts
