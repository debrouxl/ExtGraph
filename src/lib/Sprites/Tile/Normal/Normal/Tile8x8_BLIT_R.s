| C prototype: void Tile8x8_BLIT_R(unsigned short col asm("%d0"), unsigned short y asm("%d1"), const unsigned char *sprite asm("%a1"), const unsigned char maskval asm("%d3"), void *plane asm("%a0"));

.text
.globl Tile8x8_BLIT_R
.even

Tile8x8_BLIT_R:
    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1
 
    add.w    %d1,%d1
    add.w    %d0,%d1
    adda.w   %d1,%a0
 
    moveq.l  #(8/4)-1,%d2
 
0:
    move.b   (%a1)+,%d0
    and.b    %d3,(%a0)
    or.b     %d0,(%a0)
 
    move.b   (%a1)+,%d0
    and.b    %d3,30(%a0)
    or.b     %d0,30(%a0)

    move.b   (%a1)+,%d0
    and.b    %d3,60(%a0)
    or.b     %d0,60(%a0)

    move.b   (%a1)+,%d0
    and.b    %d3,90(%a0)
    or.b     %d0,90(%a0)
 
    lea.l    120(%a0),%a0
 
    dbf      %d2,0b
 
    rts
