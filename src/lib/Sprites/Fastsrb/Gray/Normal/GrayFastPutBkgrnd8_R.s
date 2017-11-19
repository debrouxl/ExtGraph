| C prototype: void GrayFastPutBkgrnd8_R(const unsigned short *sprt asm("%a2"), void *dest1 asm("%a0"), void *dest2 asm("%a1"));
|
| This routine is a fast version of GraySprite8_RPLC_R, it must be used in conjunction
| with GrayFastGetBkgrnd8_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.

.text
.globl GrayFastPutBkgrnd8_R
.even

GrayFastPutBkgrnd8_R:
    move.l   %a2,-(%sp)
    move.l   %d3,-(%sp)

    move.w   (%a2)+,%d2 | height

    adda.w   (%a2),%a0 | offset
    adda.w   (%a2)+,%a1 | offset

    move.w   (%a2)+,%d0 | x&15
    add.w    %d0,%d0
    cmpi.w   #8*2,%d0
    bgt.s    3f

    move.w   6f(%pc,%d0.w),%d1
    move.w   %d1,%d0
    not.w    %d0

    lsr.w    #1,%d2
    bcs.s    1f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    lea      -PLANE_BYTE_WIDTH(%a1),%a1
    bra.s    2f

1:
    move.w   (%a2)+,%d3
    and.w    %d0,%d3
    and.w    %d1,(%a0)
    or.w     %d3,(%a0)
    move.w   (%a2)+,%d3
    and.w    %d0,%d3
    and.w    %d1,(%a1)
    or.w     %d3,(%a1)
2:
    move.w   (%a2)+,%d3
    and.w    %d0,%d3
    and.w    %d1,PLANE_BYTE_WIDTH(%a0)
    or.w     %d3,PLANE_BYTE_WIDTH(%a0)
    move.w   (%a2)+,%d3
    and.w    %d0,%d3
    and.w    %d1,PLANE_BYTE_WIDTH(%a1)
    or.w     %d3,PLANE_BYTE_WIDTH(%a1)

    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b

    move.l   (%sp)+,%d3
    move.l   (%sp)+,%a2
    rts

6:
.word 0x00FF
.word 0x807F
.word 0xC03F
.word 0xE01F
.word 0xF00F
.word 0xF807
.word 0xFC03
.word 0xFE01
.word 0xFF00

    
3:
    add.w    %d0,%d0
    move.l   (7f-9*4)(%pc,%d0.w),%d1
    move.l   %d1,%d0
    not.l    %d0

    lsr.w    #1,%d2
    bcs.s    4f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    bra.s    5f

4:
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,(%a0)
    or.l     %d3,(%a0)
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,(%a1)
    or.l     %d3,(%a1)
5:
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,PLANE_BYTE_WIDTH(%a0)
    or.l     %d3,PLANE_BYTE_WIDTH(%a0)
    move.l   (%a2)+,%d3
    and.l    %d0,%d3
    and.l    %d1,PLANE_BYTE_WIDTH(%a1)
    or.l     %d3,PLANE_BYTE_WIDTH(%a1)

    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

    move.l   (%sp)+,%d3
    move.l   (%sp)+,%a2
    rts

7:
.long 0xFF807FFF
.long 0xFFC03FFF
.long 0xFFE01FFF
.long 0xFFF00FFF
.long 0xFFF807FF
.long 0xFFFC03FF
.long 0xFFFE01FF
