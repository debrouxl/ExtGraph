| C prototype: void FadeOutToWhite_TB_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

.text
.globl FadeOutToWhite_TB_R
.even
FadeOutToWhite_TB_R:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d1,__rest1_of_FOTW_TB_R__
    rts

__rest1_of_FOTW_TB_R__:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d0,__rest2_of_FOTW_TB_R__
    rts

__rest2_of_FOTW_TB_R__:
    move.l   %d3,-(%sp)
    move.l   %d4,-(%sp)

    move.w   %d0,%d3
    move.w   %d2,%d4

__outer_loop_FOTW_TB_R__:
    move.w   %d3,%d0

__inner_loop_FOTW_TB_R__:
    sf.b     (%a0)+
    sf.b     (%a1)+
    move.w   %d4,%d2
__wait_loop_FOTW_TB_R__:
    dbf      %d2,__wait_loop_FOTW_TB_R__

    dbf      %d0,__inner_loop_FOTW_TB_R__

    dbf      %d1,__outer_loop_FOTW_TB_R__

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
