| C prototype: void Sprite8_OR_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),register void *dest asm("%a0"));

.text
.globl Sprite8_OR_R
.even

Sprite8_OR_R:
    dbf    %d2,0f
    rts

0:
    swap     %d2

    move.w   %d1,%d2	| d2 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d2,%d1	| d1 = 15*y

    move.w   %d0,%d2	| d2 = x
    lsr.w    #4,%d2	| d2 = x/16

    add.w    %d2,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8
    adda.w   %d1,%a0	| a0 += offset

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
    or.l     %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b
    rts

2:
    lea      30(%a0),%a0
3:
    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.w    %d1,%d0
    or.w     %d0,(%a0)
    dbf      %d2,2b
    rts