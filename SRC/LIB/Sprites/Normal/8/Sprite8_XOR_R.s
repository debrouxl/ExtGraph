| C prototype: void Sprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt asm("%a1"),void *dest asm("%a0"));

.text
.globl Sprite8_XOR_R
.even

Sprite8_XOR_R:
    dbf    %d2,0f
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

    swap     %d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    eor.l    %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b
    rts

2:
    lea      30(%a0),%a0
3:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    eor.w    %d0,(%a0)
    dbf      %d2,2b
    rts
