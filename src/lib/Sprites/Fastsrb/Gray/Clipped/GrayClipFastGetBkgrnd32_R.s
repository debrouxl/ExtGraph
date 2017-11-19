| C prototype: void GrayClipFastGetBkgrnd32_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned short* dest) __attribute__((__stkparm__));
|
| This routine is a fast clipped grayscale version of Sprite32Get_R, it must be
| used in conjunction with GrayClipFastPutBkgrnd32_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.
/*
.text
.globl GrayClipFastGetBkgrnd32_R
.even

GrayClipFastGetBkgrnd32_R:
    dbf      %d2,2f
    rts

2:
    pea      (%a2)
    move.l   4+4(%sp),%a2
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0
    adda.w   %d0,%a1

    swap     %d2
    lsr.w    #1,%d2
    bcs.s    0f
    lea      -PLANE_BYTE_WIDTH+4(%a0),%a0
    lea      -PLANE_BYTE_WIDTH+4(%a1),%a1
    bra.s    1f

0:
    move.l   (%a0)+,(%a2)+
    move.l   (%a1)+,(%a2)+
    move.w   (%a0),(%a2)+
    move.w   (%a1),(%a2)+
1:
    move.l   PLANE_BYTE_WIDTH-4(%a0),(%a2)+
    move.l   PLANE_BYTE_WIDTH-4(%a1),(%a2)+
    move.w   PLANE_BYTE_WIDTH(%a0),(%a2)+
    move.w   PLANE_BYTE_WIDTH(%a1),(%a2)+
    lea      2*PLANE_BYTE_WIDTH-4(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH-4(%a1),%a1
    dbf      %d2,0b

    move.l   (%sp)+,%a2
    rts
*/
