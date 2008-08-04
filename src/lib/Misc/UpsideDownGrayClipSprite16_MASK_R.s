| C prototype: void UpsideDownGrayClipSprite16_MASK_R(register short x asm("%d0"),register short y asm("%d1"),register unsigned short height asm("%d2"), unsigned short *sprt0, unsigned short *sprt1, unsigned short *mask0, unsigned short *mask1,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl UpsideDownGrayClipSprite16_MASK_R
.even

UpsideDownGrayClipSprite16_MASK_R:
    movem.l  %d3/%a2-%a5,-(%sp)

    lea.l    4+20(%sp),%a5
    movea.l  (%a5)+,%a2
    movea.l  (%a5)+,%a3
    movea.l  (%a5)+,%a4
    movea.l  (%a5),%a5

| Modify pointers.
    move.w   %d2,%d3
    add.w    %d3,%d3
    adda.w   %d3,%a2
    adda.w   %d3,%a3
    adda.w   %d3,%a4
    adda.w   %d3,%a5

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    adda.w   %d1,%a2		| sprt += 2y
    adda.w   %d1,%a3
    adda.w   %d1,%a4
    adda.w   %d1,%a5

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
    bhi.w    7f	| x > 239-15

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    andi.w   #15,%d0
    moveq.l  #16,%d1
    sub.w    %d0,%d1

1:
    move.l   (%a0),%d3
    moveq.l  #-1,%d0
    move.w   -(%a4),%d0
    rol.l    %d1,%d0
    and.l    %d0,%d3

    moveq.l  #0,%d0
    move.w   -(%a2),%d0
    lsl.l    %d1,%d0
    or.l     %d0,%d3
    move.l   %d3,(%a0)

    move.l   (%a1),%d3
    moveq.l  #-1,%d0
    move.w   -(%a5),%d0
    rol.l    %d1,%d0
    and.l    %d0,%d3

    moveq.l  #0,%d0
    move.w   -(%a3),%d0
    lsl.l    %d1,%d0
    or.l     %d0,%d3
    move.l   %d3,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3/%a2-%a5
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?

    neg.w    %d0		| shift = -x

    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

4:
    move.w   (%a0),%d3
    moveq.l  #-1,%d1
    move.w   -(%a4),%d1
    rol.l    %d0,%d1
    and.w    %d1,%d3

    move.w   -(%a2),%d1
    lsl.w    %d0,%d1		| shifting
    or.w     %d1,%d3
    move.w   %d3,(%a0)

    move.w   (%a1),%d3
    moveq.l  #-1,%d1
    move.w   -(%a5),%d1
    rol.l    %d0,%d1
    and.w    %d1,%d3

    move.w   -(%a3),%d1
    lsl.w    %d0,%d1
    or.w     %d1,%d3
    move.w   %d3,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,4b

    movem.l  (%sp)+,%d3/%a2-%a5
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
    move.w   (%a0),%d3
    moveq.l  #-1,%d1
    move.w   -(%a4),%d1
    asr.l    %d0,%d1
    and.w    %d1,%d3

    move.w   -(%a2),%d1
    lsr.w    %d0,%d1
    or.w     %d1,%d3
    move.w   %d3,(%a0)

    move.w   (%a1),%d3
    moveq.l  #-1,%d1
    move.w   -(%a5),%d1
    asr.l    %d0,%d1
    and.w    %d1,%d3

    move.w   -(%a3),%d1
    lsr.w    %d0,%d1
    or.w     %d1,%d3
    move.w   %d3,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,5b

    movem.l  (%sp)+,%d3/%a2-%a5
    rts
