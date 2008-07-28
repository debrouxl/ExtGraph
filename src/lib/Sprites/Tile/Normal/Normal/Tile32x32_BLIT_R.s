| C prototype: void Tile32x32_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprite asm("%a1"), const unsigned long maskval asm("%d3"), void *plane asm("%a0")) __attribute__((__stkparm__));

.text
.globl Tile32x32_BLIT_R
.even
 
Tile32x32_BLIT_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(32/4)-1,%d2
 
0:
    move.l   (%a1)+,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,30(%a0)
    or.l     %d0,30(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,60(%a0)
    or.l     %d0,60(%a0)

    move.l   (%a1)+,%d0
    and.l    %d3,90(%a0)
    or.l     %d0,90(%a0)
 
    lea.l    120(%a0),%a0
 
    dbf      %d2,0b
 
    rts
