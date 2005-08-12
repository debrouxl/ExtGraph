| C prototype: void Sprite16_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned short *sprt asm("%a1"),register unsigned short maskval asm("%d3"),register void *dest asm("%a0"));

.text
.globl Sprite16_BLIT_R
.even

Sprite16_BLIT_R:
    dbf      %d2,0f
    rts

0:
    move.l   %d4,-(%sp)

    move.w   %d1,%d4
    lsl.w    #4,%d1
    sub.w    %d4,%d1

    move.w   %d0,%d4
    lsr.w    #4,%d4

    add.w    %d4,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    and.w    #0xF,%d0
    moveq    #16,%d1
    sub.w    %d0,%d1

    moveq.l  #-1,%d4
    move.w   %d3,%d4
    rol.l    %d1,%d4

1:
    moveq    #0,%d0 | 4
    move.w   (%a1)+,%d0 | 8
    lsl.l    %d1,%d0
    and.l    %d4,(%a0) | 20
    or.l     %d0,(%a0) | 20

| 52 + shift.
    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d4
    rts
