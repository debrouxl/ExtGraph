| C prototype: void CreateISpriteShadow8_R(unsigned short height asm("%d0"), const unsigned char* src asm("%a0"), unsigned char* dest asm("%a1"));

.text
.globl CreateISpriteShadow8_R
.even

CreateISpriteShadow8_R:
    subq.w   #1,%d0
    blt.s    1f

    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)

0:
    move.b   (%a0)+,%d3
    move.b   (%a0)+,%d1
    move.b   (%a0)+,%d2

    move.b   %d1,%d4
    not.b    %d4
    or.b     %d2,%d4
    or.b     %d1,%d2
    
    move.b   %d3,(%a1)+
    |not.b    %d1
    and.b    %d3,%d2
    and.b    %d3,%d4
    
    move.b   %d4,(%a1)+
    move.b   %d2,(%a1)+

    dbf      %d0,0b

    move.w   (%sp)+,%d4
    move.w   (%sp)+,%d3

1:
    rts
