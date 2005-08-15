| C prototype: void GrayTile16x16_MASK_R(register short col asm("%d0"),register short y asm("%d1"),unsigned short *sprt0,unsigned short *sprt1,unsigned short* mask1,unsigned short* mask2,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));
 
.text
.globl GrayTile16x16_MASK_R
.even

GrayTile16x16_MASK_R:
    movem.l  %a2-%a5,-(%sp)

    lea      4+16(%sp),%a5
    move.l   (%a5)+,%a2
    move.l   (%a5)+,%a3
    move.l   (%a5)+,%a4
    move.l   (%a5),%a5
    
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
    move.l   (%a4)+,%d1
   
    and.w    %d1,30(%a0)
    or.w     %d0,30(%a0)
    swap     %d0
    swap     %d1
    and.w    %d1,(%a0)
    or.w     %d0,(%a0)
 
    move.l   (%a3)+,%d0
    move.l   (%a5)+,%d1
   
    and.w    %d1,30(%a1)
    or.w     %d0,30(%a1)
    swap     %d0
    swap     %d1
    and.w    %d1,(%a1)
    or.w     %d0,(%a1)
 
    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%a2-%a5
    rts