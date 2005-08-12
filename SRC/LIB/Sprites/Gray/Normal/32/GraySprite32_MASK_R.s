| C prototype: void GraySprite32_MASK_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned long *sprt0,unsigned long *sprt1,unsigned long *mask0,unsigned long *mask1,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite32_MASK_R
.even

GraySprite32_MASK_R:
    dbf      %d2,0f
    rts

0:
    movem.l  %d3-%d5/%a2-%a5,-(%sp)

    lea.l    4+28(%sp),%a5
    movea.l  (%a5)+,%a2
    movea.l  (%a5)+,%a3
    movea.l  (%a5)+,%a4
    movea.l  (%a5),%a5

|    move.l   4+28(%sp),%a2
|    move.l   4+28+4(%sp),%a3
|    move.l   4+28+4+4(%sp),%a4
|    move.l   4+28+4+4+4(%sp),%a5

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*30 (nb pair)
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

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    dbf      %d2,1b

    movem.l  (%sp)+,%d3-%d5/%a2-%a5
    rts
