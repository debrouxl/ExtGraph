| C prototype: void GraySprite8_SMASK_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt0, const unsigned char *sprt1, const unsigned char *mask, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite8_SMASK_R
.even

GraySprite8_SMASK_R:
    subq.w   #1,%d2
    blt.s    0f

    movem.l  %d3/%a2-%a4,-(%sp)

    lea.l    4+16(%sp),%a4
    movea.l  (%a4)+,%a2
    movea.l  (%a4)+,%a3
    movea.l  (%a4),%a4

    move.w   %d1,%d3	| d3 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d3,%d1	| d1 = 15*y

    moveq    #15,%d3
    and.w    %d0,%d3
    lsr.w    #4,%d0	| d3 = x/16

    add.w    %d0,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8
    adda.w   %d1,%a0	| a0 += offset
    adda.w   %d1,%a1

    moveq    #8,%d1
    sub.w    %d3,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq.l  #-1,%d3
    move.b   (%a4)+,%d3
    swap.w   %d3
    ror.l    %d1,%d3

    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b
    movem.l  (%sp)+,%d3/%a2-%a4
0:
    rts

2:
    lea      30(%a0),%a0
    lea      30(%a1),%a1
3:
    moveq.l  #-1,%d3
    move.b   (%a4)+,%d3
    rol.w    %d1,%d3

    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    and.w    %d3,(%a0)
    or.w     %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a3)+,%d0
    lsl.w    %d1,%d0
    and.w    %d3,(%a1)
    or.w     %d0,(%a1)

    dbf      %d2,2b

    movem.l  (%sp)+,%d3/%a2-%a4
    rts
