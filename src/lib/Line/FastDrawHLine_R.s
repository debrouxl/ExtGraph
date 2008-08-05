| C prototype: void FastDrawHLine_R(void* plane asm("a0"), unsigned short x1 asm("d0"), unsigned short x2 asm("d1"), unsigned short y asm("d2"), short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_NORMAL, A_XOR, A_REPLACE, A_OR.
|
| This routine draws a horizontal line from (x1;y) to (x2;y).
| This is the version which receives most parameters in the registers, not
| on the stack. plane goes in a0, x1 in d0, x2 in d1, y in d2, mode on the
| stack.

.text
.even
0:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

1:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.globl FastDrawHLine_R
FastDrawHLine_R:
    move.l   %d4,%a1                         | d4 mustn't be destroyed.

    cmp.w    %d0,%d1
    bge.s    2f

    exg      %d0,%d1

2:
    move.w   %d2,%d4
    lsl.w    #4,%d2
    sub.w    %d4,%d2
    move.w   %d0,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d2
    add.w    %d2,%d2
    adda.w   %d2,%a0

| d4 = 8 * (x1/16 + x1/16) + 16. We add 1 before shifting instead of adding 16 
| after shifting (gain: 4 clocks and 2 bytes).
    addq.w   #1,%d4                          | d4 = 8 * (x1/16 + x1/16) + 16.
    lsl.w    #4,%d4

    move.w   %d1,%d2                         | x2 is stored in d2.
    andi.w   #0xF,%d0

    add.w    %d0,%d0
    move.w   0b(%pc,%d0.w),%d0 | d0 = mask of first pixels.
    andi.w   #0xF,%d1

    add.w    %d1,%d1
    move.w   1b(%pc,%d1.w),%d1   | d1 = mask of last pixels.
    cmp.w    %d4,%d2                         | All pixels in the same word ?
    blt.s    4f
    sub.w    %d4,%d2                         | d2 = x2 - x.
    moveq.l  #32,%d4
    tst.w    4(%sp)
    beq.s    0f
    subq.w   #2,4(%sp)                       | from cmpi.w #2,4(%sp)
    beq.s    2f

| A_NORMAL / A_OR / A_REPLACE.
    or.w     %d0,(%a0)+
    moveq    #-1,%d0
    sub.w    %d4,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    7f
    move.w   %d0,(%a0)+
7:
    or.w     %d1,(%a0)
    move.l   %a1,%d4
    rts

| A_REVERSE.
0:
    not.w    %d0
    and.w    %d0,(%a0)+
    moveq    #0,%d0
    sub.w    %d4,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    8f
    move.w   %d0,(%a0)+
8:
    not.w    %d1
    and.w    %d1,(%a0)
    move.l   %a1,%d4
    rts

2:
    eor.w    %d0,(%a0)+
    sub.w    %d4,%d2
    blt.s    5f
6:
    not.l    (%a0)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    9f
    not.w    (%a0)+
9:
    eor.w    %d1,(%a0)
    move.l   %a1,%d4
    rts

4:
    and.w    %d0,%d1
    tst.w    4(%sp)
    beq.s    8b
    subq.w   #2,4(%sp)
    beq.s    9b
    or.w     %d1,(%a0)
    move.l   %a1,%d4
    rts
