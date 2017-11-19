| C prototype: void Sprite8_BLIT_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt asm("%a1"), const unsigned char maskval asm("%d3"), void *dest asm("%a0"));

.include "common.s"

.text
.globl Sprite8_BLIT_R
.even

Sprite8_BLIT_R:
    subq.w   #1,%d2
    blt.s    0f

    move.l   %d4,-(%sp)

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d4

    move.w   %d0,%d4
    lsr.w    #4,%d4

    add.w    %d4,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    moveq.l  #-1,%d4
    move.b   %d3,%d4

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
    swap     %d4
    ror.l    %d1,%d4
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    and.l    %d4,(%a0)
    or.l     %d0,(%a0)
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d4
    rts

3:
    rol.w    %d1,%d4
2:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    and.w    %d4,(%a0)
    or.w     %d0,(%a0)
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,2b

    move.l   (%sp)+,%d4
0:
    rts
