| C prototype: void FadeOutToWhite_BT_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToWhite_BT_R
.even
FadeOutToWhite_BT_R:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d1,__rest1_of_FOTW_BT_R__
    rts

__rest1_of_FOTW_BT_R__:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d0,__rest2_of_FOTW_BT_R__
    rts

__rest2_of_FOTW_BT_R__:
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

__outer_loop_FOTW_BT_R__:
    move.w   %d3,%d0

__inner_loop_FOTW_BT_R__:
    sf.b     -(%a0)
    sf.b     -(%a1)
    move.w   %d4,%d2
__wait_loop_FOTW_BT_R__:
    dbf      %d2,__wait_loop_FOTW_BT_R__

    dbf      %d0,__inner_loop_FOTW_BT_R__

    dbf      %d1,__outer_loop_FOTW_BT_R__

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
