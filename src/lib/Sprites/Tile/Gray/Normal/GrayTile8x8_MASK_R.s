| C prototype: void GrayTile8x8_MASK_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned char *sprt0, const unsigned char *sprt1, const unsigned char* mask1, const unsigned char* mask2, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.include "common.s"

.text
.globl GrayTile8x8_MASK_R
.even

GrayTile8x8_MASK_R:
    movem.l  %a2-%a5,-(%sp)
 
    lea      4+16(%sp),%a5
    move.l   (%a5)+,%a2
    move.l   (%a5)+,%a3
    move.l   (%a5)+,%a4
    move.l   (%a5),%a5
 
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d1,%d1
    add.w    %d0,%d1
 
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(8/2)-1,%d2
 
0:
    move.b   (%a2)+,%d0
    move.b   (%a4)+,%d1
    and.b    %d1,(%a0)
    or.b     %d0,(%a0)
 
    move.b   (%a3)+,%d0
    move.b   (%a5)+,%d1
    and.b    %d1,(%a1)
    or.b     %d0,(%a1)
 
 
    move.b   (%a2)+,%d0
    move.b   (%a4)+,%d1
    and.b    %d1,PLANE_BYTE_WIDTH(%a0)
    or.b     %d0,PLANE_BYTE_WIDTH(%a0)
 
    move.b   (%a3)+,%d0
    move.b   (%a5)+,%d1
    and.b    %d1,PLANE_BYTE_WIDTH(%a1)
    or.b     %d0,PLANE_BYTE_WIDTH(%a1)
 
    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%a2-%a5
    rts
