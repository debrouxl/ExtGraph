| C prototype: void CreateISpriteShadow32_R(unsigned short height asm("%d0"), const unsigned long* src asm("%a0"), unsigned long* dest asm("%a1"));

.text
.globl CreateISpriteShadow32_R
.even

CreateISpriteShadow32_R:
    subq.w   #1,%d0
    blt.s    1f

    move.w   %d3,-(%sp)

0:
    move.l   4(%a0),%d1
    move.l   8(%a0),%d2

    move.l   %d1,%d3
    not.l    %d3
    or.l     %d2,%d3
    or.l     %d1,%d2
    
    move.l   (%a0),%d1
    
    move.l   %d1,(%a1)+

    not.l    %d1
    and.l    %d1,%d2
    and.l    %d1,%d3
    
    move.l   %d3,(%a1)+
    move.l   %d2,(%a1)+

    lea      12(%a0),%a0

    dbf      %d0,0b

    move.l   (%sp)+,%d3

1:
    rts
