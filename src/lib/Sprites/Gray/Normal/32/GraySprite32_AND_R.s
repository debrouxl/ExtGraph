| C prototype: void GraySprite32_AND_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned long *sprt0, const unsigned long *sprt1, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite32_AND_R
.even

GraySprite32_AND_R:
    subq.w   #1,%d2
    blt.s    0f

    movem.l  %d3-%d5/%a2-%a3,-(%sp)

    move.l   4+20(%sp),%a2
    move.l   4+20+4(%sp),%a3

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*PLANE_BYTE_WIDTH (nb pair)
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
    move.w   %d0,%d5
    or.w     %d3,%d5
    and.w    %d5,(%a0)+
    or.l     %d4,%d0
    and.l    %d0,(%a0)

    move.l   (%a3)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    or.w     %d3,%d5
    and.w    %d5,(%a1)+
    or.l     %d4,%d0
    and.l    %d0,(%a1)

    lea.l    28(%a0),%a0
    lea.l    28(%a1),%a1
    dbf      %d2,1b

    movem.l  (%sp)+,%d3-%d5/%a2-%a3
0:
    rts
