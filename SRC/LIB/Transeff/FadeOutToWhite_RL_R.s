| C prototype: void FadeOutToWhite_RL_R(register void *lightplane asm("%a0"),register void *darkplane asm("%a1"),register short height asm("%d0"),register short bytewidth asm("%d1"),register short wait asm("%d2"));

.text
.globl FadeOutToWhite_RL_R
.even
FadeOutToWhite_RL_R:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d1,__rest1_of_FOTW_RL_R__
    rts

__rest1_of_FOTW_RL_R__:
| Best way to subtract 1 from d1, with exit if d1 = 0.
    dbf      %d0,__rest2_of_FOTW_RL_R__
    rts

__rest2_of_FOTW_RL_R__:
    movem.l  %d3-%d5/%a2-%a3,-(%sp)

    move.w   %d0,%d3
    move.w   %d2,%d4
    move.l   %a0,%a2
    move.l   %a1,%a3
    adda.w   %d1,%a2
    adda.w   %d1,%a3

__outer_loop_FOTW_RL_R__:
    moveq    #0,%d5
_outer_loop_FOTW_RL_R__:
    move.w   %d3,%d0
    move.l   %a2,%a0
    move.l   %a3,%a1

__inner_loop_FOTW_RL_R__:
    bclr     %d5,(%a0)
    bclr     %d5,(%a1)
    lea      30(%a0),%a0
    lea      30(%a1),%a1
    move.w   %d4,%d2
__wait_loop_FOTW_RL_R__:
    dbf      %d2,__wait_loop_FOTW_RL_R__

    dbf      %d0,__inner_loop_FOTW_RL_R__

    addq.w   #1,%d5
    cmpi.w   #7,%d5
    bls.s    _outer_loop_FOTW_RL_R__

    subq.l   #1,%a2
    subq.l   #1,%a3
    dbf      %d1,__outer_loop_FOTW_RL_R__

    movem.l  (%sp)+,%d3-%d5/%a2-%a3
    rts