| C prototype: short TestCollide162h_R(register short x0 asm("%d0"),register short y0 asm("%d1"),register short x1 asm("%d2"),register short y1 asm("%d3"),short height0,short height1,register unsigned short* data0 asm("%a0"),register unsigned short* data1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl TestCollide162h_R
.even

TestCollide162h_R:
    movem.l  %d3-%d5,-(%sp)
    
    move.w   4+12(%sp),%d4
    move.w   4+12+2(%sp),%d5

    sub.w    %d0,%d2 | dx
    bge.s    9f
    | If sprite 0 is right of sprite 1 just exchange
    | all necessary variables so we can still assume
    | sprite 0 is left of sprite 1 ...
    neg.w    %d2
    exg      %a0,%a1
    exg      %d1,%d3
    exg      %d4,%d5
9:
    cmpi.w   #16,%d2 | dx
    bge.s    0f | cannot overlap in this case (x difference too large)

| Here:
| d0: scratch.
| d1: y of leftmost sprite (y0).
| d2: dx (shift count).
| d3: y of rightmost sprite (y1).
| d4: height of leftmost sprite (h0).
| d5: height of rightmost sprite (h1).
| a0: pointer to leftmost sprite (s0).
| a1: pointer to rightmost sprite (s1).
| cc: flags indicate the sign of dy.
    
    move.w   %d3,%d0
    sub.w    %d1,%d0 | d0 = dy.

    add.w    %d0,%d0 | Sprite is words, not bytes.

    bgt.s    5f
6:
| Auxiliary variable: y1 + h1 -> d5.
    add.w    %d3,%d5

| y1 + h1 >= y0 ?
    sub.w    %d1,%d5 | y1 + h1 -= y0.
    blt.s    0f | No -> no overlap.
    
    cmp.w    %d5,%d4
    bge.s    4f | >= 0: overlapping zone's height is y1 + h1 - y0 pixels (already in d5).

| < 0: overlapping zone's height is h0 pixels (put it in d5).
    move.w   %d4,%d5
4:

    tst.w    %d0
    bgt.s    7f
| Top of sprite 1 is above top of sprite 0.
    suba.w   %d0,%a1 | d0 is negative.
8:

| Offset s1: add dy to it.
    subq.w   #1,%d5 | for the dbf
    blt.s    0f | -1 or less: no overlap.

| Core of routine.
    moveq    #0,%d1
3:
    move.w   (%a1)+,%d1 | (unsigned long)*data1
    moveq    #0,%d3
    move.w   (%a0)+,%d3
    lsl.l    %d2,%d3 | ((unsigned long)*data0) << dx
    and.l    %d1,%d3
    dbne     %d5,3b | Good old decrement and branch

    move.l   %d3,%d1 | Why did we come here (speed optimization from tst.l %d3) ?
| If d1 != 0, there's a collision, therefore return non-zero (0 otherwise).
    sne      %d0
    ext.w    %d0
1:
    movem.l  (%sp)+,%d3-%d5
    rts
0:
    moveq    #0,%d0
    bra.s    1b

5:
| The problem is symmetric: swap parameters and branch to common code (size optimization which saves
| more space than it slows down, in percentage).
    exg      %d1,%d3 | y0, y1
    exg      %d4,%d5 | h0, h1
    bra.s    6b

7:
    adda.w   %d0,%a0
    bra.s    8b
