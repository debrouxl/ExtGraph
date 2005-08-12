| C prototype: void FadeOutToBlack_RL18_R(register void *lightplane asm("%a0"),register void *darkplane asm("%a1"),register short height asm("%d0"),register short bytewidth asm("%d1"),register short wait asm("%d2"));

.text
.globl FadeOutToBlack_RL18_R
.even
FadeOutToBlack_RL18_R:
    mulu.w   %d0,%d1
    beq.s    __end_FOTB_RL18_R__
    subq.w   #1,%d1

    movem.l  %d3-%d4/%a2-%a3,-(%sp)

    move.w   %d1,%d3
    move.w   %d2,%d4
    move.l   %a0,%a2
    move.l   %a1,%a3

__outer_loop_FOTB_RL18_R__:
    moveq    #0,%d0
_outer_loop_FOTB_RL18_R__:
    move.w   %d3,%d1
__inner_loop_FOTB_RL18_R__:
    bset     %d0,(%a0)+
    bset     %d0,(%a1)+
    move.w   %d4,%d2
__wait_loop_FOTB_RL18_R__:
    dbf      %d2,__wait_loop_FOTB_RL18_R__

    dbf      %d1,__inner_loop_FOTB_RL18_R__

    move.l   %a2,%a0
    move.l   %a3,%a1

    addq.w   #1,%d0
    cmpi.w   #7,%d0
    bls.s    _outer_loop_FOTB_RL18_R__

__end_FOTB_RL18_R__:
    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts
