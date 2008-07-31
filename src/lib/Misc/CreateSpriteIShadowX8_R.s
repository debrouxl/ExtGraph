| C prototype: void CreateSpriteIShadowX8_R(unsigned short height asm("%d0"), unsigned short bytewidth asm("%d1"), const unsigned char* src0 asm("%a0"), const unsigned char* src1 asm("%a1"), const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));

.text
.globl CreateSpriteIShadowX8_R
.even

CreateSpriteIShadowX8_R:
    subq.w   #1,%d0
    blt.s    2f

    subq.w   #1,%d1
    blt.s    2f

    movem.l  %d3-%d5/%a2-%a4,-(%sp)

    move.l   4+24(%sp),%a2
    move.l   4+24+4(%sp),%a3
    move.l   4+24+8(%sp),%a4

    move.w   %d1,%d5
    
0:
    move.w   %d5,%d4
1:
    move.b   (%a0)+,%d1
    move.b   (%a1)+,%d2

    move.b   %d1,%d3
    and.b    %d2,%d3
    not.b    %d1
    and.b    %d1,%d2
    
    move.b   (%a2)+,%d1
    |not.b    %d1
    and.b    %d1,%d2
    and.b    %d1,%d3
    
    move.b   %d2,(%a3)+
    move.b   %d3,(%a4)+

    dbf      %d4,1b
    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5/%a2-%a4

2:
    rts
