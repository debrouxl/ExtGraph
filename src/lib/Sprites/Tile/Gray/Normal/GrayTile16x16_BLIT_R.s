| C prototype: void GrayTile16x16_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprt0, const unsigned short *sprt1, const unsigned short maskval asm("%d3"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayTile16x16_BLIT_R
.even
 
GrayTile16x16_BLIT_R:
    move.l   %a2,-(%sp)
    move.l   %a3,-(%sp)
 
    move.l   4+8(%sp),%a2
    move.l   4+8+4(%sp),%a3
 
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(16/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    and.w    %d3,30(%a0)
    or.w     %d0,30(%a0)
    swap     %d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)
 
    move.l   (%a3)+,%d0
    and.w    %d3,30(%a1)
    or.w     %d0,30(%a1)
    swap     %d0
    and.w    %d3,(%a1)
    or.w     %d0,(%a1)
 
    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
