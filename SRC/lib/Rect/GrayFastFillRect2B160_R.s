| C prototype: void GrayFastFillRect2B160_R(void* lightplane asm("%a0"),unsigned char* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
.text
.globl GrayFastFillRect2B160_R
.even
GrayFastFillRect2B160_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    adda.w   %d2,%a1
    moveq    #-1,%d0
    bra.s    1f
0:
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    move.l   %d0,(%a0)
    move.l   %d0,(%a1)
    lea      14(%a0),%a0
    lea      14(%a1),%a1
1:
    dbf      %d1,0b
    rts
