| C prototype: void SpriteX8_MIRROR_V_R(unsigned short height asm("%d0"), const unsigned char* src asm("%a1"), unsigned short bytewidth asm("%d2"), unsigned char* dest asm("%a0")) __attribute__((__regparm__(4)));
|
| This routine is about 30% faster than the previous C routine.

.text
.globl SpriteX8_MIRROR_V_R
.even

SpriteX8_MIRROR_V_R:
    dbf      %d0,3f
    rts

3:
    move.w   %d0,%d1

    move.w   %d3,-(%sp)

    move.w   %d2,%d3
    beq.s    2f
    add.w    %d3,%d3

    mulu.w   %d2,%d1
    
    adda.w   %d1,%a0

    subq.w   #1,%d2

0:
    move.w   %d2,%d1
1:
| Very tight loop...
    move.b   (%a1)+,(%a0)+
    dbf      %d1,1b
    suba.w   %d3,%a0
    dbf      %d0,0b

2:
    move.w   (%sp)+,%d3
    rts
