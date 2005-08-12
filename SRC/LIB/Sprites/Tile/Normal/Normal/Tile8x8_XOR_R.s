| C prototype: void Tile8x8_XOR_R(register short col asm("%d0"),register short y asm("%d1"),register unsigned char *sprite asm("%a1"),register void *plane asm("%a0")) __attribute__((__regparm__));

.text
.globl Tile8x8_XOR_R
.even

Tile8x8_XOR_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d1,%d1
    add.w    %d0,%d1
 
    adda.w   %d1,%a0
 

    move.b   (%a1)+,%d0
    eor.b    %d0,(%a0)
 
    move.b   (%a1)+,%d0
    eor.b    %d0,30(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,60(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,90(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,120(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,150(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,180(%a0)

    move.b   (%a1)+,%d0
    eor.b    %d0,210(%a0)
  
    rts
