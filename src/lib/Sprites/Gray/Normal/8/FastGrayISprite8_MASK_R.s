| C prototype ! void FastGraySprite8_MASK(x,y,h,sprt,mask,dest);
| Environ 82% plus rapide que GraySprite8_MASK de extgraph 1.02

.text
.globl FastGraySprite8_MASK_R
.even
FastGraySprite8_MASK_R:
    dbf      %d2,suite
    rts

suite:
    move.w   %d3,-(%a7)

    move.w   %d1,%d3	| d3 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d3,%d1	| d1 = 15*y

    move.w   %d0,%d3	| d3 = x
    lsr.w    #4,%d3	| d3 = x/16

    add.w    %d3,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = y*PLANE_BYTE_WIDTH + x/8
    adda.w   %d1,%a0	| a0 += offset

    move.w   (%a7)+,%d3

    and.w    #0xF,%d0
    moveq.l  #8,%d1
    sub.w    %d0,%d1
    bgt.s    pre_loop_Sprite8_OR_2

    addi.w   #16,%d1

    lsr.w    #1,%d2
    bcs.s    _loop_Sprite8_OR_1

    lea.l    -PLANE_BYTE_WIDTH(%a0),%a0
    bra.s    Milieu1

_loop_Sprite8_OR_1:
    moveq.l  #-1,%d0
    move.b   (%a1)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,(%a0)

    and.l    %d0,6000(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,6000(%a0)

Milieu1:
    moveq.l  #-1,%d0
    move.b   (%a1)+,%d0
    rol.l    %d1,%d0
    and.l    %d0,PLANE_BYTE_WIDTH(%a0)

    and.l    %d0,6000+PLANE_BYTE_WIDTH(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,PLANE_BYTE_WIDTH(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    lsl.l    %d1,%d0
    or.l     %d0,6000+PLANE_BYTE_WIDTH(%a0)

    lea      2*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,_loop_Sprite8_OR_1

    rts

pre_loop_Sprite8_OR_2:
    lsr.w    #1,%d2
    bcs.s    _loop_Sprite8_OR_2

    lea.l    -PLANE_BYTE_WIDTH(%a0),%a0
    bra.s    Milieu2

_loop_Sprite8_OR_2:
    moveq.l  #-1,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    rol.l    %d1,%d0
    and.l    %d0,(%a0)

    and.l    %d0,6000(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    lsl.l    %d1,%d0
    or.l     %d0,(%a0)

    moveq    #0,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    lsl.l    %d1,%d0
    or.l     %d0,6000(%a0)

Milieu2:
    moveq.l  #-1,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    rol.l    %d1,%d0
    and.l    %d0,PLANE_BYTE_WIDTH(%a0)

    and.l    %d0,6000+PLANE_BYTE_WIDTH(%a0)

    moveq.l  #0,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    lsl.l    %d1,%d0
    or.l     %d0,PLANE_BYTE_WIDTH(%a0)

    moveq.l  #0,%d0
    move.b   (%a1)+,%d0
    swap.w   %d0
    lsl.l    %d1,%d0
    or.l     %d0,6000+PLANE_BYTE_WIDTH(%a0)

    lea      2*PLANE_BYTE_WIDTH(%a0),%a0

    dbf      %d2,_loop_Sprite8_OR_2

    rts
