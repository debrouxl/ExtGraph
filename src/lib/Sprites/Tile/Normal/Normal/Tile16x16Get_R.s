| C prototype: void Tile16x16Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned short *dest asm("%a1"));

.text
.globl Tile16x16Get_R
.even

Tile16x16Get_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #(16/8)-1,%d2

0:
    move.w   (%a0),(%a1)+

    move.w   30(%a0),(%a1)+

    move.w   60(%a0),(%a1)+

    move.w   90(%a0),(%a1)+

    move.w   120(%a0),(%a1)+

    move.w   150(%a0),(%a1)+

    move.w   180(%a0),(%a1)+

    move.w   210(%a0),(%a1)+

    lea      240(%a0),%a0

    dbf      %d2,0b

    rts
