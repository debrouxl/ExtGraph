.include "common.s"

.text
.globl DrawBuffer_OR
.even

| Display a (PLANE_BYTE_WIDTH * PLANE_PIXEL_HEIGHT) buffer onto a 240x128 1 bpp buffer, performing OR operation.

| Input :
| a0.l : source buffer address
| a1.l : destination plane address
| d0.w : x offset in pixels (0 <= d0 < PLANE_PIXEL_WIDTH - 240)
| d1.w : y offset in pixels (0 <= d1 < PLANE_PIXEL_HEIGHT - 128)

| Destroys : d0-d2/a0-a1

DrawBuffer_OR:
    movem.l  %d3-%d6,-(%a7)

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
    add.w    %d1,%d1
    adda.w   %d1,%a0	| vertical offset

    move.w   %d0,%d1
    andi.w   #15,%d0	| reduced shift count
    lsr.w    #4,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0	| horizontal offset

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2

    moveq.l  #127,%d6
0:
    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+

    swap.w   %d4	| 16 last pixels
    or.w     %d4,(%a1)+

    addq.l   #PLANE_BYTE_WIDTH-32,%a0

    dbf      %d6,0b

    movem.l  (%a7)+,%d3-%d6
    rts
