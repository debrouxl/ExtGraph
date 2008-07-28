| C prototype: void GrayClipSprite16_SMASK_R(short x asm("%d0"), short y asm("%d1"), unsigned short h asm("%d2"), const unsigned short *sprt0, const unsigned short *sprt1, const unsigned short *mask, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayClipSprite16_SMASK_R
.even

GrayClipSprite16_SMASK_R:
    movem.l  %d3/%a2-%a4,-(%sp)

    lea.l    4+16(%sp),%a4
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
    move.w   %d0,%d3		| %d3 = x
    ble.s    8f	| x < 0 ?
    cmpi.w   #239-16,%d0
    bhi.s    7f	| x > 239-15

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    andi.w   #15,%d0
    moveq.l  #16,%d1
    sub.w    %d0,%d1

1:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    rol.l    %d1,%d3

    moveq.l  #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    moveq.l  #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3/%a2-%a4
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?

    neg.w    %d0		| shift = -x

    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

4:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    rol.l    %d0,%d3

    moveq    #0,%d1
    move.w   (%a2)+,%d1
    lsl.w    %d0,%d1		| shifting
    and.w    %d3,(%a0)
    or.w     %d1,(%a0)

    move.w   (%a3)+,%d1
    lsl.w    %d0,%d1		| shifting
    and.w    %d3,(%a1)
    or.w     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,4b

    movem.l  (%sp)+,%d3/%a2-%a4
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239

    andi.w   #15,%d0		| shiftx = x & 15

    add.w    %d1,%d1		| %d1 = y*30
    addi.w   #28,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

5:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    asr.l    %d0,%d3

    moveq    #0,%d1
    move.w   (%a2)+,%d1
    lsr.w    %d0,%d1		| shifting
    and.w    %d3,(%a0)
    or.w     %d1,(%a0)

    move.w   (%a3)+,%d1
    lsr.w    %d0,%d1		| shifting
    and.w    %d3,(%a1)
    or.w     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,5b

    movem.l  (%sp)+,%d3/%a2-%a4
    rts
