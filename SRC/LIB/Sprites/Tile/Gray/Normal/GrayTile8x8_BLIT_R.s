| C prototype: void GrayTile8x8_BLIT_R(short col asm("%d0"),short y asm("%d1"),unsigned char *sprt0,unsigned char *sprt1,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayTile8x8_BLIT_R
.even

GrayTile8x8_BLIT_R:
    move.l   %a2,-(%sp)
    move.l   %a3,-(%sp)
 
    move.l   4+8(%sp),%a2
    move.l   4+8+4(%sp),%a3
 
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d1,%d1
    add.w    %d0,%d1
 
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(8/2)-1,%d2
 
0:
    move.b   (%a2)+,%d0
    and.b    %d3,(%a0)
    or.b     %d0,(%a0)
    move.b   (%a3)+,%d0
    and.b    %d3,(%a1)
    or.b     %d0,(%a1)
 
    move.b   (%a2)+,%d0
    and.b    %d3,30(%a0)
    or.b     %d0,30(%a0)
    move.b   (%a3)+,%d0
    and.b    %d3,30(%a1)
    or.b     %d0,30(%a1)
 
    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
