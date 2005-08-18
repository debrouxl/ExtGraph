| C prototype: void GrayFastPutBkgrnd16_R(const unsigned short *sprt asm("%a2"),void *dest1 asm("%a0"),void *dest2 asm("%a1"));
|
| This routine is a fast version of GraySprite16_RPLC_R, it must be used in conjunction
| with GrayFastGetBkgrnd16_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.

.text
.globl GrayFastPutBkgrnd16_R
.even

GrayFastPutBkgrnd16_R:
    move.l   %a2,-(%sp)
    move.l   %d3,-(%sp)

    move.w   (%a2)+,%d2 | height

    moveq    #15,%d0
    and.w    (%a2)+,%d0 | x&15

    adda.w   (%a2),%a0 | offset
    adda.w   (%a2)+,%a1 | offset

    add.w    %d0,%d0
    add.w    %d0,%d0
    move.l   3f(%pc,%d0.w),%d1
    move.l   %d1,%d0
    not.l    %d0

    lsr.w    #1,%d2
    bcs.s    1f
    lea      -30(%a0),%a0
    lea      -30(%a1),%a1
    bra.s    2f

1:
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,(%a0)
    or.l     %d3,(%a0)
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,(%a1)
    or.l     %d3,(%a1)
2:
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,30(%a0)
    or.l     %d3,30(%a0)
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,30(%a1)
    or.l     %d3,30(%a1)
    lea      60(%a0),%a0
    lea      60(%a1),%a1
    dbf      %d2,1b

    move.l   (%sp)+,%d3
    move.l   (%sp)+,%a2
    rts

3:
.long 0x0000FFFF
.long 0x80007FFF
.long 0xC0003FFF
.long 0xE0001FFF
.long 0xF0000FFF
.long 0xF80007FF
.long 0xFC0003FF
.long 0xFE0001FF
.long 0xFF0000FF
.long 0xFF80007F
.long 0xFFC0003F
.long 0xFFE0001F
.long 0xFFF0000F
.long 0xFFF80007
.long 0xFFFC0003
.long 0xFFFE0001
