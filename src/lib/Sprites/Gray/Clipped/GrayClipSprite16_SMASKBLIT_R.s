| C prototype: void GrayClipSprite16_SMASKBLIT_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), unsigned short *sprt0, unsigned short *sprt1, unsigned short *mask, const unsigned short maskval asm("%d3"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayClipSprite16_SMASKBLIT_R
.even

GrayClipSprite16_SMASKBLIT_R:
    movem.l  %d3-%d5/%a2-%a4,-(%sp)

    | BLIT treatment: illustration sent by Super Mario 3 68k author
    | shows that blitmask and one's complement of bitmask are necessary.
    |
    | Unlike in most other routines, it is factored
    | here because we need 6 registers in the loop anyway.
    moveq.l  #-1,%d4
    move.w   %d3,%d4
    move.l   %d4,%d5
    not.w    %d5

    lea.l    4+24(%sp),%a4
    movea.l  (%a4)+,%a2
    movea.l  (%a4)+,%a3
    movea.l  (%a4),%a4

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a2		| sprt -= 2y
    suba.w   %d1,%a3
    suba.w   %d1,%a4

    moveq.l  #0,%d1		| offsety = 0
    bra.s    10f

9:
    add.w    %d2,%d3		| %d3 = h + y
    subi.w   #127,%d3		| %d3 = h + y - 127
    ble.s    6f			| h + y - 127 <= 0 ?
    sub.w    %d3,%d2		| h -= h + y - 127 (h = 127-y)
    bmi.s    0f

6:
    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1		| %d1 = y*15

10:
    move.w   %d0,%d3		| %d4 = x
    ble    8f	| x < 0 ?
    cmpi.w   #239-16,%d0
    bhi    7f	| x > 239-15

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d1 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    andi.w   #15,%d0
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    rol.l    %d1,%d4
    rol.l    %d1,%d5

1:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    rol.l    %d1,%d3
    or.l     %d5,%d3 | 1's complement of bitmask.

    moveq.l  #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    and.l    %d4,%d0 | bitmask.
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    moveq.l  #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    and.l    %d4,%d0 | bitmask.
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3-%d5/%a2-%a4
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?

    neg.w    %d0		| shift = -x

    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    rol.l    %d0,%d4
    rol.l    %d0,%d5

4:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    rol.l    %d0,%d3
    or.w     %d5,%d3 | 1's complement of bitmask.

    moveq    #0,%d1
    move.w   (%a2)+,%d1
    lsl.w    %d0,%d1		| shifting
    and.w    %d4,%d1 | bitmask.
    and.w    %d3,(%a0)
    or.w     %d1,(%a0)

    move.w   (%a3)+,%d1
    lsl.w    %d0,%d1		| shifting
    and.w    %d4,%d1 | bitmask.
    and.w    %d3,(%a1)
    or.w     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,4b

    movem.l  (%sp)+,%d3-%d5/%a2-%a4
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239

    andi.w   #15,%d0		| shiftx = x & 15

    add.w    %d1,%d1		| %d1 = y*30
    addi.w   #28,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

    asr.l    %d0,%d4
    asr.l    %d0,%d5

5:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    asr.l    %d0,%d3
    or.w     %d5,%d3 | 1's complement of bitmask.

    moveq    #0,%d1
    move.w   (%a2)+,%d1
    lsr.w    %d0,%d1		| shifting
    and.w    %d4,%d1 | bitmask.
    and.w    %d3,(%a0)
    or.w     %d1,(%a0)

    move.w   (%a3)+,%d1
    lsr.w    %d0,%d1		| shifting
    and.w    %d4,%d1 | bitmask.
    and.w    %d3,(%a1)
    or.w     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,5b

    movem.l  (%sp)+,%d3-%d5/%a2-%a4
    rts
