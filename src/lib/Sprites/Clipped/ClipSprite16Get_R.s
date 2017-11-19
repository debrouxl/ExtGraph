| C prototype: void ClipSprite16Get_R(short x asm("%d0"),short y asm("%d1"),unsigned short height asm("%d2"), void *dest asm("%a0"), unsigned short *sprt asm("%a1"));

.text
.globl ClipSprite16Get_R
.even

ClipSprite16Get_R:
    move.l   %d3,-(%sp)

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a1		| sprt -= 2y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    10f

9:
    add.w    %d2,%d3		| %d3 = h + y
    subi.w   #PLANE_PIXEL_HEIGHT-1,%d3		| %d3 = h + y - (PLANE_PIXEL_HEIGHT-1)
    ble.s    6f			| h + y - (PLANE_PIXEL_HEIGHT-1) <= 0 ?
    sub.w    %d3,%d2		| h -= h + y - (PLANE_PIXEL_HEIGHT-1) <=> (h = (PLANE_PIXEL_HEIGHT-1)-y)
    bmi.s    0f

6:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*PLANE_BYTE_WIDTH/2

10:
    move.w   %d0,%d3		| %d3 = x
    ble.s    8f	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-16,%d0
    bhi.s    7f	| x > PLANE_PIXEL_WIDTH-1-15

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0

    moveq.l  #16,%d1
    andi.w   #15,%d0
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)

1:
    move.l   (%a0),%d0
    lsr.l    %d1,%d0
    move.w   %d0,(%a1)+

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b

0:
    move.l   (%sp)+,%d3
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?

    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0
4:
    move.w   (%a0),%d1
    lsr.w    %d0,%d1		| shifting
    move.w   %d1,(%a1)+

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,4b

    move.l   (%sp)+,%d3
    rts

7:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    0b		| x > PLANE_PIXEL_WIDTH-1

    andi.w   #15,%d0		| shiftx = x & 15
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    lea.l    PLANE_BYTE_WIDTH-2(%a0,%d1.w),%a0	| dest += offset
5:
    move.w   (%a0),%d1
    lsl.w    %d0,%d1
    move.w   %d1,(%a1)+

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,5b

    move.l   (%sp)+,%d3
    rts
