| C prototype: void Sprite8_MASK(short x,short y,short h,unsigned char *sprt,unsigned char *mask,void *dest) __attribute__((__stkparm__);

.text
.globl Sprite8_MASK
.even

Sprite8_MASK:
    move.l   %a2,-(%sp)

    lea.l    4+4(%sp),%a0
    move.w   (%a0)+,%d0
    move.w   (%a0)+,%d1
    addq.l   #2,%a0
    movea.l  (%a0)+,%a1
    movea.l  (%a0)+,%a2
    movea.l  (%a0),%a0

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1

    adda.w   %d1,%a0

    move.w   4+4+4(%sp),%d2
    beq.s    0f

    subq.w   #1,%d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq.l  #-1,%d0
    move.b   (%a2)+,%d0
    swap     %d0
    ror.l    %d1,%d0
    and.l    %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b

    movea.l  (%sp)+,%a2
    rts

2:
    lea      30(%a0),%a0
3:
    moveq.l  #-1,%d0
    move.b   (%a2)+,%d0
    rol.w    %d1,%d0
    and.w    %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)
    dbf      %d2,2b

0:
    movea.l  (%sp)+,%a2
    rts
