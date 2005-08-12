| C prototype: void GrayTile32x32_AND_R(register short col asm("%d0"),register short y asm("%d1"),unsigned long *sprt0,unsigned long *sprt1,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayTile32x32_AND_R
.even

GrayTile32x32_AND_R:
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
 
    moveq.l  #(32/4)-1,%d2
 
0:
    move.l   (%a2)+,%d0
    and.l    %d0,(%a0)
    move.l   (%a3)+,%d0
    and.l    %d0,(%a1)

    move.l   (%a2)+,%d0
    and.l    %d0,30(%a0)
    move.l   (%a3)+,%d0
    and.l    %d0,30(%a1)

    move.l   (%a2)+,%d0
    and.l    %d0,60(%a0)
    move.l   (%a3)+,%d0
    and.l    %d0,60(%a1)
 
    move.l   (%a2)+,%d0
    and.l    %d0,90(%a0)
    move.l   (%a3)+,%d0
    and.l    %d0,90(%a1)

    lea.l    120(%a0),%a0
    lea.l    120(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
