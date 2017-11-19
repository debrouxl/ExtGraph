| C prototype: void GrayClipSprite8_TRANW_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt0, const unsigned char *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayClipSprite8_TRANW_R
.even

2:
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    lea      PLANE_BYTE_WIDTH(%a1),%a1

3:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0

    moveq    #0,%d3
    move.b   (%a3)+,%d3
    lsl.w    %d1,%d3

    move.w   %d3,%d4
    not.w    %d4
    and.w    (%a0),%d4
    or.w     %d0,%d4
    move.w   %d4,(%a0)

    not.w    %d0
    and.w    (%a1),%d0
    or.w     %d3,%d0
    move.w   %d0,(%a1)

    dbf      %d2,2b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts

GrayClipSprite8_TRANW_R:
    movem.l  %d3-%d4/%a2-%a3,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    suba.w   %d1,%a2		| sprt0 -= y
    suba.w   %d1,%a3		| sprt1 -= y
    moveq.l  #0,%d1		| offsety = 0
    bra.s    10f

9:
    add.w    %d2,%d3		| %d3 = h + y
    subi.w   #PLANE_PIXEL_HEIGHT-1,%d3		| %d3 = h + y - (PLANE_PIXEL_HEIGHT-1)
    ble.s    6f			| h + y - (PLANE_PIXEL_HEIGHT-1) <= 0 ?
    sub.w    %d3,%d2		| h -= h + y - (PLANE_PIXEL_HEIGHT-1) <=> (h = (PLANE_PIXEL_HEIGHT-1)-y)
    bmi.s    0f

6:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d3

10:
    move.w   %d0,%d3		| %d3 = x
    ble.s    8f	| x < 0 ?
    cmpi.w   #PLANE_PIXEL_WIDTH-1-8,%d0
    bhi.w    7f	| x > PLANE_PIXEL_WIDTH-1-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
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

    moveq.l  #0,%d3
    move.b   (%a3)+,%d3
    swap.w   %d3
    lsr.l    %d1,%d3

    move.l   %d3,%d4
    not.l    %d4
    and.l    (%a0),%d4
    or.l     %d0,%d4
    move.l   %d4,(%a0)

    not.l    %d0
    and.l    (%a1),%d0
    or.l     %d3,%d0
    move.l   %d0,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b
0:
    movem.l  (%sp)+,%d3-%d4/%a2-%a3
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

    move.b   (%a3)+,%d3
    lsl.b    %d0,%d3		| shifting

    move.b   %d3,%d4
    not.b    %d4
    and.b    (%a0),%d4
    or.b     %d1,%d4
    move.b   %d4,(%a0)

    not.b    %d1
    and.b    (%a1),%d1
    or.b     %d3,%d1
    move.b   %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
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

    move.b   (%a3)+,%d3
    lsr.b    %d0,%d3

    move.b   %d3,%d4
    not.b    %d4
    and.b    (%a0),%d4
    or.b     %d1,%d4
    move.b   %d4,(%a0)

    not.b    %d1
    and.b    (%a1),%d1
    or.b     %d3,%d1
    move.b   %d1,(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,5b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts
