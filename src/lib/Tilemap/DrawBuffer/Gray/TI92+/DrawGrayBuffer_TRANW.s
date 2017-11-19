.include "common.s"

.text
.globl DrawGrayBuffer_TRANW
.even

| Display a (PLANE_BYTE_WIDTH * PLANE_PIXEL_HEIGHT) buffer onto a 240x128 1 bpp buffer, assuming transparent white - grayscale version.

| Input :
| a0.l : source buffer address
| a1.l : destination plane address
| d0.w : x offset in pixels (0 <= d0 < PLANE_PIXEL_WIDTH - 240)
| d1.w : y offset in pixels (0 <= d1 < PLANE_PIXEL_HEIGHT - 128)

| Destroys : d0-d2/a0-a1

DrawGrayBuffer_TRANW:
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

    moveq.l  #127,%d2
    swap.w   %d2

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2
    swap.w   %d2

0:
    swap.w   %d2

    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a2)+,%d5
    lsl.l    %d0,%d5

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d7
    and.w    %d2,%d7
    or.w     %d7,%d3

    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d7
    and.w    %d2,%d7
    or.w     %d7,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 0
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d7
    and.w    %d2,%d7
    or.w     %d7,%d4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d7
    and.w    %d2,%d7
    or.w     %d7,%d6

    move.l   %d6,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 4
    or.l     %d4,%d7
    move.l   %d7,(%a1)+

    not.l    %d4
    and.l    (%a3),%d4
    or.l     %d6,%d4
    move.l   %d4,(%a3)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d7
    and.w    %d2,%d7
    or.w     %d7,%d3

    and.w    %d1,%d5
    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d7
    and.w    %d2,%d7
    or.w     %d7,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 8
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d7
    and.w    %d2,%d7
    or.w     %d7,%d4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d7
    and.w    %d2,%d7
    or.w     %d7,%d6

    move.l   %d6,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 12
    or.l     %d4,%d7
    move.l   %d7,(%a1)+

    not.l    %d4
    and.l    (%a3),%d4
    or.l     %d6,%d4
    move.l   %d4,(%a3)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d7
    and.w    %d2,%d7
    or.w     %d7,%d3

    and.w    %d1,%d5
    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d7
    and.w    %d2,%d7
    or.w     %d7,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 16
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d7
    and.w    %d2,%d7
    or.w     %d7,%d4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d7
    and.w    %d2,%d7
    or.w     %d7,%d6

    move.l   %d6,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 20
    or.l     %d4,%d7
    move.l   %d7,(%a1)+

    not.l    %d4
    and.l    (%a3),%d4
    or.l     %d6,%d4
    move.l   %d4,(%a3)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3

    and.w    %d1,%d5
    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    and.w    %d2,%d6
    or.w     %d6,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 24
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    swap.w   %d4
    swap.w   %d6

    move.w   %d6,%d7
    not.w    %d7
    and.w    (%a1),%d7 | 28
    or.w     %d4,%d7
    move.w   %d7,(%a1)+

    not.w    %d4
    and.w    (%a3),%d4
    or.w     %d6,%d4
    move.w   %d4,(%a3)+

    addq.l   #PLANE_BYTE_WIDTH-32,%a0
    addq.l   #PLANE_BYTE_WIDTH-32,%a2

    swap.w   %d2
    dbf      %d2,0b

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
