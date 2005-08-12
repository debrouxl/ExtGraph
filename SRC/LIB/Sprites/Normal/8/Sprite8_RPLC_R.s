| C prototype: void Sprite8_RPLC_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),register void *dest asm("%a0"));

.text
.globl Sprite8_RPLC_R
.even

Sprite8_RPLC_R:
    dbf    %d2,0f
    rts

0:
    move.l   %d3,-(%sp)

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    move.w   %d0,%d3
    lsr.w    #4,%d3

    add.w    %d3,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #-1,%d3
    clr.b    %d3

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
    swap     %d3
    ror.l    %d1,%d3
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d3
    rts

3:
    rol.w    %d1,%d3
2:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,2b

    move.l   (%sp)+,%d3
    rts
