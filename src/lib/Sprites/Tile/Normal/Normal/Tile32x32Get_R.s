| C prototype: void Tile32x32Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned long *dest asm("%a1"));

.text
.globl Tile32x32Get_R
.even

Tile32x32Get_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    add.w    %d0,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

    moveq.l  #(32/8)-1,%d2

0:
    move.l   (%a0),(%a1)+

    move.l   30(%a0),(%a1)+

    move.l   60(%a0),(%a1)+

    move.l   90(%a0),(%a1)+

    move.l   120(%a0),(%a1)+

    move.l   150(%a0),(%a1)+

    move.l   180(%a0),(%a1)+

    move.l   210(%a0),(%a1)+

    lea      240(%a0),%a0

    dbf      %d2,0b

    rts
