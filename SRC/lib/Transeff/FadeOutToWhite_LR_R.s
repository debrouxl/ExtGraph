| C prototype: void FadeOutToWhite_LR_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToWhite_LR_R
.even
FadeOutToWhite_LR_R:
    subq.w   #1,%d0
    blt.s    0f
    subq.w   #1,%d1
    blt.s    0f

    movem.l  %d3-%d5/%a2-%a3,-(%sp)

    move.w   %d0,%d3
    move.w   %d2,%d4
    move.l   %a0,%a2
    move.l   %a1,%a3

1:
    moveq    #7,%d5
2:
    move.w   %d3,%d0
    move.l   %a2,%a0
    move.l   %a3,%a1

3:
    bclr     %d5,(%a0)
    bclr     %d5,(%a1)
    lea      30(%a0),%a0
    lea      30(%a1),%a1
    move.w   %d4,%d2
4:
    dbf      %d2,4b

    dbf      %d0,3b


    dbf      %d5,2b

    addq.l   #1,%a2
    addq.l   #1,%a3
    dbf      %d1,1b

    movem.l  (%sp)+,%d3-%d5/%a2-%a3
0:
    rts
