| C prototype: void FadeOutToBlack_LR18_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToBlack_LR18_R
.even
FadeOutToBlack_LR18_R:
    mulu.w   %d0,%d1
    beq.s    0f
    subq.w   #1,%d1

    movem.l  %d3-%d4/%a2-%a3,-(%sp)

    move.w   %d1,%d3
    move.w   %d2,%d4
    move.l   %a0,%a2
    move.l   %a1,%a3

    moveq    #7,%d0
1:
    move.w   %d3,%d1
2:
    bset     %d0,(%a0)+
    bset     %d0,(%a1)+
    move.w   %d4,%d2
3:
    dbf      %d2,3b

    dbf      %d1,2b

    move.l   %a2,%a0
    move.l   %a3,%a1

    subq.w   #1,%d0
    bge.s    1b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
0:
    rts
