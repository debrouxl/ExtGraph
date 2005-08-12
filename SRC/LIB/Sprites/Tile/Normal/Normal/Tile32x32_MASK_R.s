| C prototype: void Tile32x32_MASK_R(register short col asm("%d0"),register short y asm("%d1"),register unsigned long *sprite asm("%a1"),unsigned long* mask,register void *plane asm("%a0")) __attribute__((__stkparm__));
 
.text
.globl Tile32x32_MASK_R
.even

Tile32x32_MASK_R:
    pea      (%a2)

    move.l   4+4(%sp),%a2
    
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(32/4)-1,%d2
 
0:
    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1
    and.l    %d1,(%a0)
    or.l     %d0,(%a0)
 
    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1
    and.l    %d1,30(%a0)
    or.l     %d0,30(%a0)

    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1
    and.l    %d1,60(%a0)
    or.l     %d0,60(%a0)
 
    move.l   (%a1)+,%d0
    move.l   (%a2)+,%d1
    and.l    %d1,90(%a0)
    or.l     %d0,90(%a0)
 
    lea.l    120(%a0),%a0
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    rts
