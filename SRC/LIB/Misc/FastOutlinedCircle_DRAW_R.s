| C prototype: void FastOutlinedCircle_DRAW_R(register void *plane asm("%a0"),register unsigned short xcenter asm("%d0"),register unsigned short ycenter asm("%d1"),register unsigned short radius asm("%d2"));
|
| Routine based on Exploder's routine written in C, using EXT_SETPIX.
| Rewritten in plain assembly by Lionel, using an algorithm different from
| that of Exploder's routine.
| Bench on a circle of radius 25 drawn at (30;30), real 89 HW2 AMS 2.05,
| after PRG_SetStart(0xCE): ~26 ticks to draw 2500 circles, ~1930
| circles / sec, which is a >100% speed increase compared to the recompiled
| (to take advantage of the new EXT_SETPIX) and tweaked version of
| Exploder's routine, which draws ~930 circles / sec.
| The previous version contained a silly pessimization (4 separate bit
| numbers were maintained where 2 are enough), which made the routine 
| 20% slower and ~30 bytes bigger.

.text
.globl FastOutlinedCircle_DRAW_R
.even

FastOutlinedCircle_DRAW_R:
    movem.l  %d3-%d6/%a2-%a3,-(%sp)

    move.w   %d0,%d3 | xc
    lsr.w    #3,%d3 | byteoffset of xc from (0,yc)
    not.w    %d0
    andi.w   #7,%d0 | bit of xc.
    move.w   %d0,%d6 | save the bit number

    add.w    %d1,%d1 | yc
    move.w   %d1,%d4
    lsl.w    #4,%d4
    sub.w    %d1,%d4 | d4 = byteoffset of (0,yc) from (0,0)

    add.w    %d3,%d4 | d4 = byteoffset of (xc,yc) from (0,0)
    adda.w   %d4,%a0
    move.l   %a0,%a1
    move.l   %a1,%a2
    move.l   %a2,%a3


    move.w   %d2,%d1 | y = r
    clr.w    %d0 | x = 0
    moveq    #1,%d2
    sub.w    %d1,%d2
    add.w    %d2,%d2 | d = 2 * (1 - r) = 2 * (1 - y) at the beginning.

    move.w   %d1,%d3
    add.w    %d3,%d3
    move.w   %d3,%d5
    lsl.w    #4,%d5
    sub.w    %d3,%d5 | d5 = byteoffset of (0,y) from (0,0)

    suba.w   %d5,%a0
    suba.w   %d5,%a1
    adda.w   %d5,%a2
    adda.w   %d5,%a3

    move.w   %d6,%d5
| d3, d4: scratch.

    moveq    #30,%d4

0:
| bclr if you want A_REVERSE mode, bchg if you want A_XOR mode.
    bset     %d5,(%a0)
    bset     %d6,(%a1)
    bset     %d5,(%a2)
    bset     %d6,(%a3)

| if(d + y > 0) {
    move.w   %d2,%d3
    add.w    %d1,%d3
    ble.s    3f
| Short branches are faster if not taken.

    subq.w   #1,%d1 | y--
    sub.w    %d1,%d2
    sub.w    %d1,%d2
    addq.w   #1,%d2 | d -= (y * 2) - 1.

    adda.w   %d4,%a0
    adda.w   %d4,%a1
    suba.w   %d4,%a2
    suba.w   %d4,%a3

3:
| if(x > d) {
    cmp.w    %d0,%d2
    bge.s    1f
| Short branches are faster if not taken.

    addq.w   #1,%d0 | x++
    add.w    %d0,%d2
    add.w    %d0,%d2
    addq.w   #1,%d2 | d += (x * 2) + 1;

    addq.w   #1,%d5
    cmpi.w   #7,%d5
    bls.s    2f
    subq.l   #1,%a0
    subq.l   #1,%a2
    moveq    #0,%d5

2:
    subq.w   #1,%d6
    bge.s    1f
    addq.l   #1,%a1
    addq.l   #1,%a3
    moveq    #7,%d6

1:
    tst.w    %d1
    bge.s    0b


    movem.l  (%sp)+,%d3-%d6/%a2-%a3
    rts
