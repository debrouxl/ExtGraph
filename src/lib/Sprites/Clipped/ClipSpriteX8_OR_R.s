| C prototype: void ClipSpriteX8_OR_R(short x asm("%d0"), short y asm("%d1"), unsigned short h asm("%d3"), unsigned short bytewidth asm("%d2"), const unsigned char *sprt asm("%a1"), void *dest asm("%a0")) __attribute__((__regparm__));
|
| Based on a routine from GFA-Basic, made by Geoffrey Anneheim.
| Modified by Lionel Debroux:
| * changed calling convention and label names.
| * rewritten most of the code of all drawing loops to significantly
|   optimize for both speed and size.

| Agreed, this is how ExtGraph should have been written: symbolic constant definitions, macros...
| Julien started doing it for the new X8 routines.
.set _EXT_MAX_LCD_WIDTH, 239 | Number of columns of the video screen
.set _EXT_MAX_LCD_HEIGHT, 127 | Number of rows of the video screen.

.text
.globl ClipSpriteX8_OR_R
.even

ClipSpriteX8_OR_R:
    movem.l  %d3-%d7,-(%sp)

|Zone de non affichage
    move.w   %d2,%d5				|%d5 = Bytewidth
    beq.s    0f 				|(d5 == 0)?exit:keep going.
    neg.w    %d5				|%d5 = -Bytewidth
    lsl.w    #3,%d5				|-Bytewidth*8
    cmp.w    %d5,%d0				|x<=%d5
    jble     0f
    cmpi.w   #_EXT_MAX_LCD_WIDTH+1,%d0
    jbge     0f
    move.w   %d3,%d5				|%d5 = h
    beq.s    0f 				|(d5 == 0)?exit:keep going.
    neg.w    %d5				|%d5 = -h
    cmp.w    %d5,%d1
    jble     0f
    cmpi.w   #_EXT_MAX_LCD_HEIGHT+1,%d1
    jblt     10f
0:
    movem.l  (%sp)+,%d3-%d7
    rts

10:
|y<0
    tst.w    %d1
    jbge     10f
    add.w    %d1,%d3				|h += y
    move.w   %d1,%d5				|%d5 = y
    muls.w   %d2,%d5				|y*Bytewidth
    suba.w   %d5,%a1				|sprite -= y*Bytewidth
    clr.w    %d1
10:
|y+1>=_EXT_MAX_LCD_HEIGHT
    move.w   %d1,%d5				|%d5 = y
    add.w    %d3,%d5				|%d5 = y+h
    cmpi.w   #_EXT_MAX_LCD_HEIGHT+1,%d5
    jblt     10f
    move.w   #_EXT_MAX_LCD_HEIGHT+1,%d3		|h = _EXT_MAX_LCD_HEIGHT
    sub.w    %d1,%d3				|h = _EXT_MAX_LCD_HEIGHT-y
10:
    move.w   %d1,%d5
    lsl.w    #4,%d1
    sub.w    %d5,%d1
    add.w    %d1,%d1
    move.w   %d0,%d5				|%d5 = x
    asr.w    #3,%d5				|%d5 = x>>8 - arithmetical shift (important !)
    add.w    %d5,%d1
    adda.w   %d1,%a0				|offset

    move.w   %d0,%d1				|%d1 = x
    andi.w   #7,%d1				|%d1 = x&7

    moveq.l  #8,%d4
    sub.w    %d1,%d4				|8-%d1

    moveq    #30,%d5
    sub.w    %d2,%d5

|x<0
    tst.w    %d0
    jblt     7f
    move.w   %d2,%d6				|%d6 = Bytewidth
    lsl.w    #3,%d6				|%d6 = Bytewidth<<3
    add.w    %d0,%d6				|%d6 = (Bytewidth<<3)+x
    subi.w   #_EXT_MAX_LCD_WIDTH+1,%d6
    jbgt     8f

    subq.w   #2,%d2
    subq.w   #1,%d3
1:
    move.b   (%a1),%d0
    lsr.b    %d1,%d0
    or.b     %d0,(%a0)+

    move.w   %d2,%d7
    blt.s    9f
2:
    move.b   (%a1)+,%d6
    lsl.b    %d4,%d6
    or.b     %d6,(%a0)
    move.b   (%a1),%d6
    lsr.b    %d1,%d6
    or.b     %d6,(%a0)+
    dbf      %d7,2b

9:
    move.b   (%a1)+,%d0
    lsl.b    %d4,%d0
    or.b     %d0,(%a0)
    adda.w   %d5,%a0
    dbf      %d3,1b
0:
    movem.l  (%sp)+,%d3-%d7
    rts

7:
    neg.w    %d0					|x = -x
    move.w   %d0,%d6
    lsr.w    #3,%d6

    subq.w   #1,%d3

    move.w   %d6,%d7
    lsl.w    #3,%d7
    cmp.w    %d7,%d0
    jbeq     10f
    addq.w   #1,%d6
10:
    add.w    %d6,%d5

    move.w   %d2,%d7
    sub.w    %d6,%d7

    subq.w   #1,%d7
    move.w   %d7,%d2

    adda.w   %d6,%a0
4:
    lea.l    -1(%d6.w,%a1),%a1

    move.w   %d2,%d7
    blt.s    9f
6:
    move.b   (%a1)+,%d0
    lsl.b    %d4,%d0
    or.b     %d0,(%a0)
    move.b   (%a1),%d0
    lsr.b    %d1,%d0
    or.b     %d0,(%a0)+
    dbf      %d7,6b
9:
    move.b   (%a1)+,%d0
    lsl.b    %d4,%d0
    or.b     %d0,(%a0)
    adda.w   %d5,%a0
    dbf      %d3,4b
0:
    movem.l  (%sp)+,%d3-%d7
    rts

8:
    lsr.w    #3,%d6

    add.w    %d6,%d5

    move.w   %d2,%d7
    sub.w    %d6,%d7
    subq.w   #2,%d7

    move.w   %d7,%d2

    subq.w   #1,%d3

5:
    move.b   (%a1),%d0
    lsr.b    %d1,%d0
    or.b     %d0,(%a0)+

    move.w   %d2,%d7
    blt.s    9f
7:
    move.b   (%a1)+,%d0
    lsl.b    %d4,%d0
    or.b     %d0,(%a0)
    move.b   (%a1),%d0
    lsr.b    %d1,%d0
    or.b     %d0,(%a0)+
    dbf      %d7,7b
9:
    lea.l    1(%d6.w,%a1),%a1
    adda.w   %d5,%a0
    dbf      %d3,5b

    movem.l  (%sp)+,%d3-%d7
    rts
