| C prototype: void CreateSpriteShadow8_R(unsigned short height asm("%d0"), const unsigned char* src0 asm("%a0"), const unsigned char* src1 asm("%a1"), const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));

.text
.globl CreateSpriteShadow8_R
.even

CreateSpriteShadow8_R:
    subq.w   #1,%d0
    blt.s    1f

    movem.l  %d3/%a2-%a4,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3
    move.l   4+16+8(%sp),%a4

0:
    move.b   (%a0)+,%d1
    move.b   (%a1)+,%d2

    move.b   %d1,%d3
    not.b    %d3
    or.b     %d2,%d3
    or.b     %d1,%d2
    
    move.b   (%a2)+,%d1
    not.b    %d1
    and.b    %d1,%d2
    and.b    %d1,%d3
    
    move.b   %d3,(%a3)+
    move.b   %d2,(%a4)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3/%a2-%a4

1:
    rts
