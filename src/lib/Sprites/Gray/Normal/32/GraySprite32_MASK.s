| C prototype: void GraySprite32_MASK(unsigned short x, unsigned short y, unsigned short height, const unsigned long* sprite1, const unsigned long* sprite2, const unsigned long* mask1, const unsigned long* mask2, void* dest1, void* dest2) __attribute__((__stkparm__));

.text
.globl GraySprite32_MASK
.even

GraySprite32_MASK:
    movem.l  %d3-%d5/%a2-%a5,-(%sp)

    lea.l    4+28(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    move.w   (%a1)+,%d2
    beq.s    0f
    movea.l  (%a1)+,%a2
    movea.l  (%a1)+,%a3
    movea.l  (%a1)+,%a4
    movea.l  (%a1)+,%a5
    movea.l  (%a1)+,%a0
    movea.l  (%a1),%a1

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*PLANE_BYTE_WIDTH (nb pair)

    adda.w   %d3,%a0
    adda.w   %d3,%a1

    subq.w   #1,%d2

    andi.w   #15,%d0          | d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.l   %d3,%d4
    not.l    %d4
1:
    move.l   (%a4)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    or.w     %d3,%d5
    and.w    %d5,(%a0)+
    or.l     %d4,%d0
    and.l    %d0,(%a0)

    move.l   (%a5)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    or.w     %d3,%d5
    and.w    %d5,(%a1)+
    or.l     %d4,%d0
    and.l    %d0,(%a1)

    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    or.l     %d0,(%a0)
    and.w    %d4,%d5
    or.w     %d5,-(%a0)

    move.l   (%a3)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    or.l     %d0,(%a1)
    and.w    %d4,%d5
    or.w     %d5,-(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3-%d5/%a2-%a5
    rts
