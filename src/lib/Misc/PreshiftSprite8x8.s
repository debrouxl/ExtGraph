| C prototype: void PreshiftSprite8x8(register unsigned char *src asm("%a0"),register unsigned long *dest asm("%a1"));

.globl PreshiftSprite8x8
.even

PreshiftSprite8x8:
    lea.l    7*8*4(%a1),%a1

    moveq.l  #8-1,%d2

0:
    moveq.l  #0,%d0
    move.w   (%a0)+,%d0

    moveq.l  #7-1,%d1

1:
    move.l   %d0,(%a1)
    lsl.l    #2,%d0
    lea.l    -16*2(%a1),%a1

    dbf      %d1,1b

    lea.l    7*16*4+4(%a1),%a1

    dbf      %d2,0b

    rts
