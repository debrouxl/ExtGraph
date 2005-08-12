| C prototype: void SpriteX8_MIRROR_HV_R(register short h asm("%d0"),register unsigned char* src asm("%a0"),register short bytewidth asm("%d1"),register unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

| A slightly modified SpriteX8_MIRROR_H_R.

.text
.globl SpriteX8_MIRROR_HV_R
.even

SpriteX8_MIRROR_HV_R:
    dbf      %d0,4f
    rts

4:
    tst.w    %d1
    beq.s    2f

    movem.l  %d3-%d5,-(%sp)

| MIRROR_V: store sprite in reverse order.
    move.w   %d0,%d5
    addq.w   #1,%d5
    mulu.w   %d1,%d5
    adda.w   %d5,%a1
    

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

    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5

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
