| C prototype: void GrayClipFastPutBkgrnd16_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned long *sprt,register void *dest1 asm("%a0"),register void *dest2 asm("%a1")) __attribute__((__stkparm__));
|
| This routine is a fast version of GrayClipSprite16_RPLC_R, it must be used in
| conjunction with GrayClipFastGetBkgrnd16_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.
/*
.text
.globl GrayClipFastPutBkgrnd16_R
.even

GrayClipFastPutBkgrnd16_R:
    dbf      %d2,0f
    rts

0:
    pea      (%a2)
    move.l   %d3,-(%sp)
    move.l   4+8(%sp),%a2

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    move.w   %d0,%d3
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0
    adda.w   %d0,%a1

    andi.w   #0xF,%d3
    add.w    %d3,%d3
    add.w    %d3,%d3
    move.l   3f(%pc,%d3.w),%d1
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
*/
