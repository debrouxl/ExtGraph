| C prototype: void CreateSpriteIShadow32_R(short height asm("%d0"),unsigned long* src0 asm("%a0"),unsigned long* src1 asm("%a1"),unsigned long* mask, unsigned long* dest0, unsigned long* dest1) __attribute__((__stkparm__));

.text
.globl CreateSpriteIShadow32_R
.even

CreateSpriteIShadow32_R:
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
    and.l    %d2,%d3
    not.l    %d1
    and.l    %d1,%d2
    
    move.l   (%a2)+,%d1
    not.l    %d1
    and.l    %d1,%d2
    and.l    %d1,%d3
    
    move.l   %d2,(%a3)+
    move.l   %d3,(%a4)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3/%a2-%a4

1:
    rts
