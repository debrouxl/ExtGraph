| C prototype: void Sprite8_OR_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt asm("%a1"), void *dest asm("%a0")) __attribute__((__regparm__));

.include "common.s"

.text
.globl Sprite8_OR_R
.even

Sprite8_OR_R:
    subq.w   #1,%d2
    blt.s    0f

    swap     %d2

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    move.w   %d0,%d2	| d2 = x
    lsr.w    #4,%d2	| d2 = x/16

    add.w    %d2,%d1	| d1 = y*PLANE_BYTE_WIDTH/2 + x/16
    add.w    %d1,%d1	| d1 = y*PLANE_BYTE_WIDTH + x/8
    adda.w   %d1,%a0	| a0 += offset

    swap     %d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a0)
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b
    rts

2:
    lea      PLANE_BYTE_WIDTH(%a0),%a0
3:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)
    dbf      %d2,2b
0:
    rts
