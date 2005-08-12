| C prototype: void Sprite32_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned long *sprt asm("%a1"),register unsigned long mask asm("%d3"),register void *dest asm("%a0"));

.text
.globl Sprite32_BLIT_R
.even

Sprite32_BLIT_R:
    dbf    %d2,0f
    rts

0:
    movem.l  %d3-%d6,-(%sp)

    move.w   %d1,%d5
    lsl.w    #4,%d1
    sub.w    %d5,%d1

    move.w   %d0,%d5
    lsr.w    #4,%d5

    add.w    %d5,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    move.w   %d0,%d1
    and.w    #0xF,%d1

    moveq.l  #16,%d5
    sub.w    %d1,%d5

    not.l    %d3
    move.w   %d3,%d4
    lsr.l    %d1,%d3
    not.l    %d3
    lsl.w    %d5,%d4
    not.w    %d4

1:
    move.l   (%a1)+,%d0
    move.w   %d0,%d6
    lsl.w    %d5,%d6
    lsr.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)+
    and.w    %d4,(%a0)
    or.w     %d6,(%a0)

    lea      30-4(%a0),%a0
    dbf      %d2,1b

    movem.l  (%sp)+,%d3-%d6

    rts
