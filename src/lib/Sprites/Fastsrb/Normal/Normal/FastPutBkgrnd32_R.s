| C prototype: void FastPutBkgrnd32_R(const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
|
| This routine is a fast version of Sprite32_RPLC_R, it must be used in conjunction
| with FastGetBkgrnd32_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.

.text
.globl FastPutBkgrnd32_R
.even

FastPutBkgrnd32_R:
    movem.l  %d3-%d5,-(%sp)

    move.w   (%a1)+,%d2 | height

    moveq    #15,%d0
    and.w    (%a1)+,%d0 | x&15

    adda.w   (%a1)+,%a0 | offset

    moveq    #-1,%d1
    lsr.w    %d0,%d1
    move.w   %d1,%d3
    swap     %d1

    move.l   %d1,%d0
    not.l    %d1
    move.w   %d3,%d4
    not.w    %d3

0:
    move.l   (%a1)+,%d5
    and.l    %d0,%d5
    and.l    %d1,(%a0)
    or.l     %d5,(%a0)+
    move.w   (%a1)+,%d5
    and.w    %d3,%d5
    and.w    %d4,(%a0)
    or.w     %d5,(%a0)
    lea      30-4(%a0),%a0
    dbf      %d2,0b

    movem.l  (%sp)+,%d3-%d5
    rts
