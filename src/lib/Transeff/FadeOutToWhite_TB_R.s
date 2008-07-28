| C prototype: void FadeOutToWhite_TB_R(void *lightplane asm("%a0"), void *darkplane asm("%a1"), unsigned short height asm("%d0"), unsigned short bytewidth asm("%d1"), short wait asm("%d2"));

.text
.globl FadeOutToWhite_TB_R
.even
FadeOutToWhite_TB_R:
    subq.w   #1,%d0
    blt.s    0f
    subq.w   #1,%d1
    blt.s    0f

| RFS: there's a good reason to save longs.
    move.l   %d3,-(%sp)
    move.l   %d4,-(%sp)

    move.w   %d0,%d3
    move.w   %d2,%d4

1:
    move.w   %d3,%d0

2:
    sf.b     (%a0)+
    sf.b     (%a1)+
    move.w   %d4,%d2
3:
    dbf      %d2,3b

    dbf      %d0,2b

    dbf      %d1,1b

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3
0:
    rts
