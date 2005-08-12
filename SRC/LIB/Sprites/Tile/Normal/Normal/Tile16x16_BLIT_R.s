| C prototype: void Tile16x16_BLIT_R(register short col asm("%d0"),register short y asm("%d1"),register unsigned short *sprite asm("%a1"),register unsigned short maskval asm("%d3"),register void *plane asm("%a0")) __attribute__((__regparm__));

.text
.globl Tile16x16_BLIT_R
.even
 
Tile16x16_BLIT_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
 
    add.w    %d1,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(16/4)-1,%d2
 
0:
    move.l   (%a1)+,%d0
    and.w    %d3,30(%a0)
    or.w     %d0,30(%a0)
    swap     %d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)
 
    move.l   (%a1)+,%d0
    and.w    %d3,90(%a0)
    or.w     %d0,90(%a0)
    swap     %d0
    and.w    %d3,60(%a0)
    or.w     %d0,60(%a0)
 
    lea.l    120(%a0),%a0
 
    dbf      %d2,0b
 
    rts
