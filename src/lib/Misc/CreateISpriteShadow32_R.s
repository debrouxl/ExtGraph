| C prototype: void CreateISpriteShadow32_R(unsigned short height asm("%d0"), const unsigned long* src asm("%a0"), unsigned long* dest asm("%a1"));

.text
.globl CreateISpriteShadow32_R
.even

CreateISpriteShadow32_R:
    subq.w   #1,%d0
    blt.s    1f

    move.l   %d3,-(%sp)
    move.l   %d4,-(%sp)

0:
    move.l   (%a0)+,%d3
    move.l   (%a0)+,%d1
    move.l   (%a0)+,%d2

    move.l   %d1,%d4
    not.l    %d4
    or.l     %d2,%d4
    or.l     %d1,%d2
    
    move.l   %d3,(%a1)+
    |not.l    %d1
    and.l    %d3,%d2
    and.l    %d3,%d4
    
    move.l   %d4,(%a1)+
    move.l   %d2,(%a1)+

    dbf      %d0,0b

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3

1:
    rts
