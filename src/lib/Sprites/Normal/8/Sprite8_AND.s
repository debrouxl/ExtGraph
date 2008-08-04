| C prototype: void Sprite8_AND(unsigned short x, unsigned short y, unsigned short height, const unsigned char *sprt, void *dest) __attribute__((__stkparm__));
|
| This routine is faster (about 20%) than the previous C routine, because the
| algorithm was changed.

.text
.globl Sprite8_AND
.even

Sprite8_AND:
    move.w   0+4+0(%sp),%d0
    move.w   0+4+2(%sp),%d1
    movea.l  0+4+6(%sp),%a1

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    movea.w  %d0,%a0
    adda.l   0+4+10(%sp),%a0

    andi.w   #0xF,%d2
    moveq    #8,%d1
    sub.w    %d2,%d1

    move.w   0+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    tst.w    %d1
    bge.s    2f

    neg.w    %d1
1:
    moveq    #-1,%d0
    and.b    (%a1)+,%d0
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
    and.b    (%a1)+,%d0
    rol.w    %d1,%d0
    and.w    %d0,(%a0)
    dbf      %d2,3b

0:
    rts
