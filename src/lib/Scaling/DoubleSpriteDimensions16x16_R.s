| C prototype: void DoubleSpriteDimensions16x16_R(const unsigned short* src asm("%a0"), unsigned long* dest asm("%a1")) __attribute__((__regparm__(2)));

.text
.globl DoubleSpriteDimensions16x16_R
.even

DoubleSpriteDimensions16x16_R:
    move.l   %d3,-(%sp)

    moveq    #16-1,%d2
0:
    move.w   (%a0)+,%d0
    moveq    #8-1,%d3

1:
| Loop is unrolled twice, so that speed is increased (by ~1/6) while size
| is increased by only 6 bytes. Optimizing for size at all costs would be
| stupid here...
| Algorithm posted on the official TIGCC/TICT board by Kevin Kofler. It uses
| the fact asr repeats the leftmost bit.
    lsr.w    #1,%d0
    roxr.l   #1,%d1
    asr.l    #1,%d1

    lsr.w    #1,%d0
    roxr.l   #1,%d1
    asr.l    #1,%d1
    dbf      %d3,1b
    move.l   %d1,(%a1)+
    move.l   %d1,(%a1)+

    dbf      %d2,0b

    move.l   (%sp)+,%d3
    rts
