| C prototype: void Sprite16_XOR(unsigned short x, unsigned short y, unsigned short h, const unsigned short *sprt, void *dest) __attribute__((__stkparm__));
|
| This routine is faster (about 10%) than the previous C routine, because the
| algorithm was changed.
| An optimization (4 clocks) was made by Ximoon, jackiechan told me about it.

.text
.globl Sprite16_XOR
.even

Sprite16_XOR:
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
    moveq    #16,%d1
    sub.w    %d2,%d1

    move.w   0+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

1:
    moveq    #0,%d0
    move.w   (%a1)+,%d0
    lsl.l    %d1,%d0
    eor.l    %d0,(%a0)
    lea      30(%a0),%a0
    dbf      %d2,1b

0:
    rts
