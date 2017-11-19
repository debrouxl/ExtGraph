| C prototype: void GrayFastPutBkgrnd32_R(const unsigned short *sprt asm("%a2"), void *dest1 asm("%a0"), void *dest2 asm("%a1"));
|
| This routine is a fast version of GraySprite32_RPLC_R, it must be used in conjunction
| with GrayFastGetBkgrnd32_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.

.text
.globl GrayFastPutBkgrnd32_R
.even

GrayFastPutBkgrnd32_R:
    movem.l  %d3-%d5/%a2,-(%sp)

    move.w   (%a2)+,%d2 | height

    moveq    #15,%d0
    and.w    (%a2)+,%d0 | x&15

    adda.w   (%a2),%a0 | offset
    adda.w   (%a2)+,%a1 | offset

    moveq    #-1,%d1
    lsr.w    %d0,%d1
    move.w   %d1,%d3
    swap     %d1

    move.l   %d1,%d0
    not.l    %d1
    move.w   %d3,%d4
    not.w    %d3

0:
    move.l   (%a2)+,%d5
    and.l    %d0,%d5
    and.l    %d1,(%a0)
    or.l     %d5,(%a0)+
    move.l   (%a2)+,%d5
    and.l    %d0,%d5
    and.l    %d1,(%a1)
    or.l     %d5,(%a1)+
    move.w   (%a2)+,%d5
    and.w    %d3,%d5
    and.w    %d4,(%a0)
    or.w     %d5,(%a0)
    move.w   (%a2)+,%d5
    and.w    %d3,%d5
    and.w    %d4,(%a1)
    or.w     %d5,(%a1)
    lea      PLANE_BYTE_WIDTH-4(%a0),%a0
    lea      PLANE_BYTE_WIDTH-4(%a1),%a1
    dbf      %d2,0b

    movem.l  (%sp)+,%d3-%d5/%a2
    rts
