| C prototype: void GrayITile16x16_TRANB_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprite, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayITile16x16_TRANB_R
.even

GrayITile16x16_TRANB_R:
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
 
    moveq.l  #(16/2)-1,%d2
 
0:
    move.w   (%a2)+,%d0
    move.w   (%a2)+,%d1

    move.w   %d1,%d3
    not.w    %d3
    or.w     (%a0),%d3
    and.w    %d0,%d3
    move.w   %d3,(%a0)

    not.w    %d0
    or.w     (%a1),%d0
    and.w    %d1,%d0
    move.w   %d0,(%a1)


    move.w   (%a2)+,%d0
    move.w   (%a2)+,%d1

    move.w   %d1,%d3
    not.w    %d3
    or.w     30(%a0),%d3
    and.w    %d0,%d3
    move.w   %d3,30(%a0)

    not.w    %d0
    or.w     30(%a1),%d0
    and.w    %d1,%d0
    move.w   %d0,30(%a1)

    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    move.l   (%sp)+,%d3
    rts
