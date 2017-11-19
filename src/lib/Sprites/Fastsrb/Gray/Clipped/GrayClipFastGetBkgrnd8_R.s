| C prototype: void GrayClipFastGetBkgrnd8_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned long* dest) __attribute__((__stkparm__));
|
| This routine is a fast clipped grayscale version of Sprite8Get_R, it must be
| used in conjunction with GrayClipFastPutBkgrnd8_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.
/*
.text
.globl GrayClipFastGetBkgrnd8_R
.even

3:
    lsr.w    #1,%d2
    bcs.s    4f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    lea      -PLANE_BYTE_WIDTH(%a1),%a1
    bra.s    5f

4:
    move.l   (%a0),(%a2)+
    move.l   (%a1),(%a2)+
5:
    move.l   PLANE_BYTE_WIDTH(%a0),(%a2)+
    move.l   PLANE_BYTE_WIDTH(%a1),(%a2)+
    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

GrayClipFastGetBkgrnd8_R:
    move.w   %d3,-(%sp)
    pea      (%a2)
    move.l   4+6(%sp),%a2

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    __YPositive_GCFGB8_R	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    moveq.l  #0,%d1		| offsety = 0
    bra.s    __ClipX_GCFGB8_R

__YPositive_GCFGB8_R:
    add.w    %d2,%d3		| %d3 = h + y
    subi.w   #127,%d3		| %d3 = h + y - 127
    ble.s    6f			| h + y - 127 <= 0 ?
    sub.w    %d3,%d2		| h -= h + y - 127 (h = 127-y)
    bmi.s    0f

6:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*PLANE_BYTE_WIDTH

__ClipX_GCFGB8_R:
    move.w   %d0,%d3		| %d3 = x
    bmi.s    __ClipXLeft_GCFGB8_R	| x < 0 ?
    cmpi.w   #239-8,%d0
    bhi.s    __ClipXRight_GCFGB8_R	| x > 239-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    andi.w   #0xF,%d0
    cmpi.w   #8,%d0
    bgt.s    3b

    lsr.w    #1,%d2
    bcs.s    1f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    lea      -PLANE_BYTE_WIDTH(%a1),%a1
    bra.s    2f

1:
    move.w   (%a0),(%a2)+
    move.w   (%a1),(%a2)+
2:
    move.w   PLANE_BYTE_WIDTH(%a0),(%a2)+
    move.w   PLANE_BYTE_WIDTH(%a1),(%a2)+
    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b

0:
    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

__ClipXLeft_GCFGB8_R:
    cmpi.w   #-8,%d0
    ble.s    0b		| x <= -8 ?

    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH

5:
    adda.w   %d1,%a0
    adda.w   %d1,%a1

4:
    move.b   (%a0),(%a2)+
    move.b   (%a1),(%a2)+
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    lea      PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

__ClipXRight_GCFGB8_R:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239
    
    add.w    %d1,%d1
    addi.w   #29,%d1
    bra.s    5b
*/
