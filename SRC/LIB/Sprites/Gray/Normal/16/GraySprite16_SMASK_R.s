| C prototype: void GraySprite16_SMASK_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned short *sprt0,unsigned short *sprt1,unsigned short *mask,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl GraySprite16_SMASK_R
.even

GraySprite16_SMASK_R:
    dbf      %d2,0f
    rts

0:
    movem.l  %d3/%a2-%a4,-(%sp)

    lea.l    4+16(%sp),%a4
    movea.l  (%a4)+,%a2
    movea.l  (%a4)+,%a3
    movea.l  (%a4),%a4

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    moveq    #15,%d3
    and.w    %d0,%d3
    lsr.w    #4,%d0

    add.w    %d0,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0
    adda.w   %d1,%a1

    moveq.l  #16,%d1
    sub.w    %d3,%d1

1:
    moveq.l  #-1,%d3
    move.w   (%a4)+,%d3
    rol.l    %d1,%d3

    moveq.l  #0,%d0
    move.w   (%a2)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a0)
    or.l     %d0,(%a0)

    moveq.l  #0,%d0
    move.w   (%a3)+,%d0
    lsl.l    %d1,%d0
    and.l    %d3,(%a1)
    or.l     %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b

    movem.l  (%sp)+,%d3/%a2-%a4
    rts
