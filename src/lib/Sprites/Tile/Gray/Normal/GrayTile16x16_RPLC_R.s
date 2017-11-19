| C prototype: void GrayTile16x16_RPLC_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprt0, const unsigned short *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayTile16x16_RPLC_R
.even

GrayTile16x16_RPLC_R:
    move.l   %a2,-(%sp)
    move.l   %a3,-(%sp)
 
    move.l   4+8(%sp),%a2
    move.l   4+8+4(%sp),%a3
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(16/4)-1,%d2
 
0:
    move.w   (%a2)+,(%a0)
    move.w   (%a3)+,(%a1)
    move.w   (%a2)+,PLANE_BYTE_WIDTH(%a0)
    move.w   (%a3)+,PLANE_BYTE_WIDTH(%a1)
    move.w   (%a2)+,2*PLANE_BYTE_WIDTH(%a0)
    move.w   (%a3)+,2*PLANE_BYTE_WIDTH(%a1)
    move.w   (%a2)+,3*PLANE_BYTE_WIDTH(%a0)
    move.w   (%a3)+,3*PLANE_BYTE_WIDTH(%a1)

    lea.l    4*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    4*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
