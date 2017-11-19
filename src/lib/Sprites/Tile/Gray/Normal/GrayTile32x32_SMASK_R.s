| C prototype: void GrayTile32x32_SMASK_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned long *sprt0, const unsigned long *sprt1, unsigned long* mask, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));
 
.include "common.s"

.text
.globl GrayTile32x32_SMASK_R
.even

GrayTile32x32_SMASK_R:
    movem.l  %a2-%a4,-(%sp)

    lea      4+12(%sp),%a4
    move.l   (%a4)+,%a2
    move.l   (%a4)+,%a3
    move.l   (%a4),%a4
    
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(32/2)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    move.l   (%a4)+,%d1
    and.l    %d1,(%a0)
    or.l     %d0,(%a0)
 
    move.l   (%a3)+,%d0
    and.l    %d1,(%a1)
    or.l     %d0,(%a1)

    move.l   (%a2)+,%d0
    move.l   (%a4)+,%d1
    and.l    %d1,PLANE_BYTE_WIDTH(%a0)
    or.l     %d0,PLANE_BYTE_WIDTH(%a0)
 
    move.l   (%a3)+,%d0
    and.l    %d1,PLANE_BYTE_WIDTH(%a1)
    or.l     %d0,PLANE_BYTE_WIDTH(%a1)
 
    lea.l    2*PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    2*PLANE_BYTE_WIDTH(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%a2-%a4
    rts
