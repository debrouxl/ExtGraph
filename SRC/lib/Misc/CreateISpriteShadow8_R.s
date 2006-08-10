| C prototype: void CreateISpriteShadow8_R(short height asm("%d0"),unsigned char* src asm("%a0"),unsigned char* dest asm("%a1")) __attribute__((__stkparm__));

.text
.globl CreateISpriteShadow8_R
.even

CreateISpriteShadow8_R:
    subq.w   #1,%d0
    blt.s    1f

    move.w   %d3,-(%sp)

0:
    move.b   1(%a0),%d1
    move.b   2(%a0),%d2

    move.b   %d1,%d3
    not.b    %d3
    or.b     %d2,%d3
    or.b     %d1,%d2
    
    move.b   (%a0),%d1
    
    move.b   %d1,(%a1)+

    not.b    %d1
    and.b    %d1,%d2
    and.b    %d1,%d3
    
    move.b   %d3,(%a1)+
    move.b   %d2,(%a1)+

    addq.l   #3,%a0

    dbf      %d0,0b

    move.w   (%sp)+,%d3

1:
    rts
