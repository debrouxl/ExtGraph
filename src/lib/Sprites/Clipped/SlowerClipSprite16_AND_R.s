| C prototype: void SlowerClipSprite16_AND_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned short *sprt asm("%a1"),register void *dest asm("%a0"));

.text
.globl SlowerClipSprite16_AND_R
.even

SlowerClipSprite16_AND_R:
    move.w   %d3,-(%sp)
    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    __YPositive_ClipSprite16_AND_R	| h > 0 ?
    add.w    %d1,%d2		| %d2 = y + h
    bmi.s    __End_ClipSprite16_AND_R		| y + h < 0 ?
    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a1		| sprt -= 2y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    __ClipX_ClipSprite16_AND_R
__YPositive_ClipSprite16_AND_R:
    subi.w   #PLANE_PIXEL_HEIGHT-1,%d3		| %d3 = y - (PLANE_PIXEL_HEIGHT-1)
    bhi.s    __End_ClipSprite16_AND_R		| y - (PLANE_PIXEL_HEIGHT-1) > 0 ?
    add.w    %d2,%d3		| %d3 = h + y - (PLANE_PIXEL_HEIGHT-1)
    bmi.s    __CalcOffset_ClipSprite16_AND_R	| h + y - (PLANE_PIXEL_HEIGHT-1) < 0 ?
    sub.w    %d3,%d2		| h -= h + y - (PLANE_PIXEL_HEIGHT-1) <=> (h = y - (PLANE_PIXEL_HEIGHT-1))
__CalcOffset_ClipSprite16_AND_R:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*PLANE_BYTE_WIDTH/2
__ClipX_ClipSprite16_AND_R:
    move.w   %d0,%d3		| %d3 = x
    bmi.s    __ClipXLeft_ClipSprite16_AND_R	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-16,%d0
    bhi.s    __ClipXRight_ClipSprite16_AND_R	| x > PLANE_PIXEL_WIDTH-1-15
    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    moveq.l  #16,%d1
    andi.w   #15,%d0
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)
__Loop_ClipSprite16_AND_R:
    moveq.l  #-1,%d0
    move.w   (%a1)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,__Loop_ClipSprite16_AND_R
    move.w   (%sp)+,%d3
    rts
__ClipXLeft_ClipSprite16_AND_R:
    cmpi.w   #-16,%d0
    bls.s    __End_ClipSprite16_AND_R		| x <= -16 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
__LoopClipL_ClipSprite16_AND_R:
    moveq.l  #-1,%d1
    move.w   (%a1)+,%d1
    rol.l    %d0,%d1		| shifting
    and.w    %d1,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,__LoopClipL_ClipSprite16_AND_R
__End_ClipSprite16_AND_R:
    move.w   (%sp)+,%d3
    rts
__ClipXRight_ClipSprite16_AND_R:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    __End_ClipSprite16_AND_R		| x > PLANE_PIXEL_WIDTH-1
    andi.w   #15,%d0		| shiftx = x & 15
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    lea.l    PLANE_BYTE_WIDTH-2(%a0,%d1.w),%a0
__LoopClipR_ClipSprite16_AND_R:
    moveq.l  #-1,%d1
    move.w   (%a1)+,%d1
    lsr.l    %d0,%d1
    and.w    %d1,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,__LoopClipR_ClipSprite16_AND_R
    move.w   (%sp)+,%d3
    rts
