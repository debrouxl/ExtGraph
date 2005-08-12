| C prototype: void GrayClipISprite8_TRANB_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned char *sprite,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayClipISprite8_TRANB_R
.even

2:
    lea      30(%a0),%a0
    lea      30(%a1),%a1
3:
    moveq    #-1,%d0
    move.b   (%a2)+,%d0
    rol.w    %d1,%d0

    moveq    #-1,%d3
    move.b   (%a2)+,%d3
    rol.w    %d1,%d3

    move.w   %d3,%d4
    not.w    %d4
    or.w     (%a0),%d4
    and.w    %d0,%d4
    move.w   %d4,(%a0)

    not.w    %d0
    or.w     (%a1),%d0
    and.w    %d3,%d0
    move.w   %d0,(%a1)

    dbf      %d2,2b

    movem.l  (%sp)+,%d3-%d4/%a2
    rts

GrayClipISprite8_TRANB_R:
    movem.l  %d3-%d4/%a2,-(%sp)

    move.l   4+12(%sp),%a2

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
    cmpi.w   #239-8,%d0
    bhi.w    7f	| x > 239-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.w    3b

    neg.w    %d1
1:
    moveq    #-1,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    ror.l    %d1,%d0

    moveq.l  #-1,%d3
    move.b   (%a2)+,%d3
    swap.w   %d3
    ror.l    %d1,%d3

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
    movem.l  (%sp)+,%d3-%d4/%a2
    rts

8:
    cmpi.w   #-8,%d0
    ble.s    0b		| x <= -8 ?

    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

4:
    moveq    #-1,%d1
    move.b   (%a2)+,%d1
    rol.w    %d0,%d1		| shifting

    moveq    #-1,%d3
    move.b   (%a2)+,%d3
    rol.w    %d0,%d3		| shifting

    move.b   %d3,%d4
    not.b    %d4
    or.b     (%a0),%d4
    and.b    %d1,%d4
    move.b   %d4,(%a0)

    not.b    %d1
    or.b     (%a1),%d1
    and.b    %d3,%d1
    move.b   %d1,(%a1)

    lea      30(%a0),%a0
    lea      30(%a1),%a1
    dbf      %d2,4b

    movem.l  (%sp)+,%d3-%d4/%a2
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239

    andi.w   #7,%d0		| shiftx = x & 7
    add.w    %d1,%d1		| %d1 = y*30
    addi.w   #29,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

5:
    moveq    #-1,%d1
    move.b   (%a2)+,%d1
    ror.w    %d0,%d1

    moveq    #-1,%d3
    move.b   (%a2)+,%d3
    ror.w    %d0,%d3

    move.b   %d3,%d4
    not.b    %d4
    or.b     (%a0),%d4
    and.b    %d1,%d4
    move.b   %d4,(%a0)

    not.b    %d1
    or.b     (%a1),%d1
    and.b    %d3,%d1
    move.b   %d1,(%a1)

    lea      30(%a0),%a0
    lea      30(%a1),%a1
    dbf      %d2,5b

    movem.l  (%sp)+,%d3-%d4/%a2
    rts
