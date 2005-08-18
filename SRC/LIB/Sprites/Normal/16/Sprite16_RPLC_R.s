| C prototype: void Sprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned short *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl Sprite16_RPLC_R
.even

Sprite16_RPLC_R:
    dbf      %d2,0f
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

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    clr.w    %d3
    rol.l    %d1,%d3

1:
    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d3
    rts
