| C prototype: void PreshiftGrayISprite8x8(register unsigned char *src asm("%a0"),register unsigned long *dest asm("%a1"));

.globl PreshiftGrayISprite8x8
.even

PreshiftGrayISprite8x8:
    lea.l    14*8*4(%a1),%a1

    moveq.l  #2*8-1,%d2

_outer_loop_PGIS8x8_:
    moveq.l  #0,%d0
    move.w   (%a0)+,%d0

    moveq.l  #8-1,%d1

_inner_loop_PGIS8x8_:
    lsl.l    #2,%d0
    move.l   %d0,(%a1)
    lea.l    -16*2*4(%a1),%a1

    dbf      %d1,_inner_loop_PGIS8x8_

    lea.l    16*8*2*4+4(%a1),%a1

    dbf      %d2,_outer_loop_PGIS8x8_

    rts
