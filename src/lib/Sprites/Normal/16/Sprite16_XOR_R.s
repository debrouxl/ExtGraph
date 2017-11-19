| C prototype: void Sprite16_XOR_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned short *sprt asm("%a1"), void *dest asm("%a0")) __attribute__((__regparm__));

.include "common.s"

.text
.globl Sprite16_XOR_R
.even

Sprite16_XOR_R:
    subq.w   #1,%d2
    blt.s    0f

    swap     %d2

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

    swap     %d2

1:
    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    eor.l    %d0,(%a0)
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b
0:
    rts
