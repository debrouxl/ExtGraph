| C prototype: void GraySprite32_TRANB_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned long *sprt0, const unsigned long *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite32_TRANB_R
.even

GraySprite32_TRANB_R:
    subq.w   #1,%d2
    blt.s    0f

    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    move.l   4+28(%sp),%a2
    move.l   4+28+4(%sp),%a3

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*PLANE_BYTE_WIDTH (even)
    adda.w   %d3,%a0
    adda.w   %d3,%a1

    andi.w   #15,%d0          | d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.l   %d3,%d4
    not.l    %d4

1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.l   (%a3)+,%d5
    rol.l    %d1,%d5

    move.l   %d0,%d6
    and.l    %d5,%d6
    move.l   %d6,%d7
    not.l    %d7

    and.l    %d7,%d0
    and.l    %d7,%d5

    move.w   %d6,%d7
    or.w     %d3,%d7
    or.l     %d4,%d6
    and.w    %d7,(%a0)+
    and.w    %d7,(%a1)+
    and.l    %d6,(%a0)
    and.l    %d6,(%a1)

    move.w   %d0,%d6
    and.l    %d3,%d0
    or.l     %d0,(%a0)
    and.w    %d4,%d6
    or.w     %d6,-(%a0)

    move.w   %d5,%d6
    and.l    %d3,%d5
    or.l     %d5,(%a1)
    and.w    %d4,%d6
    or.w     %d6,-(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
0:
    rts


/*
1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.l   (%a3)+,%d5
    rol.l    %d1,%d5

    move.l   %d0,%d6
    and.l    %d5,%d6
    move.l   %d6,%d7
    not.l    %d7

    and.l    %d7,%d0
    and.l    %d7,%d5

    move.w   %d6,%d7
    or.w     %d3,%d7
    or.l     %d4,%d6
    and.w    %d7,(%a0)+
    and.w    %d7,(%a1)+
    and.l    %d6,(%a0)
    and.l    %d6,(%a1)

    move.w   %d0,%d6
    and.l    %d3,%d0
    or.l     %d0,(%a0)
    and.w    %d4,%d6
    or.w     %d6,-(%a0)

    move.w   %d5,%d6
    and.l    %d3,%d5
    or.l     %d5,(%a1)
    and.w    %d4,%d6
    or.w     %d6,-(%a1)

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b
*/
