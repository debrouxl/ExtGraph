| C prototype: void Sprite8_OR(unsigned short x, unsigned short y, unsigned short height, const unsigned char *sprt, void *dest) __attribute__((__stkparm__));
|
| This routine is faster (about 20%) than the previous C routine, because the
| algorithm was changed.

.include "common.s"

.text
.globl Sprite8_OR
.even

Sprite8_OR:
    move.w   0+4+0(%sp),%d0
    move.w   0+4+2(%sp),%d1
    movea.l  0+4+6(%sp),%a1

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    movea.w  %d0,%a0
    adda.l   0+4+10(%sp),%a0

    andi.w   #0xF,%d2
    moveq    #8,%d1
    sub.w    %d2,%d1

    move.w   0+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    tst.w    %d1
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
