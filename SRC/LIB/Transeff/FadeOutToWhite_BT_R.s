| C prototype: void FadeOutToWhite_BT_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToWhite_BT_R
.even
FadeOutToWhite_BT_R:
    subq.w   #1,%d0
    blt.s    0f
    subq.w   #1,%d1
    blt.s    0f

| RFS: there's a good reason to save longs.
    move.l   %d3,-(%sp)
    move.l   %d4,-(%sp)

    move.w   %d0,%d3
    addq.w   #1,%d3
    move.w   %d1,%d4
    addq.w   #1,%d4
    mulu.w   %d4,%d3
    adda.w   %d3,%a0
    adda.w   %d3,%a1

    move.w   %d0,%d3
    move.w   %d2,%d4

1:
    move.w   %d3,%d0

2:
    sf.b     -(%a0)
    sf.b     -(%a1)
    move.w   %d4,%d2
3:
    dbf      %d2,3b

    dbf      %d0,2b

    dbf      %d1,1b

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3
0:
    rts
