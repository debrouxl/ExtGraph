| C prototype: void DoubleSpriteDimensionsX8_R(register short h asm("%d0"),register unsigned char* src asm("%a0"),register short bytewidth asm("%d1"),register unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

| I love dbxx instruction, especially dbf !

.text
.globl DoubleSpriteDimensionsX8_R
.even
DoubleSpriteDimensionsX8_R:
| If you're scaling a sprite of common format (8, 16, 32-pixel wide), you
| may optimize this routine significantly (see DoubleSpriteDimensions16x16_R).
| See also the comments below. For example, using a2, so saving/restoring
| it, can be superfluous.

    dbf      %d0,1f
    rts

1:
    dbf      %d1,2f
    rts

2:
    movem.l  %d3-%d5/%a2,-(%sp)
    move.w   %d1,%d5

| Modify here if you hard-code the height of the sprite: put a moveq or
| move.w #height-1,%d0.
0:
| Suppress the move.l dest,%a2 if you're scaling a sprite of common format.
    move.l   %a1,%a2
    move.w   %d5,%d1

3:
| Modify here (both instructions) if you're scaling a sprite of common format.
    move.b   (%a0)+,%d2

    moveq    #4-1,%d4
4:
| Loop is unrolled twice, so that speed is significantly increased (by ~20%),
| while size is increased by only 6 bytes. Optimizing for size at all costs
| would be stupid here...
| Algorithm posted on the official TIGCC/TICT board by Kevin Kofler. It uses
| the fact asr repeats the leftmost bit.
    lsr.b    #1,%d2
    roxr.w   #1,%d3
    asr.w    #1,%d3

    lsr.b    #1,%d2
    roxr.w   #1,%d3
    asr.w    #1,%d3
    dbf      %d4,4b

| Modify here (suppress instruction) if you're scaling a sprite of common
| format. You may also double the loop above itself (32-pixel wide sprites).
    move.w   %d3,(%a1)+
    dbf      %d1,3b

| This block of code, down to the second dbf, is not necessary if you're
| scaling a sprite of common format.
    move.l   %a1,%d1
    sub.l    %a2,%d1
    lsr.w    #1,%d1
    subq.w   #1,%d1

5:
    move.w   (%a2)+,(%a1)+

    dbf      %d1,5b

    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5/%a2
    rts
