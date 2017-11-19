.include "common.s"

.text
.globl DrawGrayBuffer89_OR
.even

| Display a (PLANE_BYTE_WIDTH * PLANE_PIXEL_HEIGHT) buffer onto the 100 first lines of a 240x128 1 bpp buffer, performing OR operation - grayscale version.

| Input :
| a0.l : source buffer address
| a1.l : destination plane address
| d0.w : x offset in pixels (0 <= d0 < PLANE_PIXEL_WIDTH - 240)
| d1.w : y offset in pixels (0 <= d1 < PLANE_PIXEL_HEIGHT - 128)

| Destroys : d0-d2/a0-a1

DrawGrayBuffer89_OR:
    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2
    add.w    %d1,%d1
    adda.w   %d1,%a0	| vertical offset

    move.w   %d0,%d1
    andi.w   #15,%d0	| reduced shift count
    lsr.w    #4,%d1
    add.w    %d1,%d1
    adda.w   %d1,%a0	| horizontal offset

    lea.l    PLANE_BYTE_WIDTH * PLANE_PIXEL_HEIGHT(%a0),%a2
    lea.l    3840(%a1),%a3

    moveq.l  #99,%d7

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2

0:
    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+	| 1

    move.l   (%a2)+,%d5
    lsl.l    %d0,%d5

    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d3
    and.w    %d2,%d3
    or.w     %d3,%d5
    or.l     %d5,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+	| 2

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d4
    and.w    %d2,%d4
    or.w     %d4,%d6
    or.l     %d6,(%a3)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d6
    and.w    %d2,%d6
    or.w     %d6,%d3
    or.l     %d3,(%a1)+	| 3

    and.w    %d1,%d5
    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d3
    and.w    %d2,%d3
    or.w     %d3,%d5
    or.l     %d5,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+	| 4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d4
    and.w    %d2,%d4
    or.w     %d4,%d6
    or.l     %d6,(%a3)+

    and.w    %d1,%d3
    move.w   (%a0)+,%d4
    rol.w    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3
    or.l     %d3,(%a1)+	| 5

    and.w    %d1,%d5
    move.w   (%a2)+,%d6
    rol.w    %d0,%d6
    and.w    %d2,%d6
    or.w     %d6,%d5
    or.l     %d5,(%a3)+

    lea.l    PLANE_BYTE_WIDTH-22(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH-22(%a2),%a2
    lea.l    10(%a1),%a1
    lea.l    10(%a3),%a3

    dbf      %d7,0b

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
