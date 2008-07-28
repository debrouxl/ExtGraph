| C prototype: void GrayClipISprite32_BLIT_R(short x asm("%d0"), short y asm("%d1"), unsigned short h asm("%d2"), const unsigned long *sprite, const unsigned long maskval asm("%d3"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayClipISprite32_BLIT_R
.even

7:
    cmpi.w   #239,%d0
    bhi.s    0f		| x > 239

    add.w    %d1,%d1		| %d1 = y*30
    addi.w   #26,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

    subi.w   #208,%d0

    lsr.l    %d0,%d6
    moveq.l  #-1,%d7
    lsr.l    %d0,%d7
    not.l    %d7
    or.l     %d7,%d6
5:
    move.l   (%a2)+,%d1
    lsr.l    %d0,%d1
    and.l    %d6,(%a0)
    or.l     %d1,(%a0)

    move.l   (%a2)+,%d1
    lsr.l    %d0,%d1
    and.l    %d6,(%a1)
    or.l     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,5b

0:
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

GrayClipISprite32_BLIT_R:
    movem.l  %d3-%d7/%a2,-(%sp)

    move.l   4+24(%sp),%a2
    move.l   %d3,%d6

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = y + h
    bmi.s    0b		| y + h < 0 ?

    lsl.w    #3,%d1		| %d1 = 8y
    suba.w   %d1,%a2		| sprite -= 8y
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
    bhi.s    7b	| x > 239-32

    lsr.w    #4,%d3		| %d3 = x/16
    add.w    %d3,%d1		| %d3 = x/16 + y*15
    add.w    %d1,%d1		| %d3 = x/8 + y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1
    moveq.l  #16,%d1
    andi.w   #15,%d0		| %d0 = righshift
    sub.w    %d0,%d1		| %d1 = 16 - (x & 15)

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.l   %d3,%d4
    not.l    %d4

    rol.l    %d1,%d6
    move.w   %d6,%d7
    or.l     %d4,%d6
    or.w     %d3,%d7

1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    and.w    %d4,%d5
    and.w    %d7,(%a0)
    or.w     %d5,(%a0)+
    and.l    %d6,(%a0)
    or.l     %d0,(%a0)

    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    and.w    %d4,%d5
    and.w    %d7,(%a1)
    or.w     %d5,(%a1)+
    and.l    %d6,(%a1)
    or.l     %d0,(%a1)

    lea.l    28(%a0),%a0
    lea.l    28(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

8:
    cmpi.w   #-32,%d0
    ble.s    0b		| x <= -32 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
    adda.w   %d1,%a1

    rol.l    %d0,%d6
    moveq.l  #-1,%d7
    lsl.l    %d0,%d7
    not.l    %d7
    or.l     %d7,%d6
4:
    move.l   (%a2)+,%d1
    lsl.l    %d0,%d1		| shifting
    and.l    %d6,(%a0)
    or.l     %d1,(%a0)

    move.l   (%a2)+,%d1
    lsl.l    %d0,%d1		| shifting
    and.l    %d6,(%a1)
    or.l     %d1,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,4b

    movem.l  (%sp)+,%d3-%d7/%a2
    rts
