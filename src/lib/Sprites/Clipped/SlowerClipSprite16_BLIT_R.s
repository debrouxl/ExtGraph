| C prototype: void SlowerClipSprite16_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned short *sprt asm("%a1"),unsigned short maskval,register void *dest asm("%a0")) __attribute__((__stkparm__));

.text
.globl SlowerClipSprite16_BLIT_R
.even

SlowerClipSprite16_BLIT_R:
    move.l   %d3,-(%sp)

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    __YPositive_ClipSprite16_BLIT_R	| h > 0 ?
    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    __End_ClipSprite16_BLIT_R		| y + h < 0 ?
    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a1		| sprt -= 2*y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    __ClipX_ClipSprite16_BLIT_R
__YPositive_ClipSprite16_BLIT_R:
    subi.w   #127,%d3		| %d3 = y - 128
    bhi.s    __End_ClipSprite16_BLIT_R		| y - 128 > 0 ?
    add.w    %d2,%d3		| %d3 = h + y - 128
    bmi.s    __CalcOffset_ClipSprite16_BLIT_R	| h + y - 128 < 0 ?
    sub.w    %d3,%d2		| h -= h + y -128 (h = y - 128)
__CalcOffset_ClipSprite16_BLIT_R:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*15
__ClipX_ClipSprite16_BLIT_R:
    move.w   %d0,%d3		| %d3 = x
    bmi.s    __ClipXLeft_ClipSprite16_BLIT_R	| x < 0 ?
    cmpi.w   #239-16,%d0
    bhi.s    __ClipXRight_ClipSprite16_BLIT_R	| x > 239-15

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0

    moveq.l  #16,%d1
    andi.w   #15,%d0
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)

    moveq.l  #-1,%d3
    move.w   4+4(%sp),%d3
    rol.l    %d1,%d3

__Loop_ClipSprite16_BLIT_R:
    and.l    %d3,(%a0)

    moveq.l  #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,__Loop_ClipSprite16_BLIT_R

__End_ClipSprite16_BLIT_R:
    move.l   (%sp)+,%d3
    rts

__ClipXLeft_ClipSprite16_BLIT_R:

    cmpi.w   #-16,%d0
    bls.s    __End_ClipSprite16_BLIT_R		| x <= -16 ?
    neg.w    %d0		| shift = -x

    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0

    moveq.l  #-1,%d3
    move.w   2(%sp),%d3
    rol.l    %d0,%d3

__LoopClipL_ClipSprite16_BLIT_R:
    and.w    %d3,(%a0)

    move.w   (%a1)+,%d1
    lsl.w    %d0,%d1		| shifting
    or.w     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,__LoopClipR_ClipSprite16_BLIT_R

    move.l   (%sp)+,%d3
    rts

__ClipXRight_ClipSprite16_BLIT_R:
    cmpi.w   #239,%d0
    bhi.s    __End_ClipSprite16_BLIT_R		| x > 239

    andi.w   #15,%d0		| shiftx = x & 15
    add.w    %d1,%d1		| %d1 = y*30
    lea.l    28(%a0,%d1.w),%a0	| dest += offset

    moveq.l  #-1,%d3
    move.w   2(%sp),%d3
    ror.l    %d0,%d3

__LoopClipR_ClipSprite16_BLIT_R:
    and.w    %d3,(%a0)

    move.w   (%a1)+,%d1
    lsr.w    %d0,%d1
    or.w     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,__LoopClipR_ClipSprite16_BLIT_R

    move.l   (%sp)+,%d3
    rts
