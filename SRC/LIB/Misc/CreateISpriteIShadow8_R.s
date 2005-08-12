| C prototype: void CreateISpriteIShadow8_R(register short height asm("%d0"),register unsigned char* src asm("%a0"),register unsigned char* dest asm("%a1")) __attribute__((__stkparm__));

.text
.globl CreateISpriteIShadow8_R
.even

CreateISpriteIShadow8_R:
    subq.w   #1,%d0
    blt.s    1f

    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)

0:
    move.b   (%a0)+,%d3
    move.b   (%a0)+,%d1
    move.b   (%a0)+,%d2

    move.b   %d1,%d4
    and.b    %d2,%d4
    not.b    %d1
    and.b    %d1,%d2
    
    move.b   %d3,(%a1)+

    not.b    %d3
    and.b    %d3,%d2
    and.b    %d3,%d4
    
    move.b   %d2,(%a1)+
    move.b   %d4,(%a1)+
    
    dbf      %d0,0b

    move.w   (%sp)+,%d4
    move.w   (%sp)+,%d3

1:
    rts
