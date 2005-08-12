| C prototype : void GrayFastDrawHLine2B_R(short x0 asm("%d0"),short x1 asm("%d1"),short y asm("%d2"),short color asm("%d3"),void *light_plane asm("%a0"),void *dark_plane asm("%a1"));

.text
.even
0:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

1:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.globl GrayFastDrawHLine2B_R
GrayFastDrawHLine2B_R:
    move.l   %d4,-(%sp)                      | d4 mustn't be destroyed.

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
    adda.w   %d2,%a1

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
    sub.w    %d4,%d2             | All pixels in the same word ?
    blt.s    4f
    move.w   %d3,%d4 | color
    beq.s    0f
    subq.w   #2,%d4
    bmi.s    1f
    beq.s    2f

| Black.
    moveq.l  #32,%d4
    or.w     %d0,(%a0)+
    or.w     %d0,(%a1)+
    moveq    #-1,%d0
    sub.w    %d4,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    7f
    move.w   %d0,(%a0)+
    move.w   %d0,(%a1)+
7:
    or.w     %d1,(%a0)
    or.w     %d1,(%a1)
    move.l   (%sp)+,%d4
    rts

| All pixels in the same word.
4:
    and.w    %d0,%d1
    move.w   %d3,%d2 | color
    beq.s    8f
    subq.w   #2,%d2
    bmi.s    9f
    bne.s    7b
    exg      %a0,%a1
    bra.s    9f


| White.
0:
    moveq.l  #32,%d4
    not.w    %d0
    and.w    %d0,(%a0)+
    and.w    %d0,(%a1)+
    moveq    #0,%d0
    sub.w    %d4,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    move.l   %d0,(%a1)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    8f
    move.w   %d0,(%a0)+
    move.w   %d0,(%a1)+
8:
    not.w    %d1
    and.w    %d1,(%a0)
    and.w    %d1,(%a1)
    move.l   (%sp)+,%d4
    rts

| Dark gray.
2:
    exg.l   %a0,%a1

| Light gray.
1:
    moveq.l  #32,%d4
    or.w     %d0,(%a0)+
    not.w    %d0
    and.w    %d0,(%a1)+
    moveq.l  #-1,%d0
    sub.w    %d4,%d2
    blt.s    5f
6:
    move.l   %d0,(%a0)+
    clr.l    (%a1)+
    sub.w    %d4,%d2
    bge.s    6b
5:
    cmpi.w   #-16,%d2
    blt.s    9f
    move.w   %d0,(%a0)+
    clr.w    (%a1)+
9:
    or.w     %d1,(%a0)
    not.w    %d1
    and.w    %d1,(%a1)
    move.l   (%sp)+,%d4
    rts
