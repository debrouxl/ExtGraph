| C prototype: void FastPutBkgrnd8_R(register const unsigned short *sprt asm("%a1"),register void *dest asm("%a0"));
|
| This routine is a fast version of Sprite8_RPLC_R, it must be used in conjunction
| with FastGetBkgrnd8_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.

.text
.globl FastPutBkgrnd8_R
.even

FastPutBkgrnd8_R:
    move.l   %d3,-(%sp)

    move.w   (%a1)+,%d2 | height

    adda.w   (%a1)+,%a0 | offset

    move.w   (%a1)+,%d0 | x&15
    add.w    %d0,%d0
    cmpi.w   #8*2,%d0
    bgt.s    3f

    move.w   6f(%pc,%d0.w),%d1
    move.w   %d1,%d0
    not.w    %d0

    lsr.w    #1,%d2
    bcs.s    1f
    lea      -30(%a0),%a0
    bra.s    2f

1:
    move.w   (%a1)+,%d3
    and.w    %d0,%d3
    and.w    %d1,(%a0)
    or.w     %d3,(%a0)
2:
    move.w   (%a1)+,%d3
    and.w    %d0,%d3
    and.w    %d1,30(%a0)
    or.w     %d3,30(%a0)

    lea      60(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d3
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
    lea      -30(%a0),%a0
    bra.s    5f

4:
    move.l   (%a1)+,%d3
    and.l    %d0,%d3
    and.l    %d1,(%a0)
    or.l     %d3,(%a0)
5:
    move.l   (%a1)+,%d3
    and.l    %d0,%d3
    and.l    %d1,30(%a0)
    or.l     %d3,30(%a0)

    lea      60(%a0),%a0
    dbf      %d2,4b

    move.l   (%sp)+,%d3
    rts

7:
.long 0xFF807FFF
.long 0xFFC03FFF
.long 0xFFE01FFF
.long 0xFFF00FFF
.long 0xFFF807FF
.long 0xFFFC03FF
.long 0xFFFE01FF
