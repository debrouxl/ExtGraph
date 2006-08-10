| C prototype: void SpriteX8_MIRROR_V(short h,unsigned char* src,short bytewidth,unsigned char* dest) __attribute__((__stkparm__));
|
| This routine is about 30% faster than the previous C routine.

.text
.globl SpriteX8_MIRROR_V
.even

SpriteX8_MIRROR_V:
    move.w   0+4+0(%sp),%d0
    beq.s    2f

    subq.w   #1,%d0
    move.w   %d0,%d1

    movea.l  0+4+2(%sp),%a1
    move.w   0+4+6(%sp),%d2
    beq.s    2f

    move.w   %d3,-(%sp)

    move.w   %d2,%d3
    add.w    %d3,%d3

    mulu.w   %d2,%d1
    
    movea.w  %d1,%a0

    subq.w   #1,%d2

    adda.l   2+4+8(%sp),%a0
0:
    move.w   %d2,%d1
1:
| Very tight loop...
    move.b   (%a1)+,(%a0)+
    dbf      %d1,1b
    suba.w   %d3,%a0
    dbf      %d0,0b
    move.w   (%sp)+,%d3

2:
    rts
