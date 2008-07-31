| C prototype: void ClipFastFilledCircle_R(void *plane asm("%a0"), short xcenter asm("%d0"), short ycenter asm("%d1"), unsigned short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addr asm("%a0")) asm("%a2"));
|
| Routine based on Exploder's routine written in C, using FastDrawLine.
| Rewritten in plain assembly by Lionel, now using DrawSpan as callbacks
| instead of hard-coding the drawing mode.

| Agreed, this is how ExtGraph should have been written: symbolic constant definitions, macros...
| Julien started doing it for the new X8 routines.
.set _EXT_MAX_LCD_WIDTH, 239 | Number of columns of the video screen
.set _EXT_MAX_LCD_HEIGHT, 127 | Number of rows of the video screen.

.text
.globl ClipFastFilledCircle_R, GrayClipFastFilledCircle_R
.even

ClipFastFilledCircle_R:
GrayClipFastFilledCircle_R:
    movem.l  %d3-%d7/%a3-%a5,-(%sp)

| d0: xc.
| d1: yc.
| d2: r.

    move.w   %d1,%d4
    sub.w    %d2,%d4
    move.w   %d1,%d5
    add.w    %d2,%d5
    
| d4: y1 = yc - r.
| d5: y2 = yc + r.

    move.w   %d4,%d3
    add.w    %d3,%d3
    move.w   %d3,%d6
    lsl.w    #4,%d6
    sub.w    %d3,%d6
    lea      0(%a0,%d6.w),%a3

    move.w   %d5,%d3
    add.w    %d3,%d3
    move.w   %d3,%d6
    lsl.w    #4,%d6
    sub.w    %d3,%d6
    lea      0(%a0,%d6.w),%a4

| a3: pointer to (0, yc - r).
| a4: pointer to (0, yc + r).

    moveq    #0,%d6
    move.w   %d2,%d7
    move.w   %d0,%a5
    moveq    #1,%d3
    sub.w    %d2,%d3
    add.w    %d3,%d3
| d3: variable d = 2 * (1 - r).
| d6: variable x = 0.
| d7: variable y = r.
| a5: variable xc.

0:
    cmpi.w   #_EXT_MAX_LCD_HEIGHT,%d4
    bhi.s    4f

    move.w   %a5,%d0
    sub.w    %d6,%d0 | xc - x
    move.w   %a5,%d1
    add.w    %d6,%d1 | xc + x
    move.l   %a3,%a0 | line corresponding to y1 = yc - y
    jsr      (%a2)

4:
    cmpi.w   #_EXT_MAX_LCD_HEIGHT,%d5
    bhi.s    5f
| Don't draw middle line twice.
    cmpa.l   %a3,%a4
    beq.s    5f

    move.w   %a5,%d0
    sub.w    %d6,%d0 | xc - x
    move.w   %a5,%d1
    add.w    %d6,%d1 | xc + x
    move.l   %a4,%a0 | line corresponding to y2 = yc + y
    jsr      (%a2)

5:
    st.b     %d1
| d3: variable d = 2 * (1 - r).
| d6: variable x = 0.
| d7: variable y = r.
| a5: variable xc.
6:
| if(d + y > 0) {
    move.w   %d3,%d0
    add.w    %d7,%d0
    ble.s    3f
| Short branches are faster if not taken.

    subq.w   #1,%d7 | y--
    sub.w    %d7,%d3
    sub.w    %d7,%d3
    addq.w   #1,%d3 | d -= (y * 2) - 1.
    
    addq.w   #1,%d4 | y1++;
    subq.w   #1,%d5 | y2--;

    lea      30(%a3),%a3
    lea      -30(%a4),%a4
    
    clr.b    %d1

3:
| if(x > d) {
    cmp.w    %d6,%d3
    bge.s    1f
|    bls.s    1f
| Short branches are faster if not taken.

    addq.w   #1,%d6 | x++
    add.w    %d6,%d3
    add.w    %d6,%d3
    addq.w   #1,%d3 | d += (x * 2) + 1;
    
1:
    move.w   %d7,%d0
    blt.s    8f
    tst.b    %d1
    beq.s    0b
    bra.s    6b

8:
    movem.l  (%sp)+,%d3-%d7/%a3-%a5
    rts
