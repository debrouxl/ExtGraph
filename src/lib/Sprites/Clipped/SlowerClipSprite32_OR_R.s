| C prototype: void SlowerClipSprite32_OR_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned long *sprt asm("%a1"),register void *dest asm("%a0"));

.text
.globl SlowerClipSprite32_OR_R
.even

SlowerClipSprite32_OR_R:
    move.l   %d3,-(%sp)
    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    __YPositive_ClipSprite32_OR_R	| h > 0 ?
    add.w    %d1,%d2		| %d2 = y + h
    bmi.s    __End_ClipSprite32_OR_R		| y + h < 0 ?
    add.w    %d1,%d1		| %d1 = 2y
    add.w    %d1,%d1		| %d1 = 4y
    suba.w   %d1,%a1		| sprt -= 4y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    __ClipX_ClipSprite32_OR_R
__YPositive_ClipSprite32_OR_R:
    subi.w   #PLANE_PIXEL_HEIGHT-1,%d3		| %d3 = y - (PLANE_PIXEL_HEIGHT-1)
    bhi.s    __End_ClipSprite32_OR_R		| y - (PLANE_PIXEL_HEIGHT-1) > 0 ?
    add.w    %d2,%d3		| %d3 = h + y - (PLANE_PIXEL_HEIGHT-1)
    bmi.s    __CalcOffset_ClipSprite32_OR_R	| h + y - (PLANE_PIXEL_HEIGHT-1) < 0 ?
    sub.w    %d3,%d2		| h -= h + y - (PLANE_PIXEL_HEIGHT-1) <=> (h = y - (PLANE_PIXEL_HEIGHT-1))
__CalcOffset_ClipSprite32_OR_R:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*PLANE_BYTE_WIDTH/2
__ClipX_ClipSprite32_OR_R:
    move.w   %d0,%d3		| %d3 = x
    bmi.s    __ClipXLeft_ClipSprite32_OR_R	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-32,%d0
    bhi.s    __ClipXRight_ClipSprite32_OR_R	| x > PLANE_PIXEL_WIDTH-1-32
    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    moveq.l  #16,%d1
    andi.w   #15,%d0		| %d0 = righshift
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)
    move.w   %d4,-(%sp)
__Loop_ClipSprite32_OR_R:
    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,(%a0)+
    or.w     %d4,(%a0)
    lea.l    PLANE_BYTE_WIDTH-4(%a0),%a0
    dbf      %d2,__Loop_ClipSprite32_OR_R
    move.w   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
__ClipXLeft_ClipSprite32_OR_R:
    cmpi.w   #-32,%d0
    bls.s    __End_ClipSprite32_OR_R		| x <= -32 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
__LoopClipL_ClipSprite32_OR_R:
    move.l   (%a1)+,%d1
    lsl.l    %d0,%d1		| shifting
    or.l     %d1,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,__LoopClipL_ClipSprite32_OR_R
__End_ClipSprite32_OR_R:
    move.l   (%sp)+,%d3
    rts
__ClipXRight_ClipSprite32_OR_R:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    __End_ClipSprite32_OR_R		| x > PLANE_PIXEL_WIDTH-1
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    lea.l    PLANE_BYTE_WIDTH-4(%a0,%d1.w),%a0
    move.w   %d0,%d3
    andi.w   #15,%d0		| shiftx
    cmpi.w   #224,%d3
    blt.s    __LoopClipR_ClipSprite32_OR_R
    addi.w   #16,%d0
__LoopClipR_ClipSprite32_OR_R:
    move.l   (%a1)+,%d1
    lsr.l    %d0,%d1
    or.l     %d1,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,__LoopClipR_ClipSprite32_OR_R
    move.l   (%sp)+,%d3
    rts
