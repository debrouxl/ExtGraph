| C prototype: void GraySprite32_XOR(short x,short y,short h,unsigned long *sprt0,unsigned long *sprt1,void *dest0,void *dest1) __attribute__((__stkparm__));

.text
.globl GraySprite32_XOR
.even

GraySprite32_XOR:
    movem.l  %d3-%d5/%a2-%a3,-(%sp)

    lea.l    4+20(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    move.w   (%a1)+,%d2
    beq.s    0f
    movea.l  (%a1)+,%a2
    movea.l  (%a1)+,%a3
    movea.l  (%a1)+,%a0
    movea.l  (%a1),%a1

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1          | d1=y*15
    move.w   %d0,%d3
    lsr.w    #4,%d3           | d3=x/16
    add.w    %d1,%d3          | d3=x/16+y*15
    add.w    %d3,%d3          | d3=x/8+y*30 (nb pair)

    adda.w   %d3,%a0
    adda.w   %d3,%a1

    subq.w   #1,%d2

    andi.w   #15,%d0          | d0=rightshift
    moveq.l  #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d3
    lsl.l    %d1,%d3
    move.w   %d3,%d4
    not.w    %d4
1:
    move.l   (%a2)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.w    %d4,%d5
    eor.w    %d5,(%a0)+
    and.l    %d3,%d0
    eor.l    %d0,(%a0)

    move.l   (%a3)+,%d0
    rol.l    %d1,%d0
    move.w   %d0,%d5
    and.w    %d4,%d5
    eor.w    %d5,(%a1)+
    and.l    %d3,%d0
    eor.l    %d0,(%a1)

    lea.l    28(%a0),%a0
    lea.l    28(%a1),%a1
    dbf      %d2,1b

0:
    movem.l  (%sp)+,%d3-%d5/%a2-%a3
    rts
