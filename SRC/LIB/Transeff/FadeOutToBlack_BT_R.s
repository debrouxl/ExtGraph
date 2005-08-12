| C prototype: void FadeOutToBlack_BT_R(register void *lightplane asm("%a0"),register void *darkplane asm("%a1"),register short height asm("%d0"),register short bytewidth asm("%d1"),register short wait asm("%d2"));

.text
.globl FadeOutToBlack_BT_R
.even
FadeOutToBlack_BT_R:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d1,__rest1_of_FOTB_BT_R__
    rts

__rest1_of_FOTB_BT_R__:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d0,__rest2_of_FOTB_BT_R__
    rts

__rest2_of_FOTB_BT_R__:
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

__outer_loop_FOTB_BT_R__:
    move.w   %d3,%d0

__inner_loop_FOTB_BT_R__:
    st.b     -(%a0)
    st.b     -(%a1)
    move.w   %d4,%d2
__wait_loop_FOTB_BT_R__:
    dbf      %d2,__wait_loop_FOTB_BT_R__

    dbf      %d0,__inner_loop_FOTB_BT_R__

    dbf      %d1,__outer_loop_FOTB_BT_R__

    move.l   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
