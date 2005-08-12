| C prototype: void GraySprite32_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned long *sprt0,unsigned long *sprt1,register unsigned long maskval asm("%d3"),register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite32_BLIT_R
.even

GraySprite32_BLIT_R:
    dbf      %d2,0f
    rts

0:
    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    move.l   4+28(%sp),%a2
    move.l   4+28+4(%sp),%a3
    move.l   %d3,%d6

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

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
