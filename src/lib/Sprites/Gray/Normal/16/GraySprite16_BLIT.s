| C prototype: void GraySprite16_BLIT(unsigned short x, unsigned short y, unsigned short height, const unsigned short* sprite1, const unsigned short* sprite2, const unsigned short maskval, void* dest1, void* dest2) __attribute__((__stkparm__));

.text
.globl GraySprite16_BLIT
.even

GraySprite16_BLIT:
    movem.l  %d3/%a2-%a3,-(%sp)

    lea.l    4+12(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    move.w   (%a1)+,%d2
    beq.s    0f
    movea.l  (%a1)+,%a2
    movea.l  (%a1)+,%a3
    addq.l   #2,%a1
    movea.l  (%a1)+,%a0
    movea.l  (%a1),%a1

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    move.w   %d0,%d3
    lsr.w    #4,%d3

    add.w    %d3,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0
    adda.w   %d1,%a1

    subq.w   #1,%d2

    and.w    #15,%d0
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    move.w   4+12+14(%sp),%d3
    rol.l    %d1,%d3

1:
    moveq.l  #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)
    lea.l    PLANE_BYTE_WIDTH(%a0),%a0

    moveq.l  #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1

    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3/%a2-%a3
    rts
