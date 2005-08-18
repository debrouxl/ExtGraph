| Modified from FastDrawLine_R and FastDrawVLine_R.
|
| C prototype: void GrayFastDrawLine2B_R (void* plane0 asm("%a0"),void* plane1 asm("%a1"),unsigned short x1 asm("%d0"),unsigned short y1 asm("%d1"),unsigned short x2 asm("%d2"),unsigned short y2 asm("%d3"),unsigned short color) __attribute__ ((__stkparm__));

.text
.globl GrayFastDrawLine2B_R
.even

GrayFastDrawLine2B_R:
    movem.l  %d3/%d4/%d6/%d7/%a2,-(%sp)
    cmp.w    %d0,%d2
    bhi.s    0f
    exg      %d0,%d2
    exg      %d1,%d3
0:		                            | -> dx will be positive.
    move.w   (4+5*4)(%sp),%d4               | mode

| Self-modifying code.
    moveq    #-0x70,%d6                     | bclr (%a0)
    lsr.w    #1,%d4
    bcc.s    10f
    moveq    #-0x30,%d6
10:
    moveq    #-0x6F,%d7                     | bclr (%a1)
    lsr.w    #1,%d4
    bcc.s    10f
    moveq    #-0x2F,%d7
10:
| Patch the routine. This is simpler than in the B/W version, due to a different algorithm.
    lea      2f+1(%pc),%a2
    move.b   %d6,(%a2)
    move.b   %d7,2(%a2)
    move.b   %d6,6f-2f(%a2)
    move.b   %d7,6f-2f+2(%a2)

| Find the mask and the address of the leftmost point.
    move.w   %d1,%d4
    add.w    %d4,%d4
    move.w   %d4,%d6                        | y1*2
    lsl.w    #4,%d4                         | y1*32
    sub.w    %d6,%d4                        | y1*30
    move.w   %d0,%d6
    lsr.w    #3,%d6
    add.w    %d6,%d4
    adda.w   %d4,%a0                        | addr in plane0
    adda.w   %d4,%a1                        | addr in plane1

| Find the bit number.
    move.w   %d0,%d6
    not.w    %d6
    andi.b   #7,%d6                         | bit number

    moveq    #30,%d4                        | Y++ (next line).

| Calculate dx and dy.
    sub.w    %d0,%d2                        | dx = x2-x1
    sub.w    %d1,%d3                        | dy = y2-y1
| Check if the line is going up or down and patch the code accordingly.
    bpl.s    10f
    neg.w    %d3                            | -> so as to have dy>=0.
    neg.w    %d4                            | Y-- (previous line).

10:
    cmp.w    %d3,%d2
    bls.s    3f                             | if dy >= dx
| When there is only one point to draw, dx=dy -> see ScanY
| Calculate the index for the dbf and calculate P(0)
    move.w   %d2,%d0
    move.w   %d2,%d1
    lsr.w    #1,%d1                         | dx/2
    sub.w    %d2,%d1                        | P(0) = dx/2-dx = -dx/2

| Now we have :
| d0.w : dbf counter.
| d1.w : P, test function.
| d2.w : dx.
| d3.w : dy.
| d4.w : 30 or -30, if the line goes up or goes down (delta_y).
| d6.b : bit number for the left point (X1,Y1).
| a0.l : address of the left point in plane0.
| a1.l : address of the left point in plane1.

2:
    bset.b   %d6,(%a0)                      | PutPxl, plane0.
    bset.b   %d6,(%a1)                      | PutPxl, plane1.
    subq.b   #1,%d6
    bge.s    4f
    addq.w   #1,%a0
    addq.w   #1,%a1
    moveq    #7,%d6
4:
    add.w    %d3,%d1                        |P+=dy
    bmi.s    5f                             |if P < 0
    sub.w    %d2,%d1                        |P-=dx
    add.w    %d4,%a0                        |Y1++ (or --)
    add.w    %d4,%a1                        |Y2++ (or --)
5:
    dbf      %d0,2b
0:
    movem.l  (%sp)+,%d3/%d4/%d6/%d7/%a2
    rts

3:                  | The roles of dx and dy are swapped.
    move.w   %d3,%d0
    move.w   %d3,%d1
    lsr.w    #1,%d1
    sub.w    %d3,%d1                        |P(0) = dy/2-dy = -dy/2

6:
    bset.b   %d6,(%a0)                      | PutPxl, plane0.
    bset.b   %d6,(%a1)                      | PutPxl, plane1.
    adda.w   %d4,%a0
    adda.w   %d4,%a1
    add.w    %d2,%d1                        | P+=dx
    bmi.s    5f                             | if P < 0
    sub.w    %d3,%d1                        | P-=dy
4:
    subq.b   #1,%d6
    bge.s    5f
    addq.w   #1,%a0                         | X1++
    addq.w   #1,%a1                         | X2++
    moveq    #7,%d6
5:
    dbf      %d0,6b
    bra.s    0b

.even
