| C prototype: void CreateISpriteIShadow32_R(register short height asm("%d0"),register unsigned long* src asm("%a0"),register unsigned long* dest asm("%a1")) __attribute__((__stkparm__));

.text
.globl CreateISpriteIShadow32_R
.even

CreateISpriteIShadow32_R:
    subq.w   #1,%d0
    blt.s    1f

    move.l   %d3,-(%sp)
    move.l   %d4,-(%sp)

0:
    move.l   (%a0)+,%d3
    move.l   (%a0)+,%d1
    move.l   (%a0)+,%d2

    move.l   %d1,%d4
    and.l    %d2,%d4
    not.l    %d1
    and.l    %d1,%d2
    
    move.l   %d3,(%a1)+

    not.l    %d3
    and.l    %d3,%d2
    and.l    %d3,%d4
    
    move.l   %d2,(%a1)+
    move.l   %d4,(%a1)+
    
    dbf      %d0,0b

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3

1:
    rts
