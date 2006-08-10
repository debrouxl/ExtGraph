| C prototype: void Tile16x16_RPLC_R(short col asm("%d0"),short y asm("%d1"),unsigned short *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__regparm__));

.text
.globl Tile16x16_RPLC_R
.even

Tile16x16_RPLC_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(16/8)-1,%d2
 
0:
    move.w   (%a1)+,(%a0)

    move.w   (%a1)+,30(%a0)

    move.w   (%a1)+,60(%a0)

    move.w   (%a1)+,90(%a0)

    move.w   (%a1)+,120(%a0)

    move.w   (%a1)+,150(%a0)

    move.w   (%a1)+,180(%a0)

    move.w   (%a1)+,210(%a0)
 
    lea.l    240(%a0),%a0
 
    dbf      %d2,0b

    rts
