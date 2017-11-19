| C prototype: void GrayClipISprite8_XOR_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprite, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayClipISprite8_XOR_R
.even

2:
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    lea      PLANE_BYTE_WIDTH(%a1),%a1
3:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    eor.w    %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    eor.w    %d0,(%a1)

    dbf      %d2,2b

    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

GrayClipISprite8_XOR_R:
    move.w   %d3,-(%sp)
    move.l   %a2,-(%sp)

    move.l   4+6(%sp),%a2

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1
    suba.w   %d1,%a2		| sprite -= 2y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    10f

9:
    subi.w   #PLANE_PIXEL_HEIGHT-1,%d3		| %d3 = y - (PLANE_PIXEL_HEIGHT-1)
    bhi.s    0f		| y - (PLANE_PIXEL_HEIGHT-1) > 0 ?
    add.w    %d2,%d3		| %d3 = h + y - )PLANE_PIXEL_HEIGHT-1(
    bmi.s    6f	| h + y - (PLANE_PIXEL_HEIGHT-1) < 0 ?
    sub.w    %d3,%d2		| h -= h + y - (PLANE_PIXEL_HEIGHT-1) <=> (h = y - (PLANE_PIXEL_HEIGHT-1))

6:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*15

10:
    move.w   %d0,%d3		| %d3 = x
    ble.s    8f	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-8,%d0
    bhi.s    7f	| x > PLANE_PIXEL_WIDTH-1-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3b

    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    eor.l    %d0,(%a0)

    moveq.l  #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    eor.l    %d0,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b
0:
    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

8:
    cmpi.w   #-8,%d0
    ble.s    0b		| x <= -8 ?

    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

4:
    move.b   (%a2)+,%d1
    lsl.b    %d0,%d1		| shifting
    eor.b    %d1,(%a0)

    move.b   (%a2)+,%d1
    lsl.b    %d0,%d1		| shifting
    eor.b    %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts

7:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    0b		| x > PLANE_PIXEL_WIDTH-1

    andi.w   #7,%d0		| shiftx = x & 7
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    addi.w   #PLANE_BYTE_WIDTH-1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

5:
    move.b   (%a2)+,%d1
    lsr.b    %d0,%d1
    eor.b    %d1,(%a0)

    move.b   (%a2)+,%d1
    lsr.b    %d0,%d1
    eor.b    %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,5b

    move.l   (%sp)+,%a2
    move.w   (%sp)+,%d3
    rts
