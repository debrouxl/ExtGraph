| C prototype: void CreateISpriteShadow16_R(unsigned short height asm("%d0"), const unsigned short* src asm("%a0"), unsigned short* dest asm("%a1"));

.text
.globl CreateISpriteShadow16_R
.even

CreateISpriteShadow16_R:
    subq.w   #1,%d0
    blt.s    1f

    move.w   %d3,-(%sp)

0:
    move.w   2(%a0),%d1
    move.w   4(%a0),%d2

    move.w   %d1,%d3
    not.w    %d3
    or.w     %d2,%d3
    or.w     %d1,%d2
    
    move.w   (%a0),%d1
    
    move.w   %d1,(%a1)+

    not.w    %d1
    and.w    %d1,%d2
    and.w    %d1,%d3
    
    move.w   %d3,(%a1)+
    move.w   %d2,(%a1)+

    addq.l   #6,%a0

    dbf      %d0,0b

    move.w   (%sp)+,%d3

1:
    rts
