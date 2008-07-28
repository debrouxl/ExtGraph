| C prototype: void SpriteX8_MIRROR_H_R(unsigned short h asm("%d0"), const unsigned char* src asm("%a0"), unsigned short bytewidth asm("%d1"), unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));
|
| This routine is ~3 times faster than the previous C routine (the algorithm
| is different).

.text
.globl SpriteX8_MIRROR_H_R
.even

SpriteX8_MIRROR_H_R:
    dbf      %d0,4f
    rts

4:
    tst.w    %d1
    beq.s    2f

    movem.l  %d3-%d6,-(%sp)

| Adding 2 * bytewidth is needed, due to the way the data is stored to the
| destination sprite.
| 2 * bytewidth is computed once at the beginning (+ 8 clocks). It clobbers 1
| more register, so saving/restoring the registers is slower (+ 2 * 8 clocks).
| But, having 2 * bytewidth computed saves 8 clocks each time the innermost
| loop is finished. This (theoretically) means that this version is faster
| when h > 3, which should be the case most of the time...
    adda.w   %d1,%a1
    move.w   %d1,%d6
    add.w    %d6,%d6

    moveq    #0,%d3
    moveq    #0,%d4

0:
    move.w   %d1,%d2              | i (counter) = bytewidth;
    subq.w   #1,%d2               | i-- (for dbf).

1:
    move.b   (%a0)+,%d3
    move.b   %d3,%d4
    andi.b   #0xF,%d3
    lsr.b    #4,%d4

    move.b   3f(%pc,%d3.w),%d5
    lsl.b    #4,%d5
    or.b     3f(%pc,%d4.w),%d5

    move.b   %d5,-(%a1)

    dbf      %d2,1b

    adda.w   %d6,%a1

    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d6

2:
    rts

3:
    .byte 0x0
    .byte 0x8
    .byte 0x4
    .byte 0xC
    .byte 0x2
    .byte 0xA
    .byte 0x6
    .byte 0xE
    .byte 0x1
    .byte 0x9
    .byte 0x5
    .byte 0xD
    .byte 0x3
    .byte 0xB
    .byte 0x7
    .byte 0xF
