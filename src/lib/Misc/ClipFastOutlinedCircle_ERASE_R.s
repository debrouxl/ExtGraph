| C prototype: void ClipFastOutlinedCircle_ERASE_R(void *plane asm("%a0"),unsigned short xcenter asm("%d0"),unsigned short ycenter asm("%d1"),unsigned short radius asm("%d2"));
|
| Routine based on Exploder's routine written in C, using EXT_SETPIX.
| Rewritten in plain assembly by Lionel, using an algorithm different from
| that of Exploder's routine.
| Bench on a circle of radius 25 drawn at (30;30), real 89 HW2 AMS 2.05, 
| PRG_getStart() = 0xCE: 45 ticks to draw 2000 circles, ~1100 circles / sec.

| Agreed, this is how ExtGraph should have been written: symbolic constant definitions, macros...
| Julien started doing it for the new X8 routines.
.set _EXT_MAX_LCD_WIDTH, 239 | Number of columns of the video screen
.set _EXT_MAX_LCD_HEIGHT, 127 | Number of rows of the video screen.

.text
.globl ClipFastOutlinedCircle_ERASE_R
.even

ClipFastOutlinedCircle_ERASE_R:
    movem.l  %d3-%d7/%a2-%a5,-(%sp)

| Simple check for "completely out of plane".
    moveq    #_EXT_MAX_LCD_HEIGHT,%d3
    add.w    %d2,%d3
    cmp.w    %d3,%d1
    bge.w    8f
    
    addi.w   #_EXT_MAX_LCD_WIDTH-_EXT_MAX_LCD_HEIGHT,%d3
    cmp.w    %d3,%d0
    bge.w    8f

    move.w   %d0,%d3
    move.w   %d3,%d4
    lsr.w    #3,%d3
    not.w    %d4
    andi.w   #7,%d4
    move.w   %d4,%d6
| d0: xc.
| d1: yc.
| d2: r.
| d3: byteoffset of xc from (0,yc).
| d6: bit number corresponding to xc.

    move.w   %d1,%d5
    add.w    %d5,%d5
    move.w   %d5,%d4
    lsl.w    #4,%d4
    sub.w    %d5,%d4
| d0: xc.
| d1: yc.
| d2: r.
| d3: byteoffset of xc from (0,yc).
| d4: byteoffset of (0,yc) from (0,0).
| d6: bit number corresponding to xc.

    add.w    %d3,%d4
    adda.w   %d4,%a0
    move.l   %a0,%a1
    move.l   %a1,%a2
    move.l   %a2,%a3
| d0: xc.
| d1: yc.
| d2: r.
| d4: byteoffset of (xc,yc) from (0,0).
| d6: bit number corresponding to xc.
| a0-a3: pointers to the pixels (not fully computed).

    move.w   %d2,%d5
    suba.l   %a4,%a4
    moveq    #1,%d4
    sub.w    %d2,%d4
    add.w    %d4,%d4
| d0: xc.
| d1: yc.
| d2: r.
| d4: variable d = 2 * (1 - r) at the beginning.
| d6: bit number corresponding to xc.
| a0-a3: pointers to the pixels (not fully computed).
| a4: variable x.

    move.w   %d2,%d3
    add.w    %d3,%d3
    move.w   %d3,%d5
    lsl.w    #4,%d5
    sub.w    %d3,%d5
| d0: xc.
| d1: yc.
| d2: variable r.
| d4: variable d = 2 * (1 - r) at the beginning.
| d5: byteoffset of (0,y) from (0,0)
| d6: bit number corresponding to xc.
| a0-a3: pointers to the pixels (not fully computed).
| a4: variable x.

    suba.w   %d5,%a0
    suba.w   %d5,%a1
    adda.w   %d5,%a2
    adda.w   %d5,%a3

    movea.w  %d2,%a5
    move.w   %d0,%d2
    move.w   %d1,%d3
    sub.w    %a5,%d1
    add.w    %a5,%d3
    move.w   %d6,%d7

| d0: x1 = xc.
| d1: y1 = yc - r.
| d2: x2 = xc.
| d3: y2 = yc + r.
| d4: variable d.
| d5: scratch register.
| d6: bit number corresponding to left pixels.
| d7: bit number corresponding to right pixels.
| a0-a3: pointers to the pixels.
| a4: variable x.
| a5: variable r.

0:
| bclr if you want A_REVERSE mode, bchg if you want A_XOR mode.
    cmpi.w   #239,%d0 | if (!((unsigned short)x1 > 239)) {
    bhi.s    4f
    
    cmpi.w   #127,%d1 | if (!((unsigned short)y1 > 127)) {
    bhi.s    5f

    bclr     %d6,(%a0) | x1, y1

5:
    cmpi.w   #127,%d3 | if (!((unsigned short)y2 > 127)) {
    bhi.s    4f
    
    bclr     %d6,(%a2) | x1, y2

4:
    cmpi.w   #239,%d2 | if (!((unsigned short)x2 > 239)) {
    bhi.s    7f

    cmpi.w   #127,%d1 | if (!((unsigned short)y1 > 127)) {
    bhi.s    6f

    bclr     %d7,(%a1) | x2, y1

6:
    cmpi.w   #127,%d3 | if (!((unsigned short)y2 > 127)) {
    bhi.s    7f
    
    bclr     %d7,(%a3) | x2, y2

7:
| if(d + r > 0) {
    move.w   %d4,%d5
    add.w    %a5,%d5
    ble.s    3f
| Short branches are faster if not taken.

    subq.w   #1,%a5 | r--
    sub.w    %a5,%d4
    sub.w    %a5,%d4
    addq.w   #1,%d4 | d -= (r * 2) - 1.
    
    addq.w   #1,%d1 | y1++;
    subq.w   #1,%d3 | y2--;

    moveq    #30,%d5

    adda.w   %d5,%a0
    adda.w   %d5,%a1
    suba.w   %d5,%a2
    suba.w   %d5,%a3

3:
| if(x > d) {
    cmp.w    %a4,%d4
    bge.s    1f
|    bls.s    1f
| Short branches are faster if not taken.

    addq.w   #1,%a4 | x++
    add.w    %a4,%d4
    add.w    %a4,%d4
    addq.w   #1,%d4 | d += (x * 2) + 1;
    
    subq.w   #1,%d0 | x1--;
    addq.w   #1,%d2 | x2++;

    addq.w   #1,%d6
    cmpi.w   #7,%d6
    bls.s    2f
    subq.l   #1,%a0
    subq.l   #1,%a2
    moveq    #0,%d6

2:
    subq.w   #1,%d7
    bge.s    1f
    addq.l   #1,%a1
    addq.l   #1,%a3
    moveq    #7,%d7

1:
    move.l   %a5,%d5
    bge.s    0b

8:
    movem.l  (%sp)+,%d3-%d7/%a2-%a5
    rts
