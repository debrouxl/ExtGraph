| C prototype: void Sprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt asm("%a1"),unsigned char maskval asm("%d3"),void *dest asm("%a0"));

.text
.globl Sprite8_BLIT_R
.even

Sprite8_BLIT_R:
    dbf    %d2,0f
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

    moveq.l  #-1,%d4
    move.b   %d3,%d4

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    3f

    neg.w    %d1
    swap     %d4
    ror.l    %d1,%d4
1:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap     %d0
    lsr.l    %d1,%d0
    and.l    %d4,(%a0)
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b

    move.l   (%sp)+,%d4
    rts

3:
    rol.w    %d1,%d4
2:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    and.w    %d4,(%a0)
    or.w     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,2b

    move.l   (%sp)+,%d4
    rts
