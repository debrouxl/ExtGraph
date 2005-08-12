| C prototype: void ClipSprite8_OR_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),register void *dest asm("%a0"));

.text
.globl ClipSprite8_OR_R
.even

ClipSprite8_OR_R:
    move.w   %d3,-(%sp)

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
    bhi.s    7f	| x > 239-8

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a0)

    lea      30(%a0),%a0
    dbf      %d2,1b

    move.w   (%sp)+,%d3
    rts

2:
    lea      30(%a0),%a0
3:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)

    dbf      %d2,2b

0:
    move.w   (%sp)+,%d3
    rts

8:
    cmpi.w   #-8,%d0
    ble.s    0b		| x <= -8 ?

    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset

4:
    move.b   (%a1)+,%d1
    lsl.b    %d0,%d1		| shifting
    or.b     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,4b

    move.w   (%sp)+,%d3
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239

    andi.w   #7,%d0		| shiftx = x & 7
    add.w    %d1,%d1		| %d1 = y*30
    lea.l    29(%a0,%d1.w),%a0
5:
    move.b   (%a1)+,%d1
    lsr.b    %d0,%d1
    or.b     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,5b

    move.w   (%sp)+,%d3
    rts
