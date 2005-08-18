| C prototype: void Sprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned short *sprt asm("%a1"),void *dest asm("%a0"));

.text
.globl Sprite16_OR_R
.even

Sprite16_OR_R:
    dbf      %d2,0f
    rts

0:
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

_loop_Sprite16_OR_R:
    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,_loop_Sprite16_OR_R

    rts
