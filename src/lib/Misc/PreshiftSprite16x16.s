| C prototype: extern void PreshiftSprite16x16(register const unsigned short *src asm("%a0"),register unsigned long *dest asm("%a1"));

.text
.globl PreshiftSprite16x16
.even

PreshiftSprite16x16:
    lea.l    7*8*2*4(%a1),%a1

    moveq.l  #16-1,%d2

0:
    moveq.l  #0,%d0
    move.w   (%a0)+,%d0

    moveq.l  #8-1,%d1

1:
    lsl.l    #2,%d0
    move.l   %d0,(%a1)
    lea.l    -16*2*2(%a1),%a1

    dbf      %d1,1b

    lea.l    8*8*2*4+4(%a1),%a1

    dbf      %d2,0b

    rts
