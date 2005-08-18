| C prototype: void FastFilledRect_Invert_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__(5)));
|
| This function XORs a rectangle to the destination. The algorithm used here
| is faster than that of FastFillRect_R. FastFillRect_R is already quite
| fast, and modifying the self-modifying-code of FastFillRect_R to use this
| algorithm is very complicated and rather inefficient.

.text
.even

0:
.word 0xFFFF,0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001

1:
.word 0x8000,0xC000,0xE000,0xF000,0xF800,0xFC00,0xFE00,0xFF00,0xFF80,0xFFC0,0xFFE0,0xFFF0,0xFFF8,0xFFFC,0xFFFE,0xFFFF

.globl FastFilledRect_Invert_R
.even
FastFilledRect_Invert_R:
    movem.l  %d3-%d5/%a2-%a3,-(%sp)

    cmp.w    %d1,%d3
    bge.s    2f

    exg      %d1,%d3

2:
    sub.w    %d1,%d3                         | d3 = dy.

    cmp.w    %d0,%d2
    bge.s    2f
    exg      %d0,%d2

2:
| Here, we have dx in d2.
    movea.l  %a0,%a1

    move.w   %d1,%d4
    lsl.w    #4,%d1
    sub.w    %d4,%d1

    move.w   %d1,%d5   | save 15*y1 in d5

    move.w   %d0,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d1   | always word-aligned to avoid address error problems.

    add.w    %d1,%d1
    adda.w   %d1,%a0
| a0=address of the top left corner of the rectangle.

    move.w   %d2,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d5   | always word-aligned to avoid address error problems.

    add.w    %d5,%d5
    adda.w   %d5,%a1
| a1=address of the top right corner of the rectangle.

| Take masks of sides.
    moveq    #0xF,%d5
    and.w    %d5,%d0
    add.w    %d0,%d0
| The code was optimized and reordered so that d(pc,ix) mode can be used.
    move.w   0b(%pc,%d0.w),%d0    | d0 = mask of first pixels.

    and.w    %d5,%d2
    add.w    %d2,%d2
    move.w   1b(%pc,%d2.w),%d1     | d1 = mask of last pixels.

| Are all pixels in the same word ?
    cmpa.l   %a0,%a1
    beq.s    wl16
| Short branches are faster if not taken...

| Save loop count.
    move.w   %d3,%d4

    move.l   %a0,%a2
    move.l   %a1,%d2
    sub.l    %a2,%d2
    subq.w   #1,%d2
    lsr.w    #1,%d2
| d2 = number of complete 16-pixel columns (words) between the sides.


| Now, draw both sides of the rectangle.
s:
    eor.w    %d0,(%a0)
    eor.w    %d1,(%a1)
    lea      30(%a0),%a0
    lea      30(%a1),%a1
    dbf      %d3,s

| We've drawn both sides of the rectangle. Skip the left side.
    addq.l   #2,%a2

| We are going to check how many pixels we can draw at once (0, 16, 32, 64).
5:
| Restore loop count and pointers (after modification).
    move.w   %d4,%d3
    move.l   %a2,%a0

| Check for 64 pixels.
    subq.w   #4,%d2
    bge.s    w64
| Check for 32 pixels.
    addq.w   #2,%d2
    bge.s    w32
| Check for 16 pixels.
    addq.w   #1,%d2
    bne.s    6f
| We have one column left.

w16:
    not.w    (%a0)
    lea      30(%a0),%a0
    dbf      %d3,w16
| We've finished.
    bra.s    6f

w64:
| Write 64 pixels at once (2*32).
    not.l    (%a0)+
    not.l    (%a0)
    lea      30-4(%a0),%a0
    dbf      %d3,w64
    addq.l   #8,%a2
    bra.s    5b

w32:
| Write 32 pixels at once (1*32). Despite the tighter loop, this is much
| more efficient size-wise and speed-wise than writing 2*16 pixels.
    not.l    (%a0)
    lea      30(%a0),%a0
    dbf      %d3,w32
    addq.l   #4,%a2
    bra.s    5b


wl16:
    and.w    %d0,%d1
4:
    eor.w    %d1,(%a0)
    lea      30(%a0),%a0
    dbf      %d3,4b

6:
    movem.l  (%sp)+,%d3-%d5/%a2-%a3
    rts
