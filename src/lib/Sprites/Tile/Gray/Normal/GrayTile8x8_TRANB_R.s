| C prototype: void GrayTile8x8_TRANB_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned char *sprt0, const unsigned char *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayTile8x8_TRANB_R
.even

GrayTile8x8_TRANB_R:
    movem.l  %d3/%a2-%a3,-(%sp)
 
    move.l   4+12(%sp),%a2
    move.l   4+12+4(%sp),%a3
 
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(8/2)-1,%d2
 
0:
    move.b   (%a2)+,%d0
    move.b   (%a3)+,%d1

    move.b   %d1,%d3
    not.b    %d3
    or.b     (%a0),%d3
    and.b    %d0,%d3
    move.b   %d3,(%a0)

    not.b    %d0
    or.b     (%a1),%d0
    and.b    %d1,%d0
    move.b   %d0,(%a1)


    move.b   (%a2)+,%d0
    move.b   (%a3)+,%d1

    move.b   %d1,%d3
    not.b    %d3
    or.b     30(%a0),%d3
    and.b    %d0,%d3
    move.b   %d3,30(%a0)

    not.b    %d0
    or.b     30(%a1),%d0
    and.b    %d1,%d0
    move.b   %d0,30(%a1)

    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%d3/%a2-%a3
    rts
