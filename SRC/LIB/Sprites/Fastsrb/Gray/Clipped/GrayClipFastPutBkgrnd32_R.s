| C prototype: void GrayClipFastPutBkgrnd32_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned short *sprt,register void *dest1 asm("%a0"),register void *dest2 asm("%a1")) __attribute__((__stkparm__));
|
| This routine is a fast version of GrayClipSprite32_RPLC_R, it must be used in
| conjunction with GrayClipFastGetBkgrnd32_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.
/*
.text
.globl GrayClipFastPutBkgrnd32_R
.even

GrayClipFastPutBkgrnd32_R:
    dbf      %d2,1f
    rts

1:
    movem.l  %d3-%d5/%a2,-(%sp)
    move.l   4+16(%sp),%a2
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0
    adda.w   %d0,%a1

    andi.w   #0xF,%d2

    moveq    #-1,%d1
    lsr.w    %d2,%d1
    move.w   %d1,%d3
    not.l    %d1
    swap     %d1

    move.l   %d1,%d0
    not.l    %d0
    move.w   %d3,%d4
    not.w    %d4

    swap     %d2

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
    and.w    %d4,%d5
    and.w    %d3,(%a0)
    or.w     %d5,(%a0)
    move.w   (%a2)+,%d5
    and.w    %d4,%d5
    and.w    %d3,(%a1)
    or.w     %d5,(%a1)
    lea      30-4(%a0),%a0
    lea      30-4(%a1),%a1
    dbf      %d2,0b

    movem.l  (%sp)+,%d3-%d5/%a2
    rts
*/
