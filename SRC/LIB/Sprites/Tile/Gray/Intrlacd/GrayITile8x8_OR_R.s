| C prototype: void GrayITile8x8_OR_R(register short col asm("%d0"),register short y asm("%d1"),unsigned char *sprite,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GrayITile8x8_OR_R
.even

GrayITile8x8_OR_R:
    move.l   %a2,-(%sp)
 
    move.l   4+4(%sp),%a2
 
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d1,%d1
    add.w    %d0,%d1
 
    adda.w   %d1,%a0
    adda.w   %d1,%a1
 
    moveq.l  #(8/4)-1,%d2
 
0:
    move.b   (%a2)+,%d0
    or.b     %d0,(%a0)
    move.b   (%a2)+,%d0
    or.b     %d0,(%a1)
 
    move.b   (%a2)+,%d0
    or.b     %d0,30(%a0)
    move.b   (%a2)+,%d0
    or.b     %d0,30(%a1)
 
 
    move.b   (%a2)+,%d0
    or.b     %d0,60(%a0)
    move.b   (%a2)+,%d0
    or.b     %d0,60(%a1)
 
    move.b   (%a2)+,%d0
    or.b     %d0,90(%a0)
    move.b   (%a2)+,%d0
    or.b     %d0,90(%a1)
 
    lea.l    120(%a0),%a0
    lea.l    120(%a1),%a1
 
    dbf      %d2,0b
 
    move.l   (%sp)+,%a2
    rts
