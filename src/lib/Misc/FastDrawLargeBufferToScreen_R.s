| void FastDrawLargeBufferToScreen_R(const void * big_screen asm("%a0"), void * dest asm("%a1"), unsigned short offsetx asm("%d0"), unsigned short offsety asm("%d1"), unsigned short wordwidth asm("%d2"), unsigned short height asm("%d3")) __attribute__((__regparm__(6)));  // C prototype

| Replace the contents of 240x128 dest buffer with data from the rectangular area (offsetx, offsety, offsetx+LCD_WIDTH-1, offsety+LCD_HEIGHT-1) of the (wordwidth*16) x height source buffer.
| WARNING: routine incomplete for now.

.text
.globl FastDrawLargeBufferToScreen_R
.even
0:
    movem.l  (%sp)+,%d3-%d7
    rts
FastDrawLargeBufferToScreen_R:
    movem.l  %d3-%d7,-(%sp)

    move.w   %d3,%d6
    sub.w    %d1,%d6
| Will draw d6 lines.

    cmpi.w   #128,%d6
    blt.s    0b         | FIXME: bail out for now.
                        | Should draw less than 128 lines... but aligned to top or aligned to bottom ?

    moveq.l  #127,%d6   | Clamp number of lines.


    move.w   %d2,%d7
    lsl.w    #4,%d7
    sub.w    %d0,%d7
| Will draw d7 pixels.

    cmpi.w   #240,%d7
    blt.s    0b         | FIXME: should draw less than 240 pixels... but aligned to left or aligned to right ?
                        | Writing code for this special case is a pain (it's much more complicated than FastFillRect because the
                        | data is not all white or all black). Therefore, if it's not necessary, I'd rather avoid to write it :D


    mulu.w   %d2,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0	| Skip offsety * wordwidth bytes in large buffer.
    
    move.w   %d0,%d5
    lsr.w    #4,%d5     | x offset in words
    add.w    %d5,%d5    |          in bytes
    adda.w   %d5,%a0    | Skip that many additional bytes.
    
    move.w   %d2,%d7
    add.w    %d7,%d7
    sub.w    #30+2,%d7    | Offset between two lines in big screen.

    moveq.l  #16,%d1
0:
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    1f
    sub.w    %d1,%d0
    bra.s    0b
1:
| Here, d0 = (original offsetx) % 16.

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2

1:
    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    move.l   %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    move.l   %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    move.l   %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    move.l   %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    move.l   %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    move.l   %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    move.l   %d3,(%a1)+

    swap.w   %d4	| 16 last pixels
    move.w   %d4,(%a1)+

    adda.w   %d7,%a0

    dbf      %d6,1b

    movem.l  (%sp)+,%d3-%d7
    rts
