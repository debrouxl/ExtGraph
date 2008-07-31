| C prototype: void CreateSpriteShadow16_R(unsigned short height asm("%d0"), const unsigned short* src0 asm("%a0"), const unsigned short* src1 asm("%a1"), const unsigned short* mask, unsigned short* dest0, unsigned short* dest1) __attribute__((__stkparm__));

.text
.globl CreateSpriteShadow16_R
.even

CreateSpriteShadow16_R:
    subq.w   #1,%d0
    blt.s    1f

    movem.l  %d3/%a2-%a4,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3
    move.l   4+16+8(%sp),%a4

0:
    move.w   (%a0)+,%d1
    move.w   (%a1)+,%d2

    move.w   %d1,%d3
    not.w    %d3
    or.w     %d2,%d3
    or.w     %d1,%d2
    
    move.w   (%a2)+,%d1
    |not.w    %d1
    and.w    %d1,%d2
    and.w    %d1,%d3
    
    move.w   %d3,(%a3)+
    move.w   %d2,(%a4)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3/%a2-%a4

1:
    rts
