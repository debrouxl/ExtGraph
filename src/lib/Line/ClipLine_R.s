| C prototype: void * ClipLine_R(short x1 asm("%d0"), short y1 asm("%d1"), short x2 asm("%d2"), short y2 asm("%d3"), short *clippedcoord asm("%a1")) __attribute__((__regparm__));
| In assembly, you can use _ClipLine_R, which returns the clipped coordinates in d0-d3.
| Upon return, a0 = 0 if there is nothing to draw.
|
| Based on a routine found in OurWorld, slightly modified by Lionel Debroux.

| Agreed, this is how ExtGraph should have been written: symbolic constant definitions, macros...
| Julien started doing it for the new X8 routines.
.set _EXT_MAX_LCD_WIDTH, 240 | Number of columns of the video screen
.set _EXT_MAX_LCD_HEIGHT, 128 | Number of rows of the video screen.

.text
.globl ClipLine_R
.globl _ClipLine_R
.even

ClipLine_R:
    move.l   %d3,-(%sp)
    bsr.s    _ClipLine_R
    movem.w  %d0-%d3,(%a1)
    move.l   (%sp)+,%d3
    rts

_ClipLine_R:
    movem.l  %d4-%d7,-(%sp)
    moveq    #1,%d4
    movea.l  %d4,%a0

| This is the Cohen-Sutherland line clipping algorithm. First, we try and trivially reject.
    bsr.s    3f
    exg.l    %d0,%d2
    exg.l    %d1,%d3
    exg.l    %d4,%d5
    bsr.s    3f
    exg.l    %d0,%d2
    exg.l    %d1,%d3
    exg.l    %d4,%d5

1:
    move.l   %d4,%d6
    and.l    %d5,%d6
    jbne     0f
    tst.l    %d4
    jbne     10f
    tst.l    %d5
    jbeq     2f
    exg.l    %d0,%d2
    exg.l    %d1,%d3
    exg.l    %d4,%d5

10:
    tst.b    %d4
    jbeq     10f
    move.w   %d3,%d6
    sub.w    %d1,%d6
    move.w   %d0,%d7
    subi.w   #_EXT_MAX_LCD_WIDTH-1,%d7
    muls.w   %d7,%d6
    sub.w    %d2,%d0
    jbeq     0f
    divs.w   %d0,%d6
    add.w    %d6,%d1
    move.w   #_EXT_MAX_LCD_WIDTH-1,%d0
    jbsr     3f
    jbra     1b

| Get the Cohen-Sutherland clipping algorithm code for (d0,d1) into d3
3:
    tst.w    %d1
    smi.b    %d4
    move.b   %d4,-(%sp)
    move.w   (%sp)+,%d4
|    lsl.w    #8,%d4
    cmpi.w   #_EXT_MAX_LCD_HEIGHT,%d1
    sge.b    %d4
    swap.w   %d4
    tst.w    %d0
    smi.b    %d4
    move.b   %d4,-(%sp)
    move.w   (%sp)+,%d4
|    lsl.w    #8,%d4
    cmpi.w   #_EXT_MAX_LCD_WIDTH,%d0
    sge.b    %d4
    rts

10:
    tst.w    %d4
    jbpl     10f
    move.w   %d3,%d6
    sub.w    %d1,%d6
    muls.w   %d0,%d6
    sub.w    %d2,%d0
    jbeq     0f
    divs.w   %d0,%d6
    add.w    %d6,%d1
    clr.w    %d0
    jbsr     3b
    jbra     1b

10:
    tst.l    %d4
    jbpl     10f
    move.w   %d2,%d6
    sub.w    %d0,%d6
    muls.w   %d1,%d6
    sub.w    %d3,%d1
    jbeq     0f
    divs.w   %d1,%d6
    add.w    %d6,%d0
    clr.w    %d1
    jbsr     3b
    jbra     1b

10:
    move.w   %d2,%d6
    sub.w    %d0,%d6
    move.w   %d1,%d7
    subi.w   #_EXT_MAX_LCD_HEIGHT-1,%d7
    muls.w   %d7,%d6
    sub.w    %d3,%d1
    jbeq     0f
    divs.w   %d1,%d6
    add.w    %d6,%d0
    move.w   #_EXT_MAX_LCD_HEIGHT-1,%d1
    jbsr     3b
    jbra     1b

0:
| Return failure (nothing to draw).
    suba.l   %a0,%a0
2:
| Ready to draw line.
    movem.l  (%sp)+,%d4-%d7
    rts
