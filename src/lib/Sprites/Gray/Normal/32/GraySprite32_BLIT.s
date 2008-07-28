| C prototype: void GraySprite32_BLIT(unsigned short x, unsigned short y, unsigned short h, const unsigned long* sprite1, const unsigned long* sprite2, const unsigned long maskval, void* dest1, void* dest2) __attribute__((__stkparm__));

.text
.globl GraySprite32_BLIT
.even

GraySprite32_BLIT:
    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    lea.l    4+28(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    move.w   (%a1)+,%d2
    beq.s    0f
    move.l   (%a1)+,%a2
    move.l   (%a1)+,%a3
    move.l   (%a1)+,%d6
    move.l   (%a1)+,%a0
    move.l   (%a1),%a1

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*30 (even)
    adda.w   %d3,%a0
    adda.w   %d3,%a1

    andi.w   #15,%d0          | d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.l   %d3,%d4
    not.l    %d4

    rol.l    %d1,%d6
    move.w   %d6,%d7
    or.l     %d4,%d6
    or.w     %d3,%d7

    subq.w   #1,%d2
1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    and.w    %d4,%d5
    and.w    %d7,(%a0)
    or.w     %d5,(%a0)+
    and.l    %d6,(%a0)
    or.l     %d0,(%a0)

    move.l   (%a3)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.l    %d3,%d0
    and.w    %d4,%d5
    and.w    %d7,(%a1)
    or.w     %d5,(%a1)+
    and.l    %d6,(%a1)
    or.l     %d0,(%a1)

    lea.l    28(%a0),%a0
    lea.l    28(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
