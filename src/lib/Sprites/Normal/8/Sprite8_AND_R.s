| C prototype: void Sprite8_AND_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short h asm("%d2"), const unsigned char *sprt asm("%a1"), void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl Sprite8_AND_R
.even

Sprite8_AND_R:
    subq.w   #1,%d2
    blt.s    0f

    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d2

    add.w    %d2,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0

    swap     %d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    2f

    neg.w    %d1
1:
    moveq    #-1,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    ror.l    %d1,%d0
    and.l    %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b
    rts

3:
    lea      30(%a0),%a0
2:
    moveq    #-1,%d0
    move.b   (%a1)+,%d0
    rol.w    %d1,%d0
    and.w    %d0,(%a0)
    dbf      %d2,3b
0:
    rts
