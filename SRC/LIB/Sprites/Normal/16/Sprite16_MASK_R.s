| C prototype: void Sprite16_MASK_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned short *sprt asm("%a1"),unsigned short *mask,register void *dest asm("%a0")) __attribute__((__stkparm__));

.text
.globl Sprite16_MASK_R
.even

Sprite16_MASK_R:
    dbf      %d2,0f
    rts

0:
    move.l   %a2,-(%sp)

    move.l   4+4(%sp),%a2

    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

    swap     %d2

1:
    moveq.l  #-1,%d0
    move.w   (%a2)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,(%a0)

    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)

    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%a2
    rts
