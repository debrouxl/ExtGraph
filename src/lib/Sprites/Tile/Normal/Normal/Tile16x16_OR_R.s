| C prototype: void Tile16x16_OR_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned short *sprite asm("%a1"), void *plane asm("%a0"));

.text
.globl Tile16x16_OR_R
.even

Tile16x16_OR_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(16/8)-1,%d2
 
0:
    move.l   (%a1)+,%d0
    or.w     %d0,30(%a0)
    swap     %d0
    or.w     %d0,(%a0)
 
    move.l   (%a1)+,%d0
    or.w     %d0,90(%a0)
    swap     %d0
    or.w     %d0,60(%a0)
 
    move.l   (%a1)+,%d0
    or.w     %d0,150(%a0)
    swap     %d0
    or.w     %d0,120(%a0)
 
    move.l   (%a1)+,%d0
    or.w     %d0,210(%a0)
    swap     %d0
    or.w     %d0,180(%a0)
 
    lea.l    240(%a0),%a0
 
    dbf      %d2,0b
 
    rts
