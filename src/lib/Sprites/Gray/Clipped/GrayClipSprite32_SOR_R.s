| C prototype: void GrayClipSprite32_SOR_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), const unsigned long *sprt, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayClipSprite32_SOR_R
.even

GrayClipSprite32_SOR_R:
    move.l   %d3,-(%sp)
    move.l   %a2,-(%sp)

    move.l   4+8(%sp),%a2

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = y + h
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    add.w    %d1,%d1		| %d1 = 4y
    suba.w   %d1,%a2		| sprt -= 4y
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
    sub.w    %d3,%d1		| %d1 = y*15

10:
    move.w   %d0,%d3		| %d3 = x
    ble.s    8f	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-32,%d0
    bhi.s    7f	| x > PLANE_PIXEL_WIDTH-1-32

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1
    moveq.l  #16,%d1
    andi.w   #15,%d0		| %d0 = righshift
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)
    move.w   %d4,-(%sp)
    move.w   %d5,-(%sp)

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.w   %d3,%d4
    not.w    %d4
1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.w    %d4,%d5
    or.w     %d5,(%a0)+
    or.w     %d5,(%a1)+
    and.l    %d3,%d0
    or.l     %d0,(%a0)
    or.l     %d0,(%a1)

    lea.l    PLANE_BYTE_WIDTH-2(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH-2(%a1),%a1
    dbf      %d2,1b
    move.w   (%sp)+,%d5
    move.w   (%sp)+,%d4

0:
    move.l   (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts

8:
    cmpi.w   #-32,%d0
    ble.s    0b		| x <= -32 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1
4:
    move.l   (%a2)+,%d1
    lsl.l    %d0,%d1		| shifting
    or.l     %d1,(%a0)
    or.l     %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b
    bra.s    0b

7:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    0b		| x > PLANE_PIXEL_WIDTH-1
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    addi.w   #PLANE_BYTE_WIDTH-4,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

    subi.w   #208,%d0		| shiftx

5:
    move.l   (%a2)+,%d1
    lsr.l    %d0,%d1
    or.l     %d1,(%a0)
    or.l     %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,5b
    bra.s    0b
