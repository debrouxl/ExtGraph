| C prototype: void CreateSpriteShadow32_R(unsigned short height asm("%d0"), const unsigned long* src0 asm("%a0"), const unsigned long* src1 asm("%a1"), const unsigned long* mask, unsigned long* dest0, unsigned long* dest1) __attribute__((__stkparm__));

.text
.globl CreateSpriteShadow32_R
.even

CreateSpriteShadow32_R:
    subq.w   #1,%d0
    blt.s    1f

    movem.l  %d3/%a2-%a4,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3
    move.l   4+16+8(%sp),%a4

0:
    move.l   (%a0)+,%d1
    move.l   (%a1)+,%d2

    move.l   %d1,%d3
    not.l    %d3
    or.l     %d2,%d3
    or.l     %d1,%d2
    
    move.l   (%a2)+,%d1
    not.l    %d1
    and.l    %d1,%d2
    and.l    %d1,%d3
    
    move.l   %d3,(%a3)+
    move.l   %d2,(%a4)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3/%a2-%a4

1:
    rts
