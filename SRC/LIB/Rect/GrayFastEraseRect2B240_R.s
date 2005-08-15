| C prototype: void GrayFastEraseRect2B240_R(register void* lightplane asm("%a0"),register unsigned char* darkplane asm("%a1"),register short starty asm("%d0"), register unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
.text
.globl GrayFastEraseRect2B240_R
.even
GrayFastEraseRect2B240_R:
    add.w    %d0,%d0
    move.w   %d0,%d2
    lsl.w    #4,%d2
    sub.w    %d0,%d2
    adda.w   %d2,%a0
    adda.w   %d2,%a1
    moveq    #0,%d0
0:
    moveq    #7-1,%d2
1:
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    dbf      %d2,1b
    move.w   %d0,(%a0)+
    move.w   %d0,(%a1)+
    dbf      %d1,0b
    rts