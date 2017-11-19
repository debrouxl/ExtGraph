| C prototype: void GrayClipFastPutBkgrnd8_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned long *sprt,void *dest1 asm("%a0"),void *dest2 asm("%a1")) __attribute__((__stkparm__));
|
| This routine is a fast version of GrayClipSprite8_RPLC_R, it must be used in
| conjunction with GrayClipFastGetBkgrnd8_R.
| These routines are designed for programs with (non-clipped) masked sprites (double
| XOR is usually often with non-masked sprites) for which redrawing everything every
| frame is detrimental to speed.
/*
.text
.globl GrayClipFastPutBkgrnd8_R
.even

GrayClipFastPutBkgrnd8_R:
    move.l   %d3,-(%sp)
    pea      (%a2)
    move.l   4+8(%sp),%a2

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    __YPositive_GCFPB8_R	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    moveq.l  #0,%d1		| offsety = 0
    bra.s    __ClipX_GCFPB8_R

__YPositive_GCFPB8_R:
    subi.w   #127,%d3		| %d3 = y - 128
    bhi.s    0f		| y - 128 > 0 ?
    add.w    %d2,%d3		| %d3 = h + y - 128
    bmi.s    6f	| h + y - 128 < 0 ?
    sub.w    %d3,%d2		| h -= h + y -128 (h = y - 128)

6:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*PLANE_BYTE_WIDTH

__ClipX_GCFPB8_R:
    move.w   %d0,%d3		| %d3 = x
    bmi.s    __ClipXLeft_GCFPB8_R	| x < 0 ?
    cmpi.w   #239-8,%d0
    bhi.s    __ClipXRight_GCFPB8_R	| x > 239-8

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

__ClipXLeft_GCFPB8_R:
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

__ClipXRight_GCFPB8_R:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239
    
    add.w    %d1,%d1
    addi.w   #29,%d1
    bra.s    5b


GrayClipFastPutBkgrnd8_R:
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
    cmpi.w   #8,%d3
    bgt.s    3f

    add.w    %d3,%d3
    move.w   6f(%pc,%d3.w),%d1
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
|    subi.w   #9,%d3
    add.w    %d3,%d3
    add.w    %d3,%d3
    move.l   (7f-9*4)(%pc,%d3.w),%d1
|    move.l   7f(%pc,%d3.w),%d1
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
*/