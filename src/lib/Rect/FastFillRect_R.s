| C prototype: void FastFillRect_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_XOR, A_NORMAL, A_REPLACE. In fact, 
| A_NORMAL (same effect as A_REPLACE) is assumed if the mode is neither
| A_REVERSE nor A_XOR.
|
| This piece of code uses the nasty trick of code patching so as to be much
| smaller and also faster if the mode is not changed too often.
| What's more, given that the following opcodes:
| or.w %d0,(%a0)     0x8150
| eor.w %d0,(%a0)    0xB150
| and.w %d0,(%a0)    0xC150
|
| or.w %d1,(%a0)     0x8350
| eor.w %d1,(%a0)    0xB350
| and.w %d1,(%a0)    0xC350
|
| are mainly similar, we can optimize...
|
| However, there is nothing to optimize on the following opcodes:
| move.l %d5,(%a0)   0x2085
| move.w %d5,(%a0)   0x3085
| not.l (%a0)        0x4690
| not.w (%a0)        0x4650

.text
.even

0:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

1:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.text
.globl FastFillRect_R
.even
FastFillRect_R:
    movem.l  %d3-%d5,-(%sp)
    
    cmp.w    %d1,%d3
    bge.s    2f

    exg      %d1,%d3

2:
    sub.w    %d1,%d3                         | dy.

    cmp.w    %d0,%d2
    bge.s    2f
    exg      %d0,%d2
  
2:
    move.w   %d1,%d4
    lsl.w    #4,%d1
    sub.w    %d4,%d1
    move.w   %d0,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d1   | always word-aligned to avoid address error problems.
    add.w    %d1,%d1
    adda.w   %d1,%a0
| a0=address of the top left corner of the rectangle.

    andi.w   #0xF,%d0
    add.w    %d0,%d0
| The code was optimized and reordered so that d(pc,ix) mode can be used.
    move.w   0b(%pc,%d0.w),%d0    | d0 = mask of first pixels.

    move.w   %d2,%d1                           | x2 is stored in d1.
    andi.w   #0xF,%d1
    add.w    %d1,%d1
    move.w   1b(%pc,%d1.w),%d1     | d1 = mask of last pixels.

| d4 = 8 * (x1/16 + x1/16) + 16. We add 1 before shifting instead of adding 16 
| after shifting (gain: 4 clocks and 2 bytes).
    addq.w   #1,%d4
    lsl.w    #4,%d4

    | If mode is not A_REVERSE or A_XOR, A_NORMAL is assumed. That allows
    | the use of A_REPLACE and A_OR modes.
    move.w   4+12(%sp),%d5
    cmp.w    2f(%pc),%d5
    beq.s    __no_p_FFR_R__
    lea      __First_part_FFR_R__(%pc),%a1

    move.w   %d5,2f-__First_part_FFR_R__(%a1)
    beq.s    __p_clr_FFR_R__
    subq.w   #2,%d5
    beq.s    __p_eor_FFR_R__
    moveq    #-0x7F,%d5                      | -0x7F = 0x81.
    bra.s    __p_clr_and_or_FFR_R__
__p_clr_FFR_R__:
    moveq    #-0x3F,%d5                      | -0x3F = 0xC1.
__p_clr_and_or_FFR_R__:
    move.w   #0x2085,__Middle_32_FFR_R__-__First_part_FFR_R__(%a1)
    move.w   #0x3085,_Middle_16_FFR_R__-__First_part_FFR_R__(%a1)

    bra.s    __end_p_FFR_R__
__p_eor_FFR_R__:
    moveq    #-0x4F,%d5                      | -0x4F = 0xB1.
    move.w   #0x4690,__Middle_32_FFR_R__-__First_part_FFR_R__(%a1)
    move.w   #0x4650,_Middle_16_FFR_R__-__First_part_FFR_R__(%a1)

__end_p_FFR_R__:
    move.b   %d5,(%a1)
    addq.b   #2,%d5
    move.b   %d5,__End_FFR_R__-__First_part_FFR_R__(%a1)

__no_p_FFR_R__:
    move.w   2f(%pc),%d5
    bne.s    __not_A_REVERSE_FFR_R__
    not.w    %d0
    not.w    %d1
    moveq    #0,%d5 | or ext.l %d5
    bra.s    __How_long_is_the_line_FFR_R__
__not_A_REVERSE_FFR_R__:
    moveq    #-1,%d5

__How_long_is_the_line_FFR_R__:
    cmp.w    %d4,%d2                         | All pixels in the same word ?
    bge.s    __More_than_16_pixels_FFR_R__
| Instead of coding a complete and quite long block testing for mode and
| writing to the plane accordingly, we can simply branch to __End_FFR_R__ after
| doing the necessary operations. This is both faster and smaller...
    tst.w    %d5
    bne.s    __not_A_REVERSE_FFR_R_2__
    or.w     %d0,%d1
    bra.s    __short_line_FFR_R__
| Don't forget to invert the masks for A_REVERSE mode !
__not_A_REVERSE_FFR_R_2__:
    and.w    %d0,%d1
__short_line_FFR_R__:
    move.w   %d3,%d4
    bra.s    __End_FFR_R__

__More_than_16_pixels_FFR_R__:
    sub.w    %d4,%d2                         | d2 = x2 - x.
_First_part_FFR_R__:
    move.w   %d3,%d4
    movea.l  %a0,%a1
__First_part_FFR_R__:
    .word    0x0050
    lea      30(%a0),%a0
    dbf      %d3,__First_part_FFR_R__

    addq.l   #2,%a1
    movea.l  %a1,%a0
    move.w   %d4,%d3
    subi.w   #32,%d2
    blt.s    __Middle_16_FFR_R__
__Middle_32_FFR_R__:
    .word    0
    lea      30(%a0),%a0
    dbf      %d3,__Middle_32_FFR_R__
    addq.l   #4,%a1
    movea.l  %a1,%a0
    move.w   %d4,%d3
    subi.w   #32,%d2
    bge.s    __Middle_32_FFR_R__
__Middle_16_FFR_R__:
    cmpi.w   #-16,%d2
    blt.s    __End_FFR_R__
_Middle_16_FFR_R__:
    .word    0
    lea      30(%a0),%a0
    dbf      %d3,_Middle_16_FFR_R__
    lea      2(%a1),%a0
__End_FFR_R__:
    .word    0x0050
    lea      30(%a0),%a0
    dbf      %d4,__End_FFR_R__

    movem.l  (%sp)+,%d3-%d5
    rts

2:
.word 0xFFFF
