| C prototype: void FastDrawHLine(void* plane, unsigned short x1, unsigned short x2, unsigned short y, short mode) __attribute__((__stkparm__));
| Valid values for mode are: A_REVERSE, A_NORMAL, A_XOR, A_REPLACE, A_OR.
|
| This routine draws a horizontal line from (x1;y) to (x2;y).
| This is the version which receives its parameters on the stack.

.text
.even
0:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

1:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.globl FastDrawHLine
FastDrawHLine:
    move.l   %d3,%a1                         | d3 mustn't be destroyed.

    movea.l  4+0(%sp),%a0
    move.w   4+4(%sp),%d0
    move.w   4+6(%sp),%d1
    move.w   4+8(%sp),%d2
    
    cmp.w    %d0,%d1
    bge.s    2f

    exg      %d0,%d1

2:
    move.w   %d2,%d3
    lsl.w    #4,%d2
    sub.w    %d3,%d2
    move.w   %d0,%d3
    lsr.w    #4,%d3
    add.w    %d3,%d2
    add.w    %d2,%d2
    adda.w   %d2,%a0

| d3 = 8 * (x1/16 + x1/16) + 16. We add 1 before shifting instead of adding 16 
| after shifting (gain: 4 clocks and 2 bytes).
    addq.w   #1,%d3                          | d3 = 8 * (x1/16 + x1/16) + 16.
    lsl.w    #4,%d3
    move.w   %d1,%d2                         | x2 is stored in d2.
    andi.w   #0xF,%d0

    add.w    %d0,%d0
    move.w   0b(%pc,%d0.w),%d0 | d0 = mask of first pixels.
    andi.w   #0xF,%d1

    add.w    %d1,%d1
    move.w   1b(%pc,%d1.w),%d1     | d1 = mask of last pixels.
    cmp.w    %d3,%d2                         | All pixels in the same word ?
    blt.s    4f
    sub.w    %d3,%d2                         | d2 = x2 - x.
    move.w   4+10(%sp),%d3
    beq.s    0f
    subq.w   #2,%d3
    beq.s    2f

| A_NORMAL / A_OR / A_REPLACE.
    moveq.l  #32,%d3
    or.w     %d0,(%a0)+
    moveq    #-1,%d0
    sub.w    %d3,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    sub.w    %d3,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    7f
    move.w   %d0,(%a0)+
7:
    or.w     %d1,(%a0)
    move.l   %a1,%d3
    rts

| A_REVERSE.
0:
    moveq.l  #32,%d3
    not.w    %d0
    and.w    %d0,(%a0)+
    moveq    #0,%d0
    sub.w    %d3,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    sub.w    %d3,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    8f
    move.w   %d0,(%a0)+
8:
    not.w    %d1
    and.w    %d1,(%a0)
    move.l   %a1,%d3
    rts

| A_XOR.
2:
    moveq.l  #32,%d3
    eor.w    %d0,(%a0)+
    sub.w    %d3,%d2
    blt.s    5f
6:
    not.l    (%a0)+
    sub.w    %d3,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    9f
    not.w    (%a0)+
9:
    eor.w    %d1,(%a0)
    move.l   %a1,%d3
    rts

4:
    and.w    %d0,%d1
    move.w   4+10(%sp),%d3
    beq.s    8b
    subq.w   #2,%d3
    beq.s    9b
    or.w     %d1,(%a0)
    move.l   %a1,%d3
    rts
