| C prototype: void GrayClipSprite16_TRANB_R(short x asm("%d0"), short y asm("%d1"), unsigned short h asm("%d2"), const unsigned short *sprt0, const unsigned short *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayClipSprite16_TRANB_R
.even

GrayClipSprite16_TRANB_R:
    movem.l  %d3-%d4/%a2-%a3,-(%sp)

    move.l   4+16(%sp),%a2
    move.l   4+16+4(%sp),%a3
    
    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a2		| sprt -= 2y
    suba.w   %d1,%a3

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
    moveq.l  #-1,%d0
    move.w   (%a2)+,%d0
    rol.l    %d1,%d0

    moveq.l  #-1,%d3
    move.w   (%a3)+,%d3
    rol.l    %d1,%d3

    move.l   %d3,%d4
    not.l    %d4
    or.l     (%a0),%d4
    and.l    %d0,%d4
    move.l   %d4,(%a0)

    not.l    %d0
    or.l     (%a1),%d0
    and.l    %d3,%d0
    move.l   %d0,(%a1)

    lea      30(%a0),%a0
    lea      30(%a1),%a1

    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?

    neg.w    %d0		| shift = -x

    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

2:
    moveq    #-1,%d1
    move.w   (%a2)+,%d1
    rol.l    %d0,%d1		| shifting

    moveq    #-1,%d3
    move.w   (%a3)+,%d3
    rol.l    %d0,%d3

    move.w   %d3,%d4
    not.w    %d4
    or.w     (%a0),%d4
    and.w    %d1,%d4
    move.w   %d4,(%a0)

    not.w    %d1
    or.w     (%a1),%d1
    and.w    %d3,%d1
    move.w   %d1,(%a1)

    lea      30(%a0),%a0
    lea      30(%a1),%a1

    dbf      %d2,2b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239

    andi.w   #15,%d0		| shiftx = x & 15

    add.w    %d1,%d1		| %d1 = y*30
    addi.w   #28,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

3:
    moveq    #-1,%d1
    move.w   (%a2)+,%d1
    ror.l    %d0,%d1

    moveq    #-1,%d3
    move.w   (%a3)+,%d3
    ror.l    %d0,%d3

    move.w   %d3,%d4
    not.w    %d4
    or.w     (%a0),%d4
    and.w    %d1,%d4
    move.w   %d4,(%a0)

    not.w    %d1
    or.w     (%a1),%d1
    and.w    %d3,%d1
    move.w   %d1,(%a1)

    lea      30(%a0),%a0
    lea      30(%a1),%a1

    dbf      %d2,3b

    movem.l  (%sp)+,%d3-%d4/%a2-%a3
    rts
