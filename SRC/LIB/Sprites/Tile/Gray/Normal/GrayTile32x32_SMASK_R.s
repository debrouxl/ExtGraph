| C prototype: void GrayTile32x32_SMASK_R(register short col asm("%d0"),register short y asm("%d1"),unsigned long *sprt0,unsigned long *sprt1,unsigned long* mask,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));
 
.text
.globl GrayTile32x32_SMASK_R
.even

GrayTile32x32_SMASK_R:
    movem.l  %a2-%a4,-(%sp)

    lea      4+12(%sp),%a4
    move.l   (%a4)+,%a2
    move.l   (%a4)+,%a3
    move.l   (%a4),%a4
    
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
    move.l   (%a4)+,%d1
    and.l    %d1,(%a0)
    or.l     %d0,(%a0)
 
    move.l   (%a3)+,%d0
    and.l    %d1,(%a1)
    or.l     %d0,(%a1)

    move.l   (%a2)+,%d0
    move.l   (%a4)+,%d1
    and.l    %d1,30(%a0)
    or.l     %d0,30(%a0)
 
    move.l   (%a3)+,%d0
    and.l    %d1,30(%a1)
    or.l     %d0,30(%a1)
 
    lea.l    60(%a0),%a0
    lea.l    60(%a1),%a1
 
    dbf      %d2,0b
 
    movem.l  (%sp)+,%a2-%a4
    rts
