| C prototype: void Sprite16_BLIT(unsigned short x, unsigned short y, unsigned short h, const unsigned short *sprt, const unsigned short maskval, void *dest) __attribute__((__stkparm__));

.text
.globl Sprite16_BLIT
.even

Sprite16_BLIT:
    move.l   %d3,-(%sp)

    lea.l    4+4(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    addq.l   #2,%a0
    movea.l  (%a0)+,%a1
    moveq.l  #-1,%d3
    move.w   (%a0)+,%d3
    movea.l  (%a0),%a0

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

    move.w   4+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    rol.l    %d1,%d3

1:
    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b

0:
    move.l   (%sp)+,%d3
    rts
