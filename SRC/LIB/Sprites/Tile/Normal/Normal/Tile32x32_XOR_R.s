| C prototype: void Tile32x32_XOR_R(register short col asm("%d0"),register short y asm("%d1"),register unsigned long *sprite asm("%a1"),register void *plane asm("%a0")) __attribute__((__regparm__));

.text
.globl Tile32x32_XOR_R
.even

Tile32x32_XOR_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d0,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0
 
    moveq.l  #(32/8)-1,%d2
 
0:
    move.l   (%a1)+,%d0
    eor.l    %d0,(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,30(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,60(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,90(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,120(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,150(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,180(%a0)

    move.l   (%a1)+,%d0
    eor.l    %d0,210(%a0)

    lea.l    240(%a0),%a0
 
    dbf      %d2,0b
 
    rts
