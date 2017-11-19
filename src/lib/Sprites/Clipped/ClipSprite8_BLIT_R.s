| C prototype: void ClipSprite8_BLIT_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt asm("%a1"), const unsigned char maskval asm("%d3"), void *dest asm("%a0"));

.text
.globl ClipSprite8_BLIT_R
.even

ClipSprite8_BLIT_R:
    move.l   %d3,-(%sp)

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    suba.w   %d1,%a1		| sprt -= y
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
    cmpi.w   #PLANE_PIXEL_WIDTH-1-8,%d0
    bhi.s    7f	| x > PLANE_PIXEL_WIDTH-1-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*PLANE_BYTE_WIDTH/2
    add.w    %d1,%d1		| %d3 = x/8 + y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset

    moveq.l  #-1,%d3
    move.b   3(%sp),%d3

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1

    swap     %d3
    ror.l    %d1,%d3
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b

0:
    move.l   (%sp)+,%d3
    rts

3:
    rol.w    %d1,%d3
2:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)

    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,2b
0:
    move.l   (%sp)+,%d3
    rts

8:
    cmpi.w   #-8,%d0
    ble.s    0b		| x <= -8 ?

    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    adda.w   %d1,%a0		| dest += offset

    moveq.l  #-1,%d3
    move.b   3(%sp),%d3
    rol.w    %d0,%d3

4:
    move.b   (%a1)+,%d1
    lsl.b    %d0,%d1		| shifting
    and.b    %d3,(%a0)
    or.b     %d1,(%a0)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,4b

    move.l   (%sp)+,%d3
    rts

7:
    cmpi.w   #PLANE_PIXEL_WIDTH-1,%d0
    bhi.s    0b		| x > PLANE_PIXEL_WIDTH-1

    andi.w   #7,%d0		| shiftx = x & 7
    add.w    %d1,%d1		| %d1 = y*PLANE_BYTE_WIDTH
    lea.l    PLANE_BYTE_WIDTH-1(%a0,%d1.w),%a0

    moveq.l  #-1,%d3
    move.b   3(%sp),%d3
    ror.w    %d0,%d3

5:
    move.b   (%a1)+,%d1
    lsr.b    %d0,%d1
    and.b    %d3,(%a0)
    or.b     %d1,(%a0)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,5b

    move.l   (%sp)+,%d3
    rts
