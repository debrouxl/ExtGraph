| C prototype: void GrayFastInvertRect2B240_R(void* lightplane asm("%a0"),unsigned char* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
.text
.globl GrayFastInvertRect2B240_R
.even
GrayFastInvertRect2B240_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    adda.w   %d2,%a1
    bra.s    1f
0:
    moveq    #7-1,%d2
2:
    not.l    (%a0)+
    not.l    (%a1)+
    dbf      %d2,2b
    not.l    (%a1)+
    not.w    (%a1)+
1:
    dbf      %d1,0b
    rts
