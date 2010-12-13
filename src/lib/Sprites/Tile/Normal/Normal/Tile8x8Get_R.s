| C prototype: void Tile8x8Get_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const void *src asm("%a0"), unsigned char *dest asm("%a1"));

.text
.globl Tile8x8Get_R
.even

Tile8x8Get_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    add.w    %d1,%d1
    add.w    %d0,%d1

    adda.w   %d1,%a0


    move.b   (%a0),(%a1)+

    move.b   30(%a0),(%a1)+

    move.b   60(%a0),(%a1)+

    move.b   90(%a0),(%a1)+

    move.b   120(%a0),(%a1)+

    move.b   150(%a0),(%a1)+

    move.b   180(%a0),(%a1)+

    move.b   210(%a0),(%a1)+

    rts
