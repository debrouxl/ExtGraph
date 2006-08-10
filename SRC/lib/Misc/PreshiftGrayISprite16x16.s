| C prototype: void PreshiftGrayISprite16x16(unsigned short *src asm("%a0"),unsigned long *dest asm("%a1"));

.text
.globl PreshiftGrayISprite16x16
.even

PreshiftGrayISprite16x16:
    lea.l    14*8*2*4(%a1),%a1

    moveq.l  #2*16-1,%d2

0:
    moveq.l  #0,%d0
    move.w   (%a0)+,%d0

    moveq.l  #8-1,%d1

1:
    lsl.l    #2,%d0
    move.l   %d0,(%a1)
    lea.l    -16*2*4(%a1),%a1

    dbf      %d1,1b

    lea.l    16*8*2*4+4(%a1),%a1

    dbf      %d2,0b

    rts
