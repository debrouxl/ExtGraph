| C prototype: void GrayITile32x32_TRANW_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprite, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayITile32x32_TRANW_R
.even

GrayITile32x32_TRANW_R:
    move.l   %d3,-(%sp)
    move.l   %a2,-(%sp)
 
    move.l   4+8(%sp),%a2
 
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(32/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    move.l   (%a2)+,%d1

    move.l   %d1,%d3
    not.l    %d3
    and.l    (%a0),%d3
    or.l     %d0,%d3
    move.l   %d3,(%a0)

    not.l    %d0
    and.l    (%a1),%d0
    or.l     %d1,%d0
    move.l   %d0,(%a1)

    move.l   (%a2)+,%d0
    move.l   (%a2)+,%d1

    move.l   %d1,%d3
    not.l    %d3
    and.l    30(%a0),%d3
    or.l     %d0,%d3
    move.l   %d3,30(%a0)

    not.l    %d0
    and.l    30(%a1),%d0
    or.l     %d1,%d0
    move.l   %d0,30(%a1)

    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts
