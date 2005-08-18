| C prototype: void ClipSprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned short *sprt asm("%a1"),void *dest asm("%a0"));

.text
.globl ClipSprite16_OR_R
.even

ClipSprite16_OR_R:
    move.w   %d3,-(%sp)

    subq.w   #1,%d2		| %d2 = h - 1
    move.w   %d1,%d3		| %d3 = y
    bpl.s    9f	| h > 0 ?

    add.w    %d1,%d2		| %d2 = h + y
    bmi.s    0f		| y + h < 0 ?

    add.w    %d1,%d1		| %d1 = 2y
    suba.w   %d1,%a1		| sprt -= 2y
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

    andi.w   #15,%d0
    cmpi.w   #8,%d0

    bge.s    3f
    
1:
    moveq.l  #0,%d1
    move.w   (%a1)+,%d1
    swap     %d1
    lsr.l    %d0,%d1
    or.l     %d1,(%a0)
    
    lea      30(%a0),%a0
    dbf      %d2,1b

    move.w   (%sp)+,%d3
    rts

3:
    moveq    #16,%d1
    sub.w    %d0,%d1
2:
    moveq.l  #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)
    
    lea      30(%a0),%a0
    dbf      %d2,2b

0:
    move.w   (%sp)+,%d3
    rts

8:
    cmpi.w   #-16,%d0
    ble.s    0b		| x <= -16 ?
    neg.w    %d0		| shift = -x
    add.w    %d1,%d1		| %d1 = y*30
    adda.w   %d1,%a0		| dest += offset
4:
    move.w   (%a1)+,%d1
    lsl.w    %d0,%d1		| shifting
    or.w     %d1,(%a0)
    lea.l    30(%a0),%a0
    dbf      %d2,4b

    move.w   (%sp)+,%d3
    rts

7:
    cmpi.w   #239,%d0
    bhi.s    0b		| x > 239
    andi.w   #15,%d0		| shiftx = x & 15
    add.w    %d1,%d1		| %d1 = y*30
    lea.l    28(%a0,%d1.w),%a0
5:
    move.w   (%a1)+,%d1
    lsr.w    %d0,%d1
    or.w     %d1,(%a0)
    lea.l    30(%a0),%a0
    dbf      %d2,5b
    move.w   (%sp)+,%d3
    rts
