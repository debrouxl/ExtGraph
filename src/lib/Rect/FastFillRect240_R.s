| C prototype: void FastFillRect240_R(void* plane asm("%a0"), short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
.text
.globl FastFillRect240_R
.even
FastFillRect240_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    moveq    #-1,%d0
    bra.s    1f
0:
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.l   %d0,(%a0)+
    move.w   %d0,(%a0)+
1:
    dbf      %d1,0b
    rts
