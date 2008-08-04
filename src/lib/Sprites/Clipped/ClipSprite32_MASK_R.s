| C prototype: void ClipSprite32_MASK_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d2"), const unsigned long *sprt asm("%a1"), const unsigned long *mask, void *dest asm("%a0")) __attribute__((__stkparm__));

.text
.globl ClipSprite32_MASK_R
.even

ClipSprite32_MASK_R:
    move.l   %d3,-(%sp)
    move.l   %a2,-(%sp)
    
    move.l   4+8(%sp),%a2

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = y + h
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2*y
    add.w    %d1,%d1		| %d1 = 4*y
    suba.w   %d1,%a1		| sprt -= 4*y
    suba.w   %d1,%a2		| mask -= 4*y
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
    cmpi.w   #239-32,%d0
    bhi.s    7f	| x > 239-32

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    moveq.l  #16,%d1
    andi.w   #15,%d0		| %d0 = righshift
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)
    move.w   %d4,-(%sp)

1:
    move.l   (%a2)+,%d3
    not.l    %d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    not.l    %d3
    and.l    %d3,(%a0)
    lsl.w    %d1,%d4
    not.w    %d4
    and.w    %d4,4(%a0)

    move.l   (%a1)+,%d3
    move.w   %d3,%d4
    lsr.l    %d0,%d3
    lsl.w    %d1,%d4
    or.l     %d3,(%a0)+
    or.w     %d4,(%a0)

    lea.l    26(%a0),%a0
    dbf      %d2,1b

    move.w   (%sp)+,%d4
0:
    movea.l  (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts
8:
    cmpi.w   #-32,%d0
    ble.s    0b		| x <= -32 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
4:
    move.l   (%a2)+,%d1
    not.l    %d1
    lsl.l    %d0,%d1
    not.l    %d1
    and.l    %d1,(%a0)

    move.l   (%a1)+,%d1
    lsl.l    %d0,%d1		| shifting
    or.l     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,4b
    movea.l  (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239
    add.w    %d1,%d1		| %d1 = y*30
    lea.l    26(%a0,%d1.w),%a0
    subi.w   #208,%d0		| shiftx
5:
    move.l   (%a2)+,%d1
    not.l    %d1
    lsr.l    %d0,%d1
    not.l    %d1
    and.l    %d1,(%a0)

    move.l   (%a1)+,%d1
    lsr.l    %d0,%d1
    or.l     %d1,(%a0)

    lea.l    30(%a0),%a0
    dbf      %d2,5b

    movea.l  (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts
