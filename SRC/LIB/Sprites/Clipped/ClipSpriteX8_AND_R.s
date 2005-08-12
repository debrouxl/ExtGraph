| C prototype: void ClipSpriteX8_AND_R(register short x asm("%d0"), register short y asm("%d1"),register short h asm("%d3"),register short w asm("%d2"),register unsigned char *sprt asm("%a1"),register void *dest asm("%a0")) __attribute__((__regparm__));
|
| Based on a routine from GFA-Basic, made by Geoffrey Anneheim.
| Modified by Lionel Debroux:
| * changed calling convention and label names.
| * changed OR mode to AND mode.

| Agreed, this is how ExtGraph should have been written: symbolic constant definitions, macros...
| Julien started doing it for the new X8 routines.
.set _EXT_MAX_LCD_WIDTH, 239 | Number of columns of the video screen
.set _EXT_MAX_LCD_HEIGHT, 127 | Number of rows of the video screen.

.text
.globl ClipSpriteX8_AND_R
.even

ClipSpriteX8_AND_R:
    movem.l  %d3-%d7,-(%sp)

|Zone de non affichage
    move.w   %d2,%d5				|%d5 = Bytewidth
    neg.w    %d5					|%d5 = -Bytewidth
    lsl.w    #3,%d5				|-Bytewidth*8
    cmp.w    %d5,%d0				|x<=%d5
    jble     0f
    cmpi.w   #_EXT_MAX_LCD_WIDTH+1,%d0
    jbge     0f
    move.w   %d3,%d5				|%d5 = h
    neg.w    %d5					|%d5 = -h
    cmp.w    %d5,%d1
    jblt     0f
    cmpi.w   #_EXT_MAX_LCD_HEIGHT+1,%d1
    jbge     0f

|y<0
    tst.w    %d1
    jbge     _ExecCmd_Put_Draw_continue
    add.w    %d1,%d3				|h += y
    move.w   %d1,%d5				|%d5 = y
    muls.w   %d2,%d5				|y*Bytewidth
    suba.w   %d5,%a1				|sprite -= y*Bytewidth
    clr.w    %d1
_ExecCmd_Put_Draw_continue:
|y+1>=_EXT_MAX_LCD_HEIGHT
    move.w   %d1,%d5				|%d5 = y
    add.w    %d3,%d5				|%d5 = y+h
    cmpi.w   #_EXT_MAX_LCD_HEIGHT+1,%d5
    jblt     _ExecCmd_Put_Draw_continue2
    move.w   #_EXT_MAX_LCD_HEIGHT+1,%d3			|h = _EXT_MAX_LCD_HEIGHT
    sub.w    %d1,%d3				|h = _EXT_MAX_LCD_HEIGHT-y
_ExecCmd_Put_Draw_continue2:
    move.w   %d1,%d5
    lsl.w    #4,%d1
    sub.w    %d5,%d1
    add.w    %d1,%d1
/*    move.w   %d1,%d5				|%d5 = y
    add.w    %d5,%d5				|y*2
    asl.w    #5,%d1				|%d1 = y<<5
    sub.w    %d5,%d1				|(y<<5)-(y<<1)*/
    move.w   %d0,%d5				|%d5 = x
    lsr.w    #3,%d5				|%d5 = x>>8
    add.w    %d5,%d1
    adda.w   %d1,%a0				|offset

    move.w   %d0,%d1				|%d1 = x
    andi.w   #7,%d1				|%d1 = x&7

    moveq.l  #8,%d4
    sub.w    %d1,%d4				|8-%d1

    move.w   #30,%d5
    sub.w    %d2,%d5

|x<0
    tst.w    %d0
    jblt     7f
    move.w   %d2,%d6				|%d6 = Bytewidth
    lsl.w    #3,%d6				|%d6 = Bytewidth<<3
    add.w    %d0,%d6				|%d6 = (Bytewidth<<3)+x
    cmpi.w   #_EXT_MAX_LCD_WIDTH+1,%d6
    jbge     8f
_ExecCmd_Put_Draw_normal:
    moveq.l  #0,%d0
    move.w   %d3,%d0
    dbf      %d0,_ExecCmd_Put_Draw_normal_loop
    jbra     0f
_ExecCmd_Put_Draw_normal_loop:
    moveq.l  #-1,%d3
    move.b   (%a1),%d3
    asr.w    %d1,%d3
    and.b    %d3,(%a0)+

    moveq.l  #0,%d7
    move.w   %d2,%d7
    subq.l   #1,%d7
    dbf      %d7,_ExecCmd_Put_Draw_normal_loop2
    jbra     _ExecCmd_Put_Draw_normal_loop2_continue
_ExecCmd_Put_Draw_normal_loop2:
    moveq.l  #-1,%d3
    move.b   (%a1)+,%d3
    rol.w    %d4,%d3
    and.b    %d3,(%a0)
    moveq.l  #-1,%d3
    move.b   (%a1),%d3
    asr.w    %d1,%d3
    and.b    %d3,(%a0)+
    dbf      %d7,_ExecCmd_Put_Draw_normal_loop2
_ExecCmd_Put_Draw_normal_loop2_continue:
    moveq.l  #-1,%d3
    move.b   (%a1)+,%d3
    rol.w    %d4,%d3
    and.b    %d3,(%a0)
    lea.l    (%d5.w,%a0),%a0
    dbf      %d0,_ExecCmd_Put_Draw_normal_loop
0:
    movem.l  (%sp)+,%d3-%d7
    rts

7:
    neg.w    %d0					|x = -x
    move.w   %d0,%d6
    lsr.w    #3,%d6

    move.w   %d6,%d7
    lsl.w    #3,%d7
    cmp.w    %d7,%d0
    jbeq     _ExecCmd_Put_Draw_left_continue
    addi.w   #1,%d6
_ExecCmd_Put_Draw_left_continue:
    moveq.l  #0,%d0
    move.w   %d3,%d0
    dbf      %d0,_ExecCmd_Put_Draw_left_loop
    jbra     0b
_ExecCmd_Put_Draw_left_loop:
|    subq.l   #1,%a1
    lea.l    -1(%d6.w,%a1),%a1
    lea.l    (%d6.w,%a0),%a0

    moveq.l  #0,%d7
    move.w   %d2,%d7
    sub.w    %d6,%d7
    dbf      %d7,_ExecCmd_Put_Draw_left_loop2
    jbra     _ExecCmd_Put_Draw_left_loop2_continue
_ExecCmd_Put_Draw_left_loop2:
    moveq.l  #-1,%d3
    move.b   (%a1)+,%d3
    rol.w    %d4,%d3
    and.b    %d3,(%a0)
    moveq.l  #-1,%d3
    move.b   (%a1),%d3
    asr.w    %d1,%d3
    and.b    %d3,(%a0)+
    dbf      %d7,_ExecCmd_Put_Draw_left_loop2
_ExecCmd_Put_Draw_left_loop2_continue:
    moveq.l  #-1,%d3
    move.b   (%a1)+,%d3
    rol.w    %d4,%d3
    and.b    %d3,(%a0)
    lea.l    (%d5.w,%a0),%a0
    dbf      %d0,_ExecCmd_Put_Draw_left_loop
0:
    movem.l  (%sp)+,%d3-%d7
    rts

8:
    subi.w   #_EXT_MAX_LCD_WIDTH+1,%d6
    asr.w    #3,%d6
    moveq.l  #0,%d0
    move.w   %d3,%d0
    dbf      %d0,_ExecCmd_Put_Draw_right_loop
    jbra     0b
_ExecCmd_Put_Draw_right_loop:
    moveq.l  #-1,%d3
    move.b   (%a1),%d3
    asr.w    %d1,%d3
    and.b    %d3,(%a0)+

    moveq.l  #0,%d7
    move.w   %d2,%d7
    sub.w    %d6,%d7
    subq.l   #1,%d7
    dbf      %d7,_ExecCmd_Put_Draw_right_loop2
    jbra     _ExecCmd_Put_Draw_right_loop2_continue
_ExecCmd_Put_Draw_right_loop2:
    moveq.l  #-1,%d3
    move.b   (%a1)+,%d3
    rol.w    %d4,%d3
    and.b    %d3,(%a0)
    moveq.l  #-1,%d3
    move.b   (%a1),%d3
    asr.w    %d1,%d3
    and.b    %d3,(%a0)+
    dbf      %d7,_ExecCmd_Put_Draw_right_loop2
_ExecCmd_Put_Draw_right_loop2_continue:
|    addq.l   #1,%a1
    lea.l    1(%d6.w,%a1),%a1
    lea.l    0(%d6.w,%a0),%a0
    lea.l    0(%d5.w,%a0),%a0
    dbf      %d0,_ExecCmd_Put_Draw_right_loop

    movem.l  (%sp)+,%d3-%d7
    rts
